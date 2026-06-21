#ifndef REMINDERLIST_H
#define REMINDERLIST_H

#include <QList>
#include "AbstractReminder.h"

class ReminderList {

public:
    ReminderList() = default;
    ReminderList(const QList<AbstractReminder*>& list);
    ReminderList(const ReminderList& l);
    ~ReminderList();

    QList<AbstractReminder*>::iterator begin();
    QList<AbstractReminder*>::iterator end();
    QList<AbstractReminder*>::const_iterator begin() const;
    QList<AbstractReminder*>::const_iterator end() const;
    unsigned int getSize() const;

    void add(AbstractReminder& r);
    bool remove(const unsigned int id);
    AbstractReminder& get(const unsigned int id) const;
    ReminderList& search(const QString text) const;
    ReminderList& getByDate(const QDate& date) const;

private:
    QList<AbstractReminder*> list;

};

#endif
