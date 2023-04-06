#include "Widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("Minesweeper"); // Tên phần mềm
    w.setWindowIcon(QIcon(":/Image/Icon.png")); // Hình Icon
    w.show();
    return a.exec();
}
