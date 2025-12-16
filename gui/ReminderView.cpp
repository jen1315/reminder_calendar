#include "MediaView.h"
#include "../model/Utilities.h"

MediaView::MediaView(QWidget *parent) : QWidget(parent) {
    editButton = new QPushButton("Edit");
    titleLabel = new QLabel();
    yearLabel = new QLabel();
    descrLabel = new QLabel();
    imageLabel = new QLabel();
    visitLayout = new QVBoxLayout();
    layout = new QVBoxLayout();

    titleLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    yearLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    descrLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    
    QHBoxLayout *hlayout = new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout();

    vlayout->addWidget(editButton);
    vlayout->addWidget(titleLabel);
    vlayout->addWidget(yearLabel);
    vlayout->addWidget(descrLabel);
    vlayout->addLayout(visitLayout);

    hlayout->addLayout(vlayout);
    hlayout->addWidget(imageLabel);
    layout->addLayout(hlayout);

    connect(editButton, &QPushButton::clicked, this, &MediaView::toEdit);

    setLayout(layout);
}

void MediaView::displayMedia(AbstractMedia& m) {
    Util::clearLayout(visitLayout);
    media = &m;
    titleLabel->setText("Title: " + m.getTitle());
    yearLabel->setText("Year: " + QString::number(m.getYear()));
    descrLabel->setText(m.getDescr());
    
    QString imgUrl = m.getImg();
    if(imgUrl=="")
        imgUrl = "../img/placeholder.png";    
    QPixmap image(imgUrl);
    QPixmap scaled = image.scaled(QSize(200, 200), Qt::KeepAspectRatio);
    imageLabel->setPixmap(scaled);
    imageLabel->setAlignment(Qt::AlignLeft);
    
    MediaWidget *visitor = new MediaWidget();
    m.accept(visitor);
    visitLayout->addWidget(visitor->getWidget());
}

AbstractMedia& MediaView::getMedia() const {
    return *media;
}

