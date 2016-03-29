#include "squirrelmain.h"
#include "memory.h"
#include <QApplication>
#include <iostream>

using namespace std;

extern "C"
{
    #include "Facade.h"
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SquirrelMain *w = new SquirrelMain();
    w->show();
    return a.exec();
}
