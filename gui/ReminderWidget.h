#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include "../model/MediaVisitor.h"

class MediaWidget: public QWidget, public MediaVisitor {
    Q_OBJECT

public:
    MediaWidget(QWidget *parent=nullptr);
    QWidget *getWidget();
    QMap<QString, QLineEdit*> *getEdits();

    void visit(const Book *book);
    void visit(const Film *film);
    void visit(const Article *article);

    void visitEdit(const Book *book);
    void visitEdit(const Film *film);
    void visitEdit(const Article *article);

private:
    QWidget *widget;
    QMap<QString, QLineEdit*> *edits;
};

#endif
