#include "Deadline.h"

Deadline::Deadline(unsigned int id, QString& name, QString& descr, QDateTime& date, bool hasTime) : AbstractReminder(id, name, descr), date(date), hasTime(hasTime) {}

Deadline::Deadline(Deadline& d) : AbstractReminder(d), date(d.date), hasTime(d.hasTime) {}

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

void Deadline::accept(MediaVisitor *visitor) {
    visitor->visit(this);
}

void Deadline::acceptEdit(MediaVisitor *visitor) {
    visitor->visitEdit(this);
}