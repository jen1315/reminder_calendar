#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QWidget>
#include "../model/ConstReminderVisitor.h"

class EditWidget : public QWidget, public ConstReminderVisitor {
    Q_OBJECT

public:
    explicit EditWidget(QWidget *parent=nullptr);
    QWidget *getWidget();
    QMap<QString, QObject*>* getEdits();

    void visit(const Event *event);
    void visit(const Deadline *deadline);
    void visit(const Memo *memo);
    
private:
    QMap<QString, QObject*> *edits;
    QWidget *widget;

};

#endif