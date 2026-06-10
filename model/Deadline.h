#ifndef DEADLINE_H
#define DEADLINE_H

#include <QDateTime>
#include "AbstractReminder.h"

class Deadline : public AbstractReminder {

public:
    Deadline(const unsigned int id, const QString title, const QString descr, const QDateTime& date, const bool hasTime, const bool isDone);
    Deadline(const Deadline& d);

    QDateTime getDate() const;
    bool getHasTime() const;
    bool getIsDone() const;

    void setDate(const QDateTime& endDate);
    void setHasTime(const bool hasTime);
    void setIsDone(const bool isDone);

    virtual void accept(ReminderVisitor *visitor);
    virtual void acceptEdit(ReminderVisitor *visitor);
    
private:
    QDateTime date;
    bool hasTime;
    bool isDone;

};

#endif
