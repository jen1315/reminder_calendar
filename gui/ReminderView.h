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
    void clearLayout(QLayout* layout);

private:
    AbstractReminder *reminder;
    QVBoxLayout *layout;
    QPushButton *editButton;
    QLabel *titleLabel;
    QLabel *descrLabel;
    QVBoxLayout *visitLayout;

signals:
    void toEdit();
    
};

#endif
