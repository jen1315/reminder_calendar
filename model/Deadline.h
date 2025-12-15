#ifndef DEADLINE_H
#define DEADLINE_h

#include <memory>
#include <QDateTime>
#include "AbstractReminder.h"

class Deadline : public AbstractReminder {

public:
    Deadline(unsigned int id, QString title, QString descr, QDateTime& date, bool hasTime);
    Deadline(Deadline& d);

    QDateTime& getDate() const;
    bool getHasTime() const;

    void setDate(const QDateTime& endDate);
    void setHasTime(const bool hasTime);

    virtual void accept(ReminderVisitor *visitor) = 0;
    virtual void acceptEdit(ReminderVisitor *visitor) = 0;
    
private:
    std::unique_ptr<QDateTime> date;
    bool hasTime;

};

#endif
