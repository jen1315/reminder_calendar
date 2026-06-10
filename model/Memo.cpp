#include "Memo.h"

Memo::Memo(const unsigned int id, const QString title, const QString descr, const bool done) : AbstractReminder(id, title, descr), done(done) {}

Memo::Memo(const Memo& m) : AbstractReminder(m), done(m.done) {}

bool Memo::getIsDone() const {
    return done;
}

void Memo::setIsDone(const bool done) {
    this->done = done;
}

void Memo::accept(ReminderVisitor *visitor) {
    visitor->visit(this);
}

void Memo::acceptEdit(ReminderVisitor *visitor) {
    visitor->visitEdit(this);
}
