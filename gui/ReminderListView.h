#ifndef REMINDERLIST_VIEW_H
#define REMINDERLIST_VIEW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "../model/ReminderList.h"


class ReminderListView : public QWidget {
    Q_OBJECT

public:
    explicit ReminderListView(QWidget *parent=nullptr);
    void displayReminderList(const ReminderList& list);
    ReminderList& searchReminders(const QString text) const;
    ReminderList& getRemindersByDate(const QDate& date) const;
    AbstractReminder& getReminder(const unsigned int id) const;
    unsigned int getCounter() const;
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
