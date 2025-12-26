#ifndef REMINDERLIST_H
#define REMINDERLIST_H

#include <memory>
#include <QMap>
#include "AbstractReminder.h"

class ReminderList {

public:
    ReminderList();
    ReminderList(QMap<unsigned int, std::unique_ptr<AbstractReminder>>& list);

    unsigned int getNumElem() const;

    void add(const AbstractReminder& r);
    AbstractReminder& remove(unsigned int id);
    AbstractReminder& get(unsigned int id);
    ReminderList& search(QString text) const;

private:
    QMap<unsigned int, std::unique_ptr<AbstractReminder>>* list;
    unsigned int n_elem;

};

#endif