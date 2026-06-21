#include "ListWidget.h"

#include <QLabel>
#include <QHBoxLayout>
#include "../model/Event.h"
#include "../model/Deadline.h"
#include "../model/Memo.h"

ListWidget::ListWidget(QWidget *parent) : QWidget(parent) {}

QWidget* ListWidget::getWidget() {
    return widget;
}

void ListWidget::visit(const Event *event) {
    widget = new QWidget(this);
    QLabel *dateLabel = new QLabel(event->getStartDate().toString("dd/MM/yyyy") +" to "+ event->getEndDate().toString("dd/MM/yyyy"), widget);
    
    QFont font = dateLabel->font();
    font.setPointSize(8);
    dateLabel->setFont(font);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(dateLabel);
    widget->setLayout(layout);
}

void ListWidget::visit(const Deadline *deadline) {
    widget = new QWidget(this);
    QLabel *dateLabel = new QLabel(deadline->getDate().toString("dd/MM/yyyy"), widget);
    QString isDone = deadline->getIsDone()?"done":"not done";
    QLabel *doneLabel = new QLabel(isDone, widget);
    
    QFont font = doneLabel->font();
    font.setPointSize(8);
    dateLabel->setFont(font);
    doneLabel->setFont(font);
    
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(dateLabel);
    layout->addWidget(doneLabel);
    widget->setLayout(layout);
}

void ListWidget::visit(const Memo *memo) {
    widget = new QWidget(this);
    QString isDone = memo->getIsDone()?"done":"not done";
    QLabel *doneLabel = new QLabel(isDone, widget);
    
    QFont font = doneLabel->font();
    font.setPointSize(8);
    doneLabel->setFont(font);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(doneLabel);
    widget->setLayout(layout);
}