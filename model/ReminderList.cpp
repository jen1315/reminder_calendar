#include "ReminderList.h"
template<typename Iter>
ReminderList::iterator_range::iterator_range(Iter begin, Iter end) : begin_(begin), end_(end) {}

template<typename Iter>
ReminderList::iterator_range::begin() const {
    return _begin;
}

template<typename Iter>
ReminderList::iterator_range::end() const {
    return _end;
}

ReminderList::ReminderList() {
    list = new QMap<unsigned int, std::unique_ptr<AbstractReminder>>();
    n_elem = 0;
}

ReminderList::ReminderList(const QMap<unsigned int, std::unique_ptr<AbstractReminder>>& map) : list(map), n_elem(map.size()) {}

ReminderList::ReminderList(const ReminderList& l) : list(l), n_elem(l.getNumElem()) {}

unsigned int ReminderList::getNumElem() const {
    return n_elem;
}

auto getReminders() {
    return iterator_range<QMap<T>::iterator>(list->begin(), list->end);
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

auto begin() {
    return list->begin();
}

auto end() {
    return list->end();
}



