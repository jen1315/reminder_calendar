#ifndef ADDVIEW_H
#define ADDVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include "./model/AbstractMedia.h"
#include "MediaWidget.h"

class AddView : public QWidget {
    Q_OBJECT

public:
    explicit AddView(QWidget *parent=nullptr);
    void clearLayout(QLayout* layout);
    
private:
    AbstractMedia *media;
    QVBoxLayout *layout;
    QVBoxLayout *detailLayout;

    QLineEdit *titleEdit;
    QLineEdit *yearEdit;
    QLineEdit *imgEdit;
    QTextEdit *descrEdit;
    QLineEdit *authorEdit;
    QLineEdit *langEdit;
    QLineEdit *directorEdit;
    QLineEdit *hourEdit;
    QLineEdit *minEdit;
    QLineEdit *magazEdit;

    QPushButton *submitButton;
    QRadioButton *bookButton;
    QRadioButton *filmButton;
    QRadioButton *articButton;

private slots:
    void toSubmit();

signals:
    void submitted(AbstractMedia*);
};

#endif
