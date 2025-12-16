#ifndef REMINDERLIST_VIEW_H
#define REMINDERLIST_VIEW_H

#include <QWidget>
#include <QMap>
#include <QListWidget>
#include <QPushButton>
#include "../model/AbstractMReminder.h"


class ReminderListView : public QWidget {
    Q_OBJECT

public:
    explicit ReminderListView(QWidget *parent=nullptr);
    void displayReminderList(QMap<int, AbstractReminder*>& list);
    AbstractReminder& getReminder(int id);
    QMap<int, AbstractReminder*>& getReminderList() const;
    void setReminder(AbstractReminder& reminder);
    void addReminder(AbstractReminder& reminder);
    void clear();

private:
    QMap<int, AbstractReminder*> *list;
    QListWidget *listWidget;
    QPushButton *addButton;

private slots:
    void removeReminder();

signals:
    void reminderSelected(QListWidgetItem* item);
    void addClicked();

};

#endif
