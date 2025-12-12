#include "Event.h"

Event::Event(unsigned int id, QString& name, QString& descr, QDateTime& startDate, QDateTime& endDate, bool hasTime) : AbstractReminder(id, name, descr), startDate(startDate), endDate(endDate), hasTime(hasTime) {}

Event::Event(Event& e) : AbstractReminder(e), startDate(e.startDate), endDate(e.endDate), hasTime(e.hasTime) {}

QDateTime& Event::getStartDate() const {
    return *startDate;
}

QDateTime& Event::getEndDate() const {
    return *endDate;
}

bool Event::getHasTime() const {
    return *hasTime;
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

void Event::accept(MediaVisitor *visitor) {
    visitor->visit(this);
}

void Event::acceptEdit(MediaVisitor *visitor) {
    visitor->visitEdit(this);
}