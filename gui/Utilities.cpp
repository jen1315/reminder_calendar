#include "Utilities.h"

#include <QWidget>

void Utilities::clearLayout(QLayout *layout) {
    if(!layout)
        return ;

    QLayout *subLayout;
    QWidget *widget = new QWidget();
    while(QLayoutItem *item = layout->takeAt(0)) {
        widget = item->widget();
        subLayout = item->layout();
        if(widget)
            delete widget;
        else if(subLayout)
            clearLayout(subLayout);
        delete item;
    }
}