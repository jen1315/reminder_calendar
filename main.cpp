#include <QApplication>
#include "JsonFile.h"
#include "./gui/ViewManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ViewManager view;
    view.show();

    return app.exec();
}
