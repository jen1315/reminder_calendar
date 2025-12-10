#include "AbstractReminder.h"

AbstractReminder::AbstractReminder(unsigned int id, QString title, QString descr) : id(id), title(title), description(descr) {}

AbstractReminder::AbstractReminder(AbstractReminder& m) : id(m.id), title(m.title), description(m.description) {};

unsigned int AbstractReminder::getId() const {
    return id;
}

QString AbstractReminder::getTitle() const {
    return title;
}

QDateTime AbstractReminder::getDate() const {
    return date;
}

bool AbstractReminder::getHasTime() const {
    return hasTime;
}

QString AbstractReminder::getDescr() const {
    return description;
}

void AbstractReminder::setId(unsigned int id) {
    this->id = id;
}

void AbstractReminder::setTitle(QString title) {
    this->title = title;
}

void AbstractReminder::setDescr(QString descr){
    this->description = descr;
}