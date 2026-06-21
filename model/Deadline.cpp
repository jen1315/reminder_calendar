#include "Deadline.h"

Deadline::Deadline(const unsigned int id, const QString name, const QString descr, const QDateTime& date, const bool hasTime, const bool isDone) : Memo(id, name, descr, isDone), date(date), hasTime(hasTime) {}

Deadline::Deadline(const Deadline& d) : Memo(d), date(d.date), hasTime(d.hasTime) {}

QDateTime Deadline::getDate() const {
    return date;
}

bool Deadline::getHasTime() const {
    return hasTime;
}

void Deadline::setDate(const QDateTime& date) {
    this->date = date;
}

void Deadline::setHasTime(const bool hasTime) {
    this->hasTime = hasTime;
}

void Deadline::accept(ReminderVisitor *visitor) {
    visitor->visit(this);
}

void Deadline::accept(ConstReminderVisitor *visitor) const {
    visitor->visit(this);
}