#ifndef REMINDERWIDGET_H
#define REMINDERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include "../model/ReminderVisitor.h"

class ReminderWidget: public QWidget, public ReminderVisitor {
    Q_OBJECT

public:
    ReminderWidget(QWidget *parent=nullptr);
    QWidget *getWidget();
    QMap<QString, QLineEdit*> *getEdits();

    void visit(const Event *event);
    void visit(const Deadline *deadline);
    void visit(const Memo *memo);

    void visitEdit(const Event *event);
    void visitEdit(const Deadline *deadline);
    void visitEdit(const Memo *memo);

private:
    QWidget *widget;
    QMap<QString, QLineEdit*> *edits;
};

#endif
