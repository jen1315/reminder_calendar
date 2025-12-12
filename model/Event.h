#ifndef EVENT_H
#define EVENT_h

#include <memory>
#include <QDateTime>
#include "AbstractReminder.h"

class Event : public AbstractReminder {

public:
    Event(unsigned int id, QString title, QString descr, QDateTime& startDate, QDateTime& endDate, bool hasTime);
    Event(Event& e);

    QDateTime& getStartDate() const;
    QDateTime& getEndDate() const;
    bool getHasTime() const;

    void setStartDate(const QDateTime& startDate);
    void setEndDate(const QDateTime& endDate);
    void setHasTime(const bool hasTime);

    virtual void accept(ReminderVisitor *visitor) = 0;
    virtual void acceptEdit(ReminderVisitor *visitor) = 0;
    
private:
    std::unique_ptr<QDateTime> startDate;
    std::unique_ptr<QDateTime> endDate;
    bool hasTime;

};

#endif