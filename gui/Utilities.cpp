#include "Utilities.h"

#include <QWidget>

void Utilities::clearLayout(QLayout *layout) {
    if(!layout)
        return ;

    QLayout *subLayout;
    QWidget *widget = new QWidget();
    while(QLayoutItem *item = layout->takeAt(0)) {
        if(widget = item->widget())
            delete widget;
        else if(subLayout = item->layout())
            clearLayout(subLayout);
        delete item;
    }
}