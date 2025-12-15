#include "Memo.h"

Memo::Memo(unsigned int id, QString title, QString descr, bool done) : AbstractReminder(id, title, descr), done(done) {}

Memo::Memo(Memo& m) : AbstractReminder(m), done(m.done) {}

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
