#include "Event.h"

Event::Event(const unsigned int id, const QString name, const QString descr, const QDateTime& startDate, const QDateTime& endDate, const bool hasTime) : AbstractReminder(id, name, descr), startDate(startDate), endDate(endDate), hasTime(hasTime) {}

Event::Event(const Event& e) : AbstractReminder(e), startDate(e.startDate), endDate(e.endDate), hasTime(e.hasTime) {}

QDateTime Event::getStartDate() const {
    return startDate;
}

QDateTime Event::getEndDate() const {
    return endDate;
}

bool Event::getHasTime() const {
    return hasTime;
}

void Event::setStartDate(const QDateTime& startDate) {
    this->startDate = startDate;
}

void Event::setEndDate(const QDateTime& endDate) {
    this->endDate = endDate;
}

void Event::setHasTime(const bool hasTime) {
    this->hasTime = hasTime;
}

void Event::accept(ReminderVisitor *visitor) {
    visitor->visit(this);
}

void Event::acceptEdit(ReminderVisitor *visitor) {
    visitor->visitEdit(this);
}
