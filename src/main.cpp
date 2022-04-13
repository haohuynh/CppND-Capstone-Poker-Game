#include "uicontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    new UIController();

    return a.exec();
}
