#ifndef ADDVIEW_H
#define ADDVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include "./model/AbstractReminder.h"
#include "ReminderWidget.h"

class AddView : public QWidget {
    Q_OBJECT

public:
    explicit AddView(QWidget *parent=nullptr);
    void clearLayout(QLayout* layout);
    
private:
    AbstractReminder *reminder;
    QVBoxLayout *layout;
    QVBoxLayout *detailLayout;

    QLineEdit *titleEdit;
    QTextEdit *descrEdit;
    QLineEdit *startDateEdit;
    QLineEdit *endDateEdit;
    QLineEdit *startTimeEdit;
    QLineEdit *endTimeEdit;
    QLineEdit *doneEdit;

    QPushButton *submitButton;
    QRadioButton *eventButton;
    QRadioButton *deadlineButton;
    QRadioButton *memoButton;

private slots:
    void toSubmit();

signals:
    void submitted(AbstractReminder*);
};

#endif
