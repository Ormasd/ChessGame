#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication chessgame(argc, argv);
    MainWindow window;
    window.show();
    return chessgame.exec();
}
