#ifndef EDITVIEW_H
#define EDITVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include "./model/AbstractReminder.h"
#include "ReminderWidget.h"

class EditView : public QWidget {
    Q_OBJECT

public:
    explicit EditView(QWidget *parent=nullptr);
    void setReminder(AbstractReminder& reminder);
    void setAdd();
    
private:
    AbstractReminder *reminder;
    ReminderWidget *visitor;
    QVBoxLayout *layout;
    QLineEdit *titleEdit;
    QTextEdit *descrEdit;
    QPushButton *submitButton;
    QVBoxLayout *detailLayout;

private slots:
    void toSubmit();

signals:
    void submitted(AbstractReminder*);
};

#endif
