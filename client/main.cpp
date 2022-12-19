#include "include/gui/base.h"

#include <QApplication>
#include <QLabel>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Base w;
    w.show();

    return a.exec();
}
