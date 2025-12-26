#include "EditView.h"

#include <QFormLayout>
#include "../model/Utilities.h"
#include "../model/Book.h"
#include "../model/Film.h"
#include "../model/Article.h"

EditView::EditView(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout();
    titleEdit = new QLineEdit(this);
    yearEdit = new QLineEdit(this);
    imgEdit = new QLineEdit(this);
    descrEdit = new QTextEdit(this);
    submitButton = new QPushButton("Submit", this);
    detailLayout = new QVBoxLayout();

    QFormLayout *form = new QFormLayout();
    form->addRow("Title:", titleEdit);
    form->addRow("Year:", yearEdit);
    form->addRow("Image path:", imgEdit);
    form->addRow("Description:", descrEdit);
    
    layout->addLayout(form);
    layout->addLayout(detailLayout);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &EditView::toSubmit);

    setLayout(layout);
}

void EditView::setMedia(AbstractReminder& m) {
    Util::clearLayout(detailLayout);
    reminder = &m;
    titleEdit->setText(m.getTitle());
    yearEdit->setText(QString::number(m.getYear()));
    imgEdit->setText(m.getImg());
    descrEdit->setText(m.getDescr());

    visitor = new ReminderWidget();
    m.acceptEdit(visitor);
    detailLayout->addWidget(visitor->getWidget());
}

void EditView::toSubmit() {
    reminder->setTitle(titleEdit->text());
    reminder->setYear((yearEdit->text()).toInt());
    reminder->setDescr(descrEdit->toPlainText());
    reminder->setImg(imgEdit->text());

    QMap<QString, QLineEdit*> *edits = visitor->getEdits();
    if(dynamic_cast<Book*>(reminder)) {
        Book *b = static_cast<Book*>(reminder);
        b->setAuthor((*edits)["author"]->text());
        b->setLanguage((*edits)["language"]->text());
    }
    if(dynamic_cast<Film*>(reminder)) {
        Film *f = static_cast<Film*>(reminder);
        f->setDirector((*edits)["director"]->text());
        int h = ((*edits)["hours"]->text()).toInt();
        int m = ((*edits)["minutes"]->text()).toInt();
        f->setTotMinutes(h*60+m);
    }
    if(dynamic_cast<Article*>(reminder)) {
        Article *a = static_cast<Article*>(reminder);
        a->setAuthor((*edits)["author"]->text());
        a->setMagazine((*edits)["magazine"]->text());
    }
    qDeleteAll(*edits);
    edits->clear();
    
    emit submitted(reminder);
}
