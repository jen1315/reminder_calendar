#include "EditWidget.h"

#include <QFormLayout>
#include <QDateTimeEdit>
#include <QCheckBox>
#include "../model/Event.h"
#include "../model/Deadline.h"
#include "../model/Memo.h"
#include <iostream>

EditWidget::EditWidget(QWidget *parent) : QWidget(parent) {}

QWidget* EditWidget::getWidget() {
    return widget;
}

QMap<QString, QObject*>* EditWidget::getEdits() {
    return edits;
}

void EditWidget::visit(const Event *event) {
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

    QDateTime start, end;
    start.setDate(startDateEdit->date());
    end.setDate(endDateEdit->date());
    if(hasTimeEdit->isChecked()) {
        start.setTime(startTimeEdit->time());
        end.setTime(endTimeEdit->time());
    }
    edits = new QMap<QString, QObject*>();
    edits->insert("startDate", startDateEdit);
    edits->insert("startTime", startTimeEdit);
    edits->insert("endDate", endDateEdit);
    edits->insert("endTime", endTimeEdit);
    edits->insert("hasTime", hasTimeEdit);
}

void EditWidget::visit(const Deadline *deadline) {
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

    QDateTime date;
    date.setDate(dateEdit->date());
    if(hasTimeEdit->isChecked()) {
        date.setTime(timeEdit->time());
    }
    edits = new QMap<QString, QObject*>();
    edits->insert("date", dateEdit);
    edits->insert("time", timeEdit);
    edits->insert("hasTime", hasTimeEdit);
    edits->insert("done", doneEdit);
}

void EditWidget::visit(const Memo *memo) {
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
