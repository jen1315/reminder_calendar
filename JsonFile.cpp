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

    if(!file->open(QIODevice::ReadOnly)) {
        qDebug("Errore di caricamento.");
    }
    
    QJsonDocument json = QJsonDocument::fromJson(file->readAll());
    file->close();
    
    if(!json.isArray()) {
        qDebug("Errore di caricamento.");
    }
    
    QJsonArray array = json.array();
    QList<AbstractReminder*> calendar;
    unsigned int count = 0;
    
    for(auto it=array.begin(); it!=array.end(); ++it) {
        QJsonObject obj = it->toObject();

        QString type = obj["type"].toString();
        int id = count;
        QString title = obj["title"].toString();
        QString descr = obj["descr"].toString();

        AbstractReminder *reminder;
        if(type=="event") {
            QDateTime start = QDateTime::fromString(obj["start_date"].toString(), "yyyy-MM-dd hh:mm:ss");
            QDateTime end = QDateTime::fromString(obj["end_date"].toString(), "yyyy-MM-dd hh:mm:ss");
            reminder = new Event(id, title, descr, start, end, obj["has_time"].toBool());
            calendar.insert(id, reminder);
        }
        if(type=="deadline") {
            QDateTime date = QDateTime::fromString(obj["date"].toString(), "yyyy-MM-dd hh:mm:ss");
            reminder = new Deadline(id, title, descr, date, obj["has_time"].toBool(), obj["done"].toBool());
            calendar.insert(id, reminder);
        }
        if(type=="memo") {
            reminder = new Memo(id, title, descr, obj["done"].toBool());
            calendar.insert(id, reminder);
        }
        count += 1;
    }
    list = new ReminderList(calendar);
}

ReminderList& JsonFile::getList() {
    return *list;
}

void JsonFile::erase(const unsigned int pos) {
    if(!file->open(QIODevice::ReadOnly)) {
        qDebug("Errore di caricamento.");
    }

    QJsonDocument json = QJsonDocument::fromJson(file->readAll());
    file->close();
    
    QJsonArray array = json.array();
    if(pos < array.size()-1) {
        QJsonObject obj = (array.last()).toObject();
        obj["id"] = (int)pos;
        array.replace(pos, obj);
    }
    array.removeLast();
    json.setArray(array);

    file->open(QFile::WriteOnly | QFile::Truncate);
    file->write(json.toJson());
    file->close();
}

void JsonFile::save(const AbstractReminder& r, bool isAdd) {
    
    if(!file->open(QIODevice::ReadOnly)) {
        qDebug("Errore di caricamento.");
    }

    QJsonDocument json = QJsonDocument::fromJson(file->readAll());
    file->close();

    obj = QJsonObject();
    obj["id"] = (int)(r.getId());
    obj["title"] = r.getTitle();
    obj["descr"] = r.getDescr();
    
    r.accept(this);

    QJsonArray array = json.array();
    if(isAdd)
        array.push_back(obj);
    else
        array.replace(r.getId(), obj);
    json.setArray(array);

    file->open(QFile::WriteOnly | QFile::Truncate);
    file->write(json.toJson());
    file->close();
}

void JsonFile::visit(const Event *event) {
    obj["start_date"] = event->getStartDate().toString("yyyy-MM-dd hh:mm:ss");
    obj["end_date"] = event->getEndDate().toString("yyyy-MM-dd hh:mm:ss");
    obj["has_time"] = event->getHasTime();
    obj["type"] = "event";
}

void JsonFile::visit(const Deadline *deadline) {
    obj["date"] = deadline->getDate().toString("yyyy-MM-dd hh:mm:ss");
    obj["has_time"] = deadline->getHasTime();
    obj["done"] = deadline->getIsDone();
    obj["type"] = "deadline";
}

void JsonFile::visit(const Memo *memo) {
    obj["done"] = memo->getIsDone();
    obj["type"] = "memo";  
}