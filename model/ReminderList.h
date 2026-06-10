#ifndef REMINDERLIST_H
#define REMINDERLIST_H

#include <QMap>
#include "AbstractReminder.h"

class ReminderList {

public:
    ReminderList();
    ReminderList(const QMap<unsigned int, AbstractReminder*>& list, unsigned int counter);
    ReminderList(const ReminderList& l);
    ~ReminderList();

    QMap<unsigned int, AbstractReminder*>::iterator begin();
    QMap<unsigned int, AbstractReminder*>::iterator end();
    QMap<unsigned int, AbstractReminder*>::const_iterator begin() const;
    QMap<unsigned int, AbstractReminder*>::const_iterator end() const;
    ReminderList& operator=(const ReminderList &other);
    unsigned int getCounter() const;

    void add(AbstractReminder& r);
    bool remove(const unsigned int id);
    AbstractReminder& get(const unsigned int id) const;
    ReminderList& search(const QString text) const;
    ReminderList& getByDate(const QDate& date) const;

private:
    QMap<unsigned int, AbstractReminder*> list;
    unsigned int counter;

};

#endif
