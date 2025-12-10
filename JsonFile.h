#ifndef JSONFILE_H
#define JSONFILE_H

#include <QFile>
#include "./model/AbstractReminder.h"

class JsonFile {

public:
    JsonFile(const QString jsonUrl);
    QMap<int, AbstractReminder*>& getMap() const;
    void submitChanges(int id) const;

private:
    QFile *file;
    QMap<int, AbstractReminder*> *calendar;

};

#endif
