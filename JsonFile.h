#ifndef JSONFILE_H
#define JSONFILE_H

#include <QFile>
#include "./model/ReminderList.h"

class JsonFile {

public:
    JsonFile(const QString jsonUrl);

    ReminderList& getList();
    void erase(const unsigned int pos);
    void save(const AbstractReminder& r, bool isAdd);

private:
    QFile *file;
    ReminderList *list;

};

#endif
