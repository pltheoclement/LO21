#include "operator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Operator w;
    w.show();
    return a.exec();
}
