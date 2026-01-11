#ifndef REMINDERLIST_H
#define REMINDERLIST_H

#include <memory>
#include <QMap>
#include "AbstractReminder.h"

class ReminderList {

template<typename Iter>
class iterator_range {

public:
    iterator_range(Iter begin, Iter end);
    Iter begin() const;
    Iter end() const;

private:
    Iter begin_, end_;

};

public:
    ReminderList();
    ReminderList(const QMap<unsigned int, std::unique_ptr<AbstractReminder>>& list);
    ReminderList(const ReminderList& l);

    unsigned int getNumElem() const;
    AbstractReminder& getReminders();

    void add(const AbstractReminder& r);
    AbstractReminder& remove(unsigned int id);
    AbstractReminder& get(unsigned int id);
    ReminderList& search(QString text) const;

private:
    std::unique_ptr<QMap<unsigned int, std::unique_ptr<AbstractReminder>>> list;
    unsigned int n_elem;

};

#endif
