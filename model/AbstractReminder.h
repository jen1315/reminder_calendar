#ifndef ABSTRACTREMINDER_H
#define ABSTRACTREMINDER_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include "ReminderVisitor.h"

class AbstractReminder {

public:
    AbstractReminder(unsigned int id, QString title, QString descr);
    AbstractReminder(AbstractReminder& r);

    unsigned int getId() const;
    QString getTitle() const;
    QString getDescr() const;

    void setId(unsigned int);
    void setTitle(QString title);
    void setDescr(QString descr);

    virtual void accept(ReminderVisitor *visitor) = 0;
    virtual void acceptEdit(ReminderVisitor *visitor) = 0;

    // virtual QJsonObject toJson() const = 0;

protected:
    unsigned int id;
    QString title;
    QString description;
};

#endif
