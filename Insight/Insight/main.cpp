#include "Insight.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Insight w;
    w.show();
    return a.exec();
}
