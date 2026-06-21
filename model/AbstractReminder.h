#ifndef ABSTRACTREMINDER_H
#define ABSTRACTREMINDER_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include "ReminderVisitor.h"
#include "ConstReminderVisitor.h"

class AbstractReminder {

public:
    AbstractReminder(const unsigned int id, const QString title, const QString descr);
    AbstractReminder(const AbstractReminder& r);
    AbstractReminder() = default;
    virtual ~AbstractReminder() = default;

    unsigned int getId() const;
    QString getTitle() const;
    QString getDescr() const;

    void setId(const unsigned int);
    void setTitle(const QString title);
    void setDescr(const QString descr);

    virtual void accept(ReminderVisitor *visitor) = 0;
    virtual void accept(ConstReminderVisitor *visitor) const = 0;

protected:
    unsigned int id;
    QString title;
    QString description;
};

#endif
