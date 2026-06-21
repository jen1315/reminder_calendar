#ifndef EDITVIEW_H
#define EDITVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include "EditWidget.h"
#include "../model/AbstractReminder.h"
#include "../model/ReminderVisitor.h"

class EditView : public QWidget, public ReminderVisitor {
    Q_OBJECT

public:
    explicit EditView(QWidget *parent=nullptr);
    void setReminder(AbstractReminder& r);

    void visit(Event *event);
    void visit(Deadline *deadline);
    void visit(Memo *memo);
    
private:
    AbstractReminder *reminder;
    EditWidget* visitor;
    QMap<QString, QObject*> *edits;

    QVBoxLayout *layout;
    QLineEdit *titleEdit;
    QTextEdit *descrEdit;
    QPushButton *submitButton;
    QVBoxLayout *detailLayout;

private slots:
    void toSubmit();

signals:
    void submitted(AbstractReminder*);
};

#endif
