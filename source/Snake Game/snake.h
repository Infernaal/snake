#pragma once

#include <QWidget>
#include <QKeyEvent>

class snake : public QWidget {

  public:
      snake(QWidget *parent = 0);

  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

public slots:
       void pauseGame();
       void startGame();

private:
      QImage snake_torso;
      QImage snake_head;
      QImage fruit;
      QImage fruit1;

      static const int B_WIDTH = 300;
      static const int B_HEIGHT = 300;
      static const int DOT_SIZE = 10;
      static const int ALL_DOTS = 900;
      static const int RAND_POS = 29;
      static const int DELAY = 140;

      int timerId;
      int torso;
      int fruit_x;
      int fruit_y;

      int x[ALL_DOTS];
      int y[ALL_DOTS];

      bool leftMove;
      bool rightMove;
      bool upMove;
      bool downMove;
      bool inGame;
      bool inPaused;

      void loadImages();
      void initGame();
      void locateFruit();
      void checkFruit();
      void checkCollision();
      void move();
      void doDrawing();
      void gameOver(QPainter &);
};
