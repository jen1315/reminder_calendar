#include "AddView.h"

#include <QFormLayout>
#include "../model/Book.h"
#include "../model/Film.h"
#include "../model/Article.h"

AddView::AddView(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout();
    titleEdit = new QLineEdit(this);
    yearEdit = new QLineEdit(this);
    imgEdit = new QLineEdit(this);
    descrEdit = new QTextEdit(this);
    submitButton = new QPushButton("Submit", this);
    detailLayout = new QVBoxLayout();
    bookButton = new QRadioButton("Book", this);
    filmButton = new QRadioButton("Film", this);
    articButton = new QRadioButton("Article", this);

    QFormLayout *form = new QFormLayout();
    form->addRow("Title:", titleEdit);
    form->addRow("Year:", yearEdit);
    form->addRow("Image path:", imgEdit);
    form->addRow("Description:", descrEdit);
    
    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(bookButton);
    buttons->addWidget(filmButton);
    buttons->addWidget(articButton);
    
    QFormLayout *detailForm = new QFormLayout();
    QLineEdit *authorEdit = new QLineEdit(this);
    QLineEdit *langEdit = new QLineEdit(this);
    detailForm->addRow("Author", authorEdit);
    detailForm->addRow("Language", langEdit);
    QLineEdit *directorEdit = new QLineEdit(this);
    QLineEdit *hourEdit = new QLineEdit(this);
    QLineEdit *minEdit = new QLineEdit(this);
    detailForm->addRow("Director", directorEdit);
    detailForm->addRow("Hours", hourEdit);
    detailForm->addRow("Minutes", minEdit);
    QLineEdit *magazEdit = new QLineEdit();
    QLineEdit *author1Edit = new QLineEdit();
    detailForm->addRow("Author", author1Edit);
    detailForm->addRow("Magazine", magazEdit);

    layout->addLayout(form);
    layout->addLayout(buttons);
    layout->addLayout(detailForm);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &AddView::toSubmit);
    setLayout(layout);    
}

void AddView::toSubmit() {
    if(bookButton->isChecked())
        media = new Book(0, titleEdit->text(), (yearEdit->text()).toInt(), descrEdit->toPlainText(), imgEdit->text(), authorEdit->text(), langEdit->text());
    if(filmButton->isChecked()) {
        int h = (hourEdit->text()).toInt();
        int m = (minEdit->text()).toInt();
        media = new Film(0, titleEdit->text(), (yearEdit->text()).toInt(), descrEdit->toPlainText(), imgEdit->text(), directorEdit->text(), h*60+m);
    }
    if(articButton->isChecked()) {
        media = new Article(0, titleEdit->text(), (yearEdit->text()).toInt(), descrEdit->toPlainText(), imgEdit->text(), authorEdit->text(), magazEdit->text());
    }

    emit submitted(media);
}
