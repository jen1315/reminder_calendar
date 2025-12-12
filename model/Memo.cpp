#import "Memo.h"

Memo::Memo(unsigned int id, QString& title, QString& descr, bool done) : AbstractReminder(id, name, descr), done(done) {}

Memo::Memo(Memo& m) : AbstractReminder(m.id, m.title, m.descr), done(m.done) {}

bool Memo::getIsDone() const {
    return done;
}

void Memo::setIsDone(const bool done) {
    this->done = done;
}