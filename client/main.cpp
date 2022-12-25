#include "include/gui/base.h"

#include <QApplication>
#include <QLabel>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Base w;

    w.setWindowTitle("Rabbit Hole");
    w.setWindowIcon(QIcon("img/rabbit.png"));

    w.show();

    return a.exec();
}
