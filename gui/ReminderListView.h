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
    void displayReminderList(QMap<int, AbstractReminder*>& list);
    void setReminder(AbstractReminder& reminder);
    void clear();

private:
    ReminderList *list;
    QListWidget *listWidget;
    QPushButton *addButton;

private slots:
    void removeReminder();

signals:
    void reminderSelected(QListWidgetItem* item);
    void addClicked();

};

#endif
