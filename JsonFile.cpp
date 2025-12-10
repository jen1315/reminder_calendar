#include "JsonFile.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "./model/Event.h"
#include "./model/Deadline.h"
#include "./model/Memo.h"

JsonFile::JsonFile(const QString jsonUrl) {
    file = new QFile(jsonUrl);
    lib = new QMap<int, AbstractMedia*>();
    if(!file->open(QIODevice::ReadOnly)) {
        qDebug("Errore di caricamento.");
    }
    
    QByteArray data = file->readAll();
    file->close();
    
    QJsonDocument json = QJsonDocument::fromJson(data);
    if(!json.isArray()) {
        qDebug("Errore di caricamento.");
    }
    
    QJsonArray array = json.array();
    
    for(auto it=array.begin(); it!=array.end(); ++it) {
        QJsonObject obj = it->toObject();

        QString type = obj["type"].toString();
        int id = obj["id"].toInt();
        QString title = obj["title"].toString();
        QString descr = obj["descr"].toString();

        AbstractReminder *reminder;

        if(type=="event")
            reminder = new Event(id, title, descr, QDateTime::fromString(obj["start_date"].toString(), "yyyy-MM-dd hh:mm:ss"), QDateTime::fromString(obj["end_date"].toString()), obj["hasTime"]);
        if(type=="deadline")
            reminder = new Deadline(id, title, descr, QDateTime::fromString(obj["date"].toString(), "yyyy-MM-dd hh:mm:ss"), obj["hasTime"]);
        if(type=="reminder")
            reminder = new Memo(id, title, descr, obj["isDone"]);
        calendar->insert(id, reminder);
    }
}

QMap<int, AbstractReminder*>& JsonFile::getMap() const {
    return *calendar;
}

void JsonFile::submitChanges(int id) const {
    QJsonArray array;

    for(auto it=calendar->begin(); it!=calendar->end(); ++it) {
        array.append((*it)->toJson());
    }
    
    QJsonDocument doc(array);
    
    if(!file->open(QIODevice::ReadOnly)) {
        qDebug("Errore di caricamento.");
    }
    
    file->write(doc.toJson());
    file->close();
}
