#include "ReminderList.h"

ReminderList::ReminderList() {
    list = new QMap<unsigned int, AbstractReminder>();
    n_elem = 0;
}

ReminderList::ReminderList(QMap<unsigned int, std::unique_ptr<AbstractReminder>>& map) : list(map), n_elem(map.size()) {}

unsigned int ReminderList::getNumElem() const {
    return n_elem;
}

AbstractReminder& ReminderList::get(unsigned int id) {
    return list.find(id);
}

void ReminderList::add(const AbstractReminder& r) {
    list.insert(r.getId(), std::make_unique<AbstractReminder>(r));
}

AbstractReminder& ReminderList::remove(const unsigned int id) {
    if(list.erase(id))
        n_elem -= 1;
}

ReminderList& search(const QString text) const {
    ReminderList *results = new ReminderList();
    for(auto it = list.begin(); it!=list.end(); ++it) {
        if(((*it)->getTitle()).contains(text) || ((*it)->getDescr()).contains(text))
            results.add((*it)->getId(), *it);
    }
    return *results; 
}



