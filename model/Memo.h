#ifndef MEMO_H
#define MEMO_H

#include "AbstractReminder.h"

class Memo : public AbstractReminder {

public:
    Memo(const unsigned int id, const QString title, const QString descr, const bool done);
    Memo(const Memo& m);

    bool getIsDone() const;

    void setIsDone(const bool done);

    virtual void accept(ReminderVisitor *visitor);
    virtual void accept(ConstReminderVisitor *visitor) const;

private:
    bool done;

};

#endif
