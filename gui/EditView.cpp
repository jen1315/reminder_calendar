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

void EditView::setMedia(AbstractMedia& m) {
    Util::clearLayout(detailLayout);
    media = &m;
    titleEdit->setText(m.getTitle());
    yearEdit->setText(QString::number(m.getYear()));
    imgEdit->setText(m.getImg());
    descrEdit->setText(m.getDescr());

    visitor = new MediaWidget();
    m.acceptEdit(visitor);
    detailLayout->addWidget(visitor->getWidget());
}

void EditView::toSubmit() {
    media->setTitle(titleEdit->text());
    media->setYear((yearEdit->text()).toInt());
    media->setDescr(descrEdit->toPlainText());
    media->setImg(imgEdit->text());

    QMap<QString, QLineEdit*> *edits = visitor->getEdits();
    if(dynamic_cast<Book*>(media)) {
        Book *b = static_cast<Book*>(media);
        b->setAuthor((*edits)["author"]->text());
        b->setLanguage((*edits)["language"]->text());
    }
    if(dynamic_cast<Film*>(media)) {
        Film *f = static_cast<Film*>(media);
        f->setDirector((*edits)["director"]->text());
        int h = ((*edits)["hours"]->text()).toInt();
        int m = ((*edits)["minutes"]->text()).toInt();
        f->setTotMinutes(h*60+m);
    }
    if(dynamic_cast<Article*>(media)) {
        Article *a = static_cast<Article*>(media);
        a->setAuthor((*edits)["author"]->text());
        a->setMagazine((*edits)["magazine"]->text());
    }
    qDeleteAll(*edits);
    edits->clear();
    
    emit submitted(media);
}
