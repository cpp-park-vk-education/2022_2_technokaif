#include "../include/windows/base.h"

#include <QApplication>
#include <QLabel>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Base w;
    w.setWindowTitle("Rabbit Hole");
    QIcon logo("img/rabbit.png");
    w.setWindowIcon(logo);

    w.show();

    return a.exec();
}
