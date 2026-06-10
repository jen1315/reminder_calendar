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
    QMap<unsigned int, AbstractReminder*> calendar;
    unsigned int count = 0;
    
    for(auto it=array.begin(); it!=array.end(); ++it) {
        QJsonObject obj = it->toObject();

        QString type = obj["type"].toString();
        int id = obj["id"].toInt();
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
    list = new ReminderList(calendar, count);
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
    QJsonObject obj;
    array.replace(pos, obj);
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

    QJsonObject obj;
    obj["id"] = (int)(r.getId());
    obj["title"] = r.getTitle();
    obj["descr"] = r.getDescr();
    if(dynamic_cast<const Event*>(&r)) {
        const Event* e = static_cast<const Event*>(&r);
        obj["start_date"] = e->getStartDate().toString("yyyy-MM-dd hh:mm:ss");
        obj["end_date"] = e->getEndDate().toString("yyyy-MM-dd hh:mm:ss");
        obj["has_time"] = e->getHasTime();
        obj["type"] = "event";
    }
    if(dynamic_cast<const Deadline*>(&r)) {
        const Deadline* d = static_cast<const Deadline*>(&r);
        obj["date"] = d->getDate().toString("yyyy-MM-dd hh:mm:ss");
        obj["has_time"] = d->getHasTime();
        obj["type"] = "deadline";
    }
    if(dynamic_cast<const Memo*>(&r)) {
        const Memo* m = static_cast<const Memo*>(&r);
        obj["done"] = m->getIsDone();
        obj["type"] = "memo";
    }

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