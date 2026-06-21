#include "AddView.h"

#include "../model/Event.h"
#include "../model/Deadline.h"
#include "../model/Memo.h"

AddView::AddView(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout();
    titleEdit = new QLineEdit(this);
    descrEdit = new QTextEdit(this);
    startDateEdit = new QDateEdit(this);
    startTimeEdit = new QTimeEdit(this);
    endDateEdit = new QDateEdit(this);
    endTimeEdit = new QTimeEdit(this);
    timeEdit = new QCheckBox(this);
    doneEdit = new QCheckBox(this);
    errorLabel = new QLabel(this);

    startDateEdit->setDate(QDate::currentDate());
    endDateEdit->setDate(QDate::currentDate());

    submitButton = new QPushButton("Submit", this);
    eventButton = new QRadioButton("Event", this);
    deadlineButton = new QRadioButton("Deadline", this);
    memoButton = new QRadioButton("Memo", this);

    form = new QFormLayout();
    form->addRow("Title:", titleEdit);
    form->addRow("Description:", descrEdit);
    
    buttons = new QHBoxLayout();
    buttons->addWidget(eventButton);
    buttons->addWidget(deadlineButton);
    buttons->addWidget(memoButton);
    
    detailForm = new QFormLayout();
    detailForm->addRow("Does it have time?", timeEdit);
    detailForm->addRow("From:", startDateEdit);
    detailForm->addRow("Time:", startTimeEdit);
    detailForm->addRow("To:", endDateEdit);
    detailForm->addRow("Time:", endTimeEdit);
    
    doneEdit->setLayoutDirection(Qt::RightToLeft);
    detailForm->addRow("Is it done?", doneEdit);

    layout->addLayout(form);
    layout->addLayout(buttons);
    layout->addLayout(detailForm);
    layout->addWidget(submitButton);
    layout->addWidget(errorLabel);

    connect(submitButton, &QPushButton::clicked, this, &AddView::toSubmit);
    connect(this, SIGNAL(error(QString)), this, SLOT(printError(QString)));
    setLayout(layout);    
}

void AddView::toSubmit() {
    if((titleEdit->text()).isEmpty())
        emit error(tr("The title is empty"));
    else {
        if(eventButton->isChecked()) {
            QDateTime startDate = startDateEdit->dateTime();
            startDate.setTime(startTimeEdit->time());
            QDateTime endDate = endDateEdit->dateTime();
            endDate.setTime(endTimeEdit->time());
            if(startDate > endDate) 
                emit error(tr("The start date is after the end date"));
            else {
                reminder = new Event(0, titleEdit->text(), descrEdit->toPlainText(), startDate, endDate, timeEdit->isChecked());
                emit submitted(reminder);
            }
        }
        if(deadlineButton->isChecked()) {
            QDateTime date = startDateEdit->dateTime();
            date.setTime(startTimeEdit->time());
            reminder = new Deadline(0, titleEdit->text(), descrEdit->toPlainText(), date, timeEdit->isChecked(), doneEdit->isChecked());
            emit submitted(reminder);
        }
        if(memoButton->isChecked()) {
            reminder = new Memo(0, titleEdit->text(), descrEdit->toPlainText(), doneEdit->isChecked());
            emit submitted(reminder);
        }
    }
}

void AddView::printError(QString error) {
    errorLabel->setText("<font color='pink'>"+ error+ "</font>");
}

void AddView::clear() {
    titleEdit->clear();
    descrEdit->clear();
    startDateEdit->clear();
    endDateEdit->clear();
    startTimeEdit->clear();
    endTimeEdit->clear();
    errorLabel->clear();
}