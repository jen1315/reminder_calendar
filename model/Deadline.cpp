#include "Deadline.h"

Deadline::Deadline(unsigned int id, QString name, QString descr, QDateTime& date, bool hasTime) : AbstractReminder(id, name, descr), date(std::make_unique<QDateTime>(date)), hasTime(hasTime) {}

Deadline::Deadline(Deadline& d) : AbstractReminder(d), date(d.date.get()), hasTime(d.hasTime) {}

QDateTime& Deadline::getDate() const {
    return *date;
}

bool Deadline::getHasTime() const {
    return hasTime;
}

void Deadline::setDate(const QDateTime& date) {
    this->date = std::make_unique<QDateTime>(date);
}

void Deadline::setHasTime(const bool hasTime) {
    this->hasTime = hasTime;
}

void Deadline::accept(ReminderVisitor *visitor) {
    visitor->visit(this);
}

void Deadline::acceptEdit(ReminderVisitor *visitor) {
    visitor->visitEdit(this);
}
