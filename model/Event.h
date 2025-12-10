#ifndef EVENT_H
#define EVENT_h

#include <QDateTime>
#include "AbstractReminder.h"

class Event : public AbstractReminder {

public:
    Event(unsigned int id, QString title, QString descr, QDateTime startDate, QDateTime endDate, bool hasTime);
    Event(Event& e);

    QDateTime getStardDate() const;
    QDateTime getEndDate() const;
    bool getHasTime() const;

    void setStartDate(QDateTime startDate);
    void setEndDate(QDateTime endDate);
    void setHasTime(bool hasTime);

    virtual void accept(ReminderVisitor *visitor) = 0;
    virtual void acceptEdit(ReminderVisitor *visitor) = 0;
    
private:
    QDateTime startDate;
    QDateTime endDate;
    bool hasTime;

};

#endif