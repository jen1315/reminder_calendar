#include "EditView.h"

#include <QFormLayout>
#include <QDateTimeEdit>
#include <QCheckBox>
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
    ReminderWidget::clearLayout(detailLayout);
    reminder = &m;
    titleEdit->setText(m.getTitle());
    descrEdit->setText(m.getDescr());

    visitor = new ReminderWidget();
    m.acceptEdit(visitor);
    detailLayout->addWidget(visitor->getWidget());
}

void EditView::toSubmit() {
    reminder->setTitle(titleEdit->text());
    reminder->setDescr(descrEdit->toPlainText());

    QMap<QString, QObject*> *edits = visitor->getEdits();
    if(dynamic_cast<Event*>(reminder)) {
        Event *e = static_cast<Event*>(reminder);
        QDateTime start, end;
        bool hasTime = static_cast<QCheckBox*>((*edits)["hasTime"])->isChecked();
        start.setDate(static_cast<QDateEdit*>((*edits)["startDate"])->date());
        end.setDate(static_cast<QDateEdit*>((*edits)["endDate"])->date());
        if(hasTime) {
            start.setTime(static_cast<QTimeEdit*>((*edits)["startTime"])->time());
            end.setTime(static_cast<QTimeEdit*>((*edits)["endTime"])->time());
        }
        e->setStartDate(start);
        e->setEndDate(end);
        e->setHasTime(hasTime);
    }
    if(dynamic_cast<Deadline*>(reminder)) {
        Deadline *d = static_cast<Deadline*>(reminder);
        QDateTime date;
        bool hasTime = static_cast<QCheckBox*>((*edits)["hasTime"])->isChecked();
        date.setDate(static_cast<QDateEdit*>((*edits)["date"])->date());
        if(hasTime)
            date.setTime(static_cast<QTimeEdit*>((*edits)["time"])->time());
        d->setDate(date);
        d->setHasTime(hasTime);
        d->setIsDone(static_cast<QCheckBox*>((*edits)["done"])->isChecked());
    }
    if(dynamic_cast<Memo*>(reminder)) {
        Memo *m = static_cast<Memo*>(reminder);
        m->setIsDone(static_cast<QCheckBox*>((*edits)["done"])->isChecked());
    }
    qDeleteAll(*edits);
    edits->clear();
    
    emit submitted(reminder);
}
