#include "Deadline.h"

Deadline::Deadline(const unsigned int id, const QString name, const QString descr, const QDateTime& date, const bool hasTime, const bool isDone) : AbstractReminder(id, name, descr), date(date), hasTime(hasTime), isDone(isDone) {}

Deadline::Deadline(const Deadline& d) : AbstractReminder(d), date(d.date), hasTime(d.hasTime), isDone(d.isDone) {}

QDateTime Deadline::getDate() const {
    return date;
}

bool Deadline::getHasTime() const {
    return hasTime;
}

bool Deadline::getIsDone() const {
    return isDone;
}

void Deadline::setDate(const QDateTime& date) {
    this->date = date;
}

void Deadline::setHasTime(const bool hasTime) {
    this->hasTime = hasTime;
}

void Deadline::setIsDone(const bool isDone) {
    this->isDone = isDone;
}

void Deadline::accept(ReminderVisitor *visitor) {
    visitor->visit(this);
}

void Deadline::acceptEdit(ReminderVisitor *visitor) {
    visitor->visitEdit(this);
}
