#include "widget.h"
#include <QApplication>
#include<QtSerialPort>
#include<QSerialPortInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
