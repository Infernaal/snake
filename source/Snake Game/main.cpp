#include <QApplication>
#include "snake.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    snake snakegame;
    snakegame.setWindowTitle("Snake Game");
    snakegame.setStyleSheet("background-image: url(:/image/backpicture.png);");
    snakegame.show();

    return a.exec();
}
