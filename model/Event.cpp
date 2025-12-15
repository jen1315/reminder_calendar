#include "Event.h"

Event::Event(unsigned int id, QString name, QString descr, QDateTime& startDate, QDateTime& endDate, bool hasTime) : AbstractReminder(id, name, descr), startDate(std::make_unique<QDateTime>(startDate)), endDate(std::make_unique<QDateTime>(endDate)), hasTime(hasTime) {}

Event::Event(Event& e) : AbstractReminder(e), startDate(e.startDate.get()), endDate(e.endDate.get()), hasTime(e.hasTime) {}

QDateTime& Event::getStartDate() const {
    return *startDate;
}

QDateTime& Event::getEndDate() const {
    return *endDate;
}

bool Event::getHasTime() const {
    return hasTime;
}

void Event::setStartDate(const QDateTime& startDate) {
    this->startDate = std::make_unique<QDateTime>(startDate);
}

void Event::setEndDate(const QDateTime& endDate) {
    this->endDate = std::make_unique<QDateTime>(endDate);
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
