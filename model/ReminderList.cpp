#include "ReminderList.h"
#include "Event.h"
#include "Deadline.h"

ReminderList::ReminderList() {
    counter = 0;
}

ReminderList::ReminderList(const QMap<unsigned int, AbstractReminder*>& map, unsigned int counter) : list(map), counter(counter) {}

ReminderList::ReminderList(const ReminderList& l) : list(l.list), counter(l.counter) {}

ReminderList::~ReminderList() {
    for(auto it=list.begin(); it!=list.end(); it++) {
        delete *it;
    }
}

unsigned int ReminderList::getCounter() const {
    return counter;
}

QMap<unsigned int, AbstractReminder*>::iterator ReminderList::begin() {
    return list.begin();
}

QMap<unsigned int, AbstractReminder*>::iterator ReminderList::end() {
    return list.end();
}

QMap<unsigned int, AbstractReminder*>::const_iterator ReminderList::begin() const {
    return list.begin();
}

QMap<unsigned int, AbstractReminder*>::const_iterator ReminderList::end() const {
    return list.end();
}

ReminderList& ReminderList::operator=(const ReminderList &other) {
    for(auto it=other.begin(); it!=other.end(); ++it)
        add(**it);
    counter = other.counter;
    return *this;
}
    

AbstractReminder& ReminderList::get(const unsigned int id) const {
    return *(list[id]);
}

void ReminderList::add(AbstractReminder& r) {
    if(!list.contains(r.getId())) {
        counter += 1;
    }
    list.insert(r.getId(), &r);
}

bool ReminderList::remove(const unsigned int id) {
    if(list.contains(id)) {
        delete list[id];
        list.remove(id);
        return true;
    }
    return false;
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
