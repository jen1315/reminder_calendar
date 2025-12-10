#ifndef DEADLINE_H
#define DEADLINE_h

#include <QDateTime>
#include "AbstractReminder.h"

class Deadline : public AbstractReminder {

public:
    Deadline(unsigned int id, QString title, QString descr, QDateTime date);
    Deadline(Deadline& d);

    QDateTime getDate() const;
    bool getHasTime() const;

    void setDate(QDateTime endDate);
    bool getHasTime(bool hasTime);

    virtual void accept(ReminderVisitor *visitor) = 0;
    virtual void acceptEdit(ReminderVisitor *visitor) = 0;
    
private:
    QDateTime date;
    bool hasTime;

};

#endif