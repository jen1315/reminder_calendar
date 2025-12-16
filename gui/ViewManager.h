#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include "ReminderListView.h"
#include "ReminderView.h"
#include "EditView.h"
#include "AddView.h"

class ViewManager : public QMainWindow {
    Q_OBJECT

public:
    explicit ViewManager(QWidget *parent=nullptr);
    void setReminders(QMap<int, AbstractReminder*>& list);
    
private:
    QStackedWidget *stackWidget;
    QPushButton *homeButton;
    QLineEdit *searchBar;
    QPushButton *searchButton;

    ReminderListView *memoView;
    ReminderView *reminderView;
    ReminderListView *todayView;
    EditView *editView;
    AddView *addView;

private slots:
    void viewReminder(QListWidgetItem* item);
    void viewSearch();
    void viewEdit();
    void viewAdd();
    void submitReminder(AbstractReminder* reminder);
    void addReminder(AbstractReminder* reminder);
    void switchHome();
};

#endif
