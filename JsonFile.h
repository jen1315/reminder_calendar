#ifndef JSONFILE_H
#define JSONFILE_H

#include <QFile>
#include "./model/ReminderList.h"
#include "./model/ConstReminderVisitor.h"

class JsonFile : public ConstReminderVisitor {

public:
    JsonFile(const QString jsonUrl);

    ReminderList& getList();
    void erase(const unsigned int pos);
    void save(const AbstractReminder& r, bool isAdd);

    void visit(const Event *event);
    void visit(const Deadline *deadline);
    void visit(const Memo *memo);

private:
    QFile *file;
    ReminderList *list;
    QJsonObject obj;

};

#endif
