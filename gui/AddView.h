#ifndef ADDVIEW_H
#define ADDVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include "./model/AbstractReminder.h"
#include "ReminderWidget.h"

class AddView : public QWidget {
    Q_OBJECT

public:
    explicit AddView(QWidget *parent=nullptr);
    void clear();
    
private:
    AbstractReminder *reminder;
    QVBoxLayout *layout;
    QFormLayout *form;
    QFormLayout *detailForm;

    QLineEdit *titleEdit;
    QTextEdit *descrEdit;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QTimeEdit *startTimeEdit;
    QTimeEdit *endTimeEdit;
    QCheckBox *timeEdit;
    QCheckBox *doneEdit;

    QHBoxLayout *buttons;
    QPushButton *submitButton;
    QRadioButton *eventButton;
    QRadioButton *deadlineButton;
    QRadioButton *memoButton;
    QLabel *errorLabel;

private slots:
    void toSubmit();
    void printError(QString error);

signals:
    void submitted(AbstractReminder*);
    void error(QString);
};

#endif
