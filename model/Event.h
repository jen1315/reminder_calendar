#ifndef EVENT_H
#define EVENT_H

#include <QDateTime>
#include "AbstractReminder.h"

class Event : public AbstractReminder {

public:
    Event(const unsigned int id, const QString title, const QString descr, const QDateTime& startDate, const QDateTime& endDate, const bool hasTime);
    Event(const Event& e);

    QDateTime getStartDate() const;
    QDateTime getEndDate() const;
    bool getHasTime() const;

    void setStartDate(const QDateTime& startDate);
    void setEndDate(const QDateTime& endDate);
    void setHasTime(const bool hasTime);

    void accept(ReminderVisitor *visitor) override;
    void accept(ConstReminderVisitor *visitor) const override;
    
private:
    QDateTime startDate;
    QDateTime endDate;
    bool hasTime;

};

#endif
