#ifndef REMINDERLISTVIEW_H
#define REMINDERLISTVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "../model/ReminderList.h"

class ListView : public QWidget {
    Q_OBJECT

public:
    explicit ListView(QWidget *parent=nullptr);
    void displayReminderList(const ReminderList& list);
    ReminderList& searchReminders(const QString text) const;
    ReminderList& getRemindersByDate(const QDate& date) const;
    AbstractReminder& getReminder(const unsigned int id) const;

    ReminderList& getReminderList() const;
    unsigned int getSize() const;
    
    void insertReminder(AbstractReminder& reminder);
    void removeReminder(unsigned int id);
    void clear();

private:
    ReminderList *list;
    QListWidget *listWidget;
    QPushButton *addButton;

signals:
    void reminderSelected(QListWidgetItem* item);
    void addClicked();

};

#endif
