#include "EditView.h"

#include <QFormLayout>
#include <QDateTimeEdit>
#include <QCheckBox>
#include "Utilities.h"
#include "../model/Event.h"
#include "../model/Deadline.h"
#include "../model/Memo.h"

EditView::EditView(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout();
    titleEdit = new QLineEdit(this);
    descrEdit = new QTextEdit(this);
    submitButton = new QPushButton("Submit", this);
    detailLayout = new QVBoxLayout();

    QFormLayout *form = new QFormLayout();
    form->addRow("Title:", titleEdit);
    form->addRow("Description:", descrEdit);
    
    layout->addLayout(form);
    layout->addLayout(detailLayout);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &EditView::toSubmit);

    setLayout(layout);
}

void EditView::setReminder(AbstractReminder& m) {
    Utilities::clearLayout(detailLayout);
    reminder = &m;
    titleEdit->setText(m.getTitle());
    descrEdit->setText(m.getDescr());

    visitor = new EditWidget();
    m.accept(visitor);
    detailLayout->addWidget(visitor->getWidget());
}

void EditView::toSubmit() {
    reminder->setTitle(titleEdit->text());
    reminder->setDescr(descrEdit->toPlainText());

    edits = visitor->getEdits();
    reminder->accept(this);
    qDeleteAll(*edits);
    edits->clear();

    emit submitted(reminder);
}

void EditView::visit(Event* event) {
    QDateTime start, end;
    bool hasTime = static_cast<QCheckBox*>((*edits)["hasTime"])->isChecked();
    start.setDate(static_cast<QDateEdit*>((*edits)["startDate"])->date());
    end.setDate(static_cast<QDateEdit*>((*edits)["endDate"])->date());
    if(hasTime) {
        start.setTime(static_cast<QTimeEdit*>((*edits)["startTime"])->time());
        end.setTime(static_cast<QTimeEdit*>((*edits)["endTime"])->time());
    }
    event->setStartDate(start);
    event->setEndDate(end);
    event->setHasTime(hasTime);
}

void EditView::visit(Deadline *deadline) {
    QDateTime date;
    bool hasTime = static_cast<QCheckBox*>((*edits)["hasTime"])->isChecked();
    date.setDate(static_cast<QDateEdit*>((*edits)["date"])->date());
    if(hasTime)
        date.setTime(static_cast<QTimeEdit*>((*edits)["time"])->time());
    deadline->setDate(date);
    deadline->setHasTime(hasTime);
    deadline->setIsDone(static_cast<QCheckBox*>((*edits)["done"])->isChecked());
}

void EditView::visit(Memo *memo) {
    memo->setIsDone(static_cast<QCheckBox*>((*edits)["done"])->isChecked());
}