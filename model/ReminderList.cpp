#include "ReminderList.h"
#include "Event.h"
#include "Deadline.h"

ReminderList::ReminderList(const QList<AbstractReminder*>& list) : list(list) {}

ReminderList::ReminderList(const ReminderList& l) : list(l.list) {}

ReminderList::~ReminderList() {
    for(auto it=list.begin(); it!=list.end(); it++) {
        delete *it;
    }
}

unsigned int ReminderList::getSize() const {
    return list.size();
}

QList<AbstractReminder*>::iterator ReminderList::begin() {
    return list.begin();
}

QList<AbstractReminder*>::iterator ReminderList::end() {
    return list.end();
}

QList<AbstractReminder*>::const_iterator ReminderList::begin() const {
    return list.begin();
}

QList<AbstractReminder*>::const_iterator ReminderList::end() const {
    return list.end();
}

AbstractReminder& ReminderList::get(const unsigned int id) const {
    return *(list[id]);
}

void ReminderList::add(AbstractReminder& r) {
    unsigned int id = r.getId();
    if(list.size() <= id)
        list.append(&r);
    else
        list.replace(id, &r);
}

bool ReminderList::remove(const unsigned int id) {

    if(list.size() <= id)
        return false;

    if(list.size()-1 == id) {
        list.removeLast();
    }
    else {
        delete list[id];
        (list.last())->setId(id);
        list.replace(id, list.takeLast());
    }
    return true;
}

ReminderList& ReminderList::search(const QString text) const {
    ReminderList *results = new ReminderList();
    for(auto it = list.begin(); it!=list.end(); ++it) {
        if(((*it)->getTitle()).contains(text) || ((*it)->getDescr()).contains(text))
            results->add(**it);
    }
    return *results;
}

ReminderList& ReminderList::getByDate(const QDate& date) const {
    ReminderList *results = new ReminderList();
    for(auto it = list.begin(); it!=list.end(); ++it) {
        if(dynamic_cast<Event*>(*it)) {
            Event *e = static_cast<Event*>(*it);
            if(date>=e->getStartDate().date() && date<=e->getEndDate().date())
                results->add(**it);
        }
        if(dynamic_cast<Deadline*>(*it) && static_cast<Deadline*>(*it)->getDate().date()==date)
            results->add(**it);
    }
    return *results;
}
