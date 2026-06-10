#include "ReminderWidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QDateTimeEdit>
#include <QCheckBox>
#include <QFormLayout>
#include "../model/Event.h"
#include "../model/Deadline.h"
#include "../model/Memo.h"

ReminderWidget::ReminderWidget(QWidget *parent) : QWidget(parent) {}

QWidget* ReminderWidget::getWidget() {
    return widget;
}

QMap<QString, QObject*>* ReminderWidget::getEdits() {
    return edits;
}

void ReminderWidget::visit(const Event *event) {
    widget = new QWidget(this);
    QLabel *startLabel = new QLabel("Starts: "+ event->getStartDate().toString("d ddd MMMM yyyy"), widget);
    QLabel *endLabel = new QLabel("Ends: "+ event->getEndDate().toString("d ddd MMMM yyyy"), widget);
    QLabel *startTimeLabel = new QLabel(widget);
    QLabel *endTimeLabel = new QLabel(widget);
    if(event->getHasTime()) {
        startTimeLabel->setText("at: "+ event->getStartDate().toString("hh:mm:ss"));
        endTimeLabel->setText("at: "+ event->getEndDate().toString("hh:mm:ss"));
    }

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(startLabel);
    layout->addWidget(startTimeLabel);
    layout->addWidget(endLabel);
    layout->addWidget(endTimeLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visit(const Deadline *deadline) {
    widget = new QWidget(this);
    QLabel *dateLabel = new QLabel("Date: " + deadline->getDate().toString("d ddd MMMM yyyy"), widget);
    QLabel *timeLabel = new QLabel(widget);
    QString isDone = deadline->getIsDone()?"Yes":"No";
    QLabel *doneLabel = new QLabel("Is it done? " + isDone, widget);
    if(deadline->getHasTime())
        timeLabel->setText("at: "+ deadline->getDate().toString("hh:mm:ss"));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(dateLabel);
    layout->addWidget(timeLabel);
    layout->addWidget(doneLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visit(const Memo *memo) {
    widget = new QWidget(this);
    QString isDone = memo->getIsDone()?"Yes":"No";
    QLabel *doneLabel = new QLabel("Is it done? " + isDone, widget);
    
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(doneLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visitEdit(const Event *event) {
    widget = new QWidget(this);
    QDateEdit *startDateEdit = new QDateEdit(event->getStartDate().date(), widget);
    QTimeEdit *startTimeEdit = new QTimeEdit(event->getStartDate().time(), widget);
    QDateEdit *endDateEdit = new QDateEdit(event->getEndDate().date(), widget);
    QTimeEdit *endTimeEdit = new QTimeEdit(event->getEndDate().time(), widget);
    QCheckBox *hasTimeEdit = new QCheckBox(widget);
    if(event->getHasTime())
        hasTimeEdit->setCheckState(Qt::Checked);
    else
        hasTimeEdit->setCheckState(Qt::Unchecked);
    
    QFormLayout *form = new QFormLayout();
    form->addRow("Starts: ", startDateEdit);
    form->addRow("at: ", startTimeEdit);
    form->addRow("Ends: ", endDateEdit);
    form->addRow("at: ", endTimeEdit);
    form->addRow("Does it have time? ", hasTimeEdit);
    widget->setLayout(form);

    edits = new QMap<QString, QObject*>();
    edits->insert("startDate", startDateEdit);
    edits->insert("startTime", startTimeEdit);
    edits->insert("endDate", endDateEdit);
    edits->insert("endTime", endTimeEdit);
    edits->insert("hasTime", hasTimeEdit);
}

void ReminderWidget::visitEdit(const Deadline *deadline) {
    widget = new QWidget(this);
    QDateEdit *dateEdit = new QDateEdit(deadline->getDate().date(), widget);
    QTimeEdit *timeEdit = new QTimeEdit(deadline->getDate().time(), widget);
    QCheckBox *hasTimeEdit = new QCheckBox(widget);
    QCheckBox *doneEdit = new QCheckBox(widget);
    if(deadline->getHasTime())
        hasTimeEdit->setChecked(true);
    else
        hasTimeEdit->setChecked(false);
    if(deadline->getIsDone())
        doneEdit->setChecked(true);
    else
        doneEdit->setChecked(false);
    QFormLayout *form = new QFormLayout();
    form->addRow("Date:", dateEdit);
    form->addRow("Time:", timeEdit);
    form->addRow("Does it have time? ", hasTimeEdit);
    form->addRow("Is it done? ", doneEdit);
    widget->setLayout(form);

    edits = new QMap<QString, QObject*>();
    edits->insert("date", dateEdit);
    edits->insert("time", timeEdit);
    edits->insert("hasTime", hasTimeEdit);
    edits->insert("done", doneEdit);
}

void ReminderWidget::visitEdit(const Memo *memo) {
    widget = new QWidget(this);
    QCheckBox *doneEdit = new QCheckBox(widget);
    if(memo->getIsDone())
        doneEdit->setChecked(true);
    else
        doneEdit->setChecked(false);
    
    QFormLayout *form = new QFormLayout();
    form->addRow("Is it done? ", doneEdit);
    widget->setLayout(form);

    edits = new QMap<QString, QObject*>();
    edits->insert("done", doneEdit);
}

void ReminderWidget::clearLayout(QLayout *layout) {
    if(!layout)
        return ;

    QLayout *subLayout;
    QWidget *widget = new QWidget();
    while(QLayoutItem *item = layout->takeAt(0)) {
        if(widget = item->widget())
            delete widget;
        else if(subLayout = item->layout())
            clearLayout(subLayout);
        delete item;
    }
}