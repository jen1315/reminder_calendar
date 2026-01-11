#include "MediaView.h"
#include "../model/Utilities.h"

MediaView::MediaView(QWidget *parent) : QWidget(parent) {
    titleLabel = new QLabel();
    descrLabel = new QLabel();
    visitLayout = new QVBoxLayout();
    layout = new QVBoxLayout();

    titleLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    descrLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QPixmap image("../img/save.png");
    QPixmap scaled = image.scaled(QSize(50, 50), Qt::KeepAspectRatio);
    QLabel *imageEdit = new QLabel();
    imageEdit->setPixmap(scaled);
    
    editButton = new QPushButton("Edit");
    
    QHBoxLayout *hlayout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout();

    hlayout->addWidget(image)    
    
    vlayout->addWidget(editButton);
    vlayout->addWidget(titleLabel);
    vlayout->addWidget(descrLabel);
    vlayout->addLayout(visitLayout);

    layout->addLayout(vlayout);

    connect(editButton, &QPushButton::clicked, this, &MediaView::toEdit);

    setLayout(layout);
}

void MediaView::displayReminder(AbstractReminder& m) {
    Util::clearLayout(visitLayout);
    reminder = &m;
    titleLabel->setText("Title: " + m.getTitle());
    descrLabel->setText(m.getDescr());
    
    ReminderWidget *visitor = new ReminderWidget();
    m.accept(visitor);
    visitLayout->addWidget(visitor->getWidget());
}

AbstractReminder& MediaView::getReminder() const {
    return *reminder;
}

