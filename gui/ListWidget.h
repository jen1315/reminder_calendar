#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include "../model/ConstReminderVisitor.h"

class ListWidget: public QWidget, public ConstReminderVisitor {
    Q_OBJECT

public:
    ListWidget(QWidget *parent=nullptr);
    QWidget *getWidget();

    void visit(const Event *event);
    void visit(const Deadline *deadline);
    void visit(const Memo *memo);

private:
    QWidget *widget;
};

#endif