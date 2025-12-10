#ifndef MEMO_H
#define MEMO_H

#include "AbstractReminder.h"

class Memo : public AbstractReminder {

public:
    Memo(unsigned int id, QString title, QString descr, bool done);
    Memo(Memo& m);

    QDateTime getIsDone() const;

    void setIsDone(bool done);

    virtual void accept(ReminderVisitor *visitor) = 0;
    virtual void acceptEdit(ReminderVisitor *visitor) = 0;

private:
    bool done;

};

#endif