#include "ReminderWidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include "../model/Book.h"
#include "../model/Film.h"
#include "../model/Article.h"

ReminderWidget::ReminderWidget(QWidget *parent) : QWidget(parent) {}

QWidget* ReminderWidget::getWidget() {
    return widget;
}

QMap<QString, QLineEdit*>* ReminderWidget::getEdits() {
    return edits;
}

void ReminderWidget::visit(const Book *book) {
    widget = new QWidget(this);
    QLabel *authorLabel = new QLabel("Author: "+ book->getAuthor(), widget);
    QLabel *langLabel = new QLabel("Language: "+ book->getLanguage(), widget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(authorLabel);
    layout->addWidget(langLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visit(const Film *film) {
    widget = new QWidget(this);
    QLabel *directLabel = new QLabel("Director :" + film->getDirector(), widget);
    QLabel *lengthLabel = new QLabel("Length :" + QString::number(film->getHours()) + "h " + QString::number(film->getMinutes()) + "min", widget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(directLabel);
    layout->addWidget(lengthLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visit(const Article *article) {
    widget = new QWidget(this);
    QLabel *authorLabel = new QLabel("Author: " + article->getAuthor(), widget);
    QLabel *magLabel = new QLabel("Magazine: " + article->getMagazine(), widget);
    
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(authorLabel);
    layout->addWidget(magLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visitEdit(const Book *book) {
    widget = new QWidget(this);
    QLineEdit *authorEdit = new QLineEdit(book->getAuthor(), widget);
    QLineEdit *langEdit = new QLineEdit(book->getLanguage(), widget);

    QFormLayout *form = new QFormLayout();
    form->addRow("Author:", authorEdit);
    form->addRow("Language:", langEdit);
    widget->setLayout(form);

    edits = new QMap<QString, QLineEdit*>();
    edits->insert("author", authorEdit);
    edits->insert("language", langEdit);
}

void ReminderWidget::visitEdit(const Film *film) {
    widget = new QWidget(this);
    QLineEdit *directEdit = new QLineEdit(film->getDirector(), widget);
    QLineEdit *hourEdit = new QLineEdit(QString::number(film->getHours()), widget);
    QLineEdit *minEdit = new QLineEdit(QString::number(film->getMinutes()), widget);

    QFormLayout *form = new QFormLayout();
    form->addRow("Director:", directEdit);
    form->addRow("Hours:", hourEdit);
    form->addRow("Minutes:", minEdit);
    widget->setLayout(form);

    edits = new QMap<QString, QLineEdit*>();
    edits->insert("director", directEdit);
    edits->insert("hours", hourEdit);
    edits->insert("minutes", minEdit);
}

void ReminderWidget::visitEdit(const Article *article) {
    widget = new QWidget(this);
    QLineEdit *authorEdit = new QLineEdit(article->getAuthor(), widget);
    QLineEdit *magEdit = new QLineEdit(article->getMagazine(), widget);

    QFormLayout *form = new QFormLayout();
    form->addRow("Author:", authorEdit);
    form->addRow("Magazine:", magEdit);
    widget->setLayout(form);

    edits = new QMap<QString, QLineEdit*>();
    edits->insert("author", authorEdit);
    edits->insert("magazine", magEdit);
}
