#ifndef DEADLINE_H
#define DEADLINE_H

#include <QDateTime>
#include "Memo.h"

class Deadline : public Memo {

public:
    Deadline(const unsigned int id, const QString title, const QString descr, const QDateTime& date, const bool hasTime, const bool isDone);
    Deadline(const Deadline& d);

    QDateTime getDate() const;
    bool getHasTime() const;

    void setDate(const QDateTime& endDate);
    void setHasTime(const bool hasTime);

    void accept(ReminderVisitor *visitor) override;
    void accept(ConstReminderVisitor *visitor) const override;
    
private:
    QDateTime date;
    bool hasTime;

};

#endif
