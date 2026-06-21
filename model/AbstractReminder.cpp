#include "AbstractReminder.h"

AbstractReminder::AbstractReminder(const unsigned int id, const QString title, const QString descr) : id(id), title(title), description(descr) {}

AbstractReminder::AbstractReminder(const AbstractReminder& m) : id(m.id), title(m.title), description(m.description) {}

unsigned int AbstractReminder::getId() const {
    return id;
}

QString AbstractReminder::getTitle() const {
    return title;
}

QString AbstractReminder::getDescr() const {
    return description;
}

void AbstractReminder::setId(const unsigned int id) {
    this->id = id;
}

void AbstractReminder::setTitle(const QString title) {
    this->title = title;
}

void AbstractReminder::setDescr(const QString descr){
    this->description = descr;
}