#include "stdafx.h"
#include "sibsdump.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiBsDump w;
    w.show();
    return a.exec();
}
