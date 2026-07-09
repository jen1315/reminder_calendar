#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <QMainWindow>
#include <QStackedWidget>
#include "ListView.h"
#include "ReminderView.h"
#include "EditView.h"
#include "AddView.h"
#include "CalendarView.h"
#include "JsonFile.h"

class ViewManager : public QMainWindow {
    Q_OBJECT

public:
    explicit ViewManager(QWidget *parent=nullptr);
    void loadReminders(QString fileName);
    
private:
    JsonFile *json;
    QStackedWidget *stackWidget;
    QLineEdit *searchBar;
    QPushButton *searchButton;
    QPushButton *homeButton;
    QPushButton *importButton;
    QPushButton *newButton;

    ListView *nextView;
    ListView *memoView;
    ListView *searchView;
    ReminderView *reminderView;
    EditView *editView;
    AddView *addView;
    CalendarView *calendarView;

private slots:
    void newFile();
    void loadFile();
    void viewReminder(QListWidgetItem* item);
    void viewSearch();
    void viewSearchSelected(QDate date);
    void viewAdd();
    void viewEdit();
    void switchHome();
    void editReminder(AbstractReminder* reminder);
    void addReminder(AbstractReminder* reminder);
    void deleteReminder(unsigned int id);
};

#endif
