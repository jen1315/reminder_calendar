#ifndef REMINDERVIEW_H
#define REMINDERVIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "../model/AbstractReminder.h"
#include "ReminderWidget.h"

class ReminderView : public QWidget {
    Q_OBJECT

public:
    explicit ReminderView(QWidget *parent = nullptr);
    void displayReminder(AbstractReminder& m);
    AbstractReminder& getReminder() const;

private:
    AbstractReminder *reminder;
    QVBoxLayout *layout;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QLabel *titleLabel;
    QLabel *descrLabel;
    QVBoxLayout *visitLayout;

private slots:
    void toDelete();

signals:
    void toEdit();
    void deleted(unsigned int);
    
};

#endif
