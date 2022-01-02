#include <QPainter>
#include <QTime>
#include <QIcon>
#include <QCoreApplication>
#include "snake.h"

snake::snake(QWidget *parent) : QWidget(parent) {

    leftMove = false;
    rightMove = true;
    upMove = false;
    downMove = false;
    inGame = true;
    inPaused = false;
    setFixedSize(B_WIDTH, B_HEIGHT);
    setWindowIcon(QIcon(":/image/snake.png"));
    loadImages();
    initGame();
}


void snake::loadImages() {

    snake_torso.load(":/image/sneak_torso.png");
    snake_head.load(":/image/snake_head_right.png");
    fruit.load(":/image/fruit.png");
}

void snake::initGame() {
    torso = 3;

    for (int z = 0; z < torso; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    locateFruit();

    timerId = startTimer(DELAY);
}

void snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    QPainter painter(this);
    QRect rect = contentsRect();
    QFont font("Courier", 15, QFont::DemiBold);
    painter.setFont(font);
    if (inPaused) {
           painter.setPen ( Qt::black);
           painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
           return;
       }

    doDrawing();
}

void snake::startGame()
{
    if (inPaused)
        return;

    leftMove = false;
    rightMove = true;
    upMove = false;
    downMove = false;
    inGame = true;
    inPaused = false;
    initGame();
}

void snake::pauseGame()
{
    if (!inGame)
        return;
    inPaused = !inPaused;
    if (inPaused) {
        killTimer(timerId);
    } else {
        timerId = startTimer(DELAY);
    }
    update();
}

void snake::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(fruit_x, fruit_y, fruit);
        for (int z = 0; z < torso; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], snake_head);
            } else {
                qp.drawImage(x[z], y[z], snake_torso);
            }
        }

    } else {

        gameOver(qp);
    }
}

void snake::gameOver(QPainter &qp) {

    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::black));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

void snake::checkFruit() {

    if ((x[0] == fruit_x) && (y[0] == fruit_y)) {

        torso++;
        locateFruit();
    }
}

void snake::move() {

    for (int z = torso; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftMove) {
        x[0] -= DOT_SIZE;
        snake_head.load(":/image/snake_head_left.png");
    }

    if (rightMove) {
        x[0] += DOT_SIZE;
        snake_head.load(":/image/snake_head_right.png");
    }

    if (upMove) {
        y[0] -= DOT_SIZE;
        snake_head.load(":/image/snake_head_up.png");
    }

    if (downMove) {
        y[0] += DOT_SIZE;
        snake_head.load(":/image/snake_head_down.png");
    }
}

void snake::checkCollision() {

    for (int z = torso; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

void snake::locateFruit() {

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    fruit_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    fruit_y = (r * DOT_SIZE);
}

void snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (inGame) {

        checkFruit();
        checkCollision();
        move();
    }

    repaint();
}

void snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightMove)) {
        leftMove = true;
        upMove = false;
        downMove = false;
    }

    if ((key == Qt::Key_Right) && (!leftMove)) {
        rightMove = true;
        upMove = false;
        downMove = false;
    }

    if ((key == Qt::Key_Up) && (!downMove)) {
        upMove = true;
        rightMove = false;
        leftMove = false;
    }

    if ((key == Qt::Key_Down) && (!upMove)) {
        downMove = true;
        rightMove = false;
        leftMove = false;
    }

    if(key == Qt::Key_Space){
        startGame();
    }

    if(key == Qt::Key_Escape){
        qApp->exit();
    }

    if(key == Qt::Key_P){
        pauseGame();
    }

    QWidget::keyPressEvent(e);
}
