#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QMainWindow>
#include <QStackedWidget>
#include "ListView.h"
#include "ReminderView.h"
#include "EditView.h"
#include "AddView.h"
#include "JsonFile.h"
#include "CalendarView.h"

class ViewManager : public QMainWindow {
    Q_OBJECT

public:
    explicit ViewManager(QString file, QWidget *parent=nullptr);
    
private:
    JsonFile *json;
    QStackedWidget *stackWidget;
    QPushButton *homeButton;
    QLineEdit *searchBar;
    QPushButton *searchButton;

    ListView *nextView;
    ListView *memoView;
    ListView *searchView;
    ReminderView *reminderView;
    EditView *editView;
    AddView *addView;
    CalendarView *calendarView;

private slots:
    void viewReminder(QListWidgetItem* item);
    void viewSearch();
    void viewSearchSelected(QDate date);
    void viewAdd();
    void viewEdit();
    void editReminder(AbstractReminder* reminder);
    void addReminder(AbstractReminder* reminder);
    void deleteReminder(unsigned int id);
    void switchHome();
};

#endif
