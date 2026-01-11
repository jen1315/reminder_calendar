#include "ReminderWidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include "../model/Event.h"
#include "../model/Deadline.h"
#include "../model/Memo.h"

ReminderWidget::ReminderWidget(QWidget *parent) : QWidget(parent) {}

QWidget* ReminderWidget::getWidget() {
    return widget;
}

QMap<QString, QLineEdit*>* ReminderWidget::getEdits() {
    return edits;
}

void ReminderWidget::visit(const Event *event) {
    widget = new QWidget(this);
    QLabel *startLabel = new QLabel("Start: "+ event->getStartDate().toString("d ddd MMMM yyyy"), widget);
    QLabel *endLabel = new QLabel("End: "+ event->getEndDate().toString("d ddd MMMM yyyy"), widget);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(startLabel);
    layout->addWidget(endLabel);
    widget->setLayout(layout);
}

void ReminderWidget::visit(const Deadline *deadline) {
    widget = new QWidget(this);
    QLabel *directLabel = new QLabel("Director :" + deadline->getDirector(), widget);
    QLabel *lengthLabel = new QLabel("Length :" + QString::number(deadline->getHours()) + "h " + QString::number(deadline->getMinutes()) + "min", widget);

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

void ReminderWidget::visitEdit(const Event *event) {
    widget = new QWidget(this);
    QStartEdit *startDateEdit = new QLineEdit(event->getStartDate(), widget);
    QLineEdit *langDateEdit = new QLineEdit(book->getEndDate(), widget);

    QFormLayout *form = new QFormLayout();
    form->addRow("Author:", authorEdit);
    form->addRow("Language:", langEdit);
    widget->setLayout(form);

    edits = new QMap<QString, QLineEdit*>();
    edits->insert("startDate", startDateEdit);
    edits->insert("endDate", endDateEdit);
}

void ReminderWidget::visitEdit(const Event *event) {
    widget = new QWidget(this);
    QLineEdit *startEdit = new QLineEdit(event->getStartDate(), widget);
    QLineEdit *endEdit = new QLineEdit(QString::number(event->getEndDate()), widget);
    QLineEdit *timeEdit = new QLineEdit(QString::number(event->getHasTime()), widget);

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
