#include "EditView.h"

#include <QFormLayout>
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
    Util::clearLayout(detailLayout);
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

    QMap<QString, QLineEdit*> *edits = visitor->getEdits();
    if(dynamic_cast<Event*>(reminder)) {
        Event *e = static_cast<Event*>(reminder);
        e->setStartDate((*edits)["startDate"]->dateTime());
        e->setEndDate((*edits)["endDate"]->dateTime());
        e->setHasTime((*edits)["hasTime"]);
    }
    if(dynamic_cast<Deadline*>(reminder)) {
        Deadline *d = static_cast<Deadline*>(reminder);
        d->setDate((*edits)["date"]->dateTime());
        d->setHasTime((*edits)["hasTime"]);
    }
    if(dynamic_cast<Memo*>(reminder)) {
        Memo *m = static_cast<Memo*>(reminder);
        m->setIsDone((*edits)["done"]);
    }
    qDeleteAll(*edits);
    edits->clear();
    
    emit submitted(reminder);
}
