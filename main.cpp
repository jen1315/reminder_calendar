#include <QApplication>
#include "JsonFile.h"
#include "./gui/ViewManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QString json = "reminder.json";

    ViewManager view(json);
    view.show();

    return app.exec();
}
