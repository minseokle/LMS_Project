#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#define PI 3.141592

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <cmath>
#include "ball.h"
#include <QMainWindow>

class Gameboard: public QGraphicsView
{

public:
    Gameboard(QWidget *parent);
    void restart(bool mode);
    void ballmove();
    int white;
    int black;
    bool player;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QGraphicsScene *scene;
    QGraphicsLineItem *goline;
    QPoint firstpoint;
    bool drag;
    QGraphicsRectItem*endline;
    double length;
    double deg;
    Ball*ball;
    bool play;
    int selectball;
    QGraphicsTextItem *endtext;
    QGraphicsRectItem *gameend;
    bool text;
};

#endif // GAMEBOARD_H
