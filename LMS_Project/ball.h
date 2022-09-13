#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QGraphicsScene>


class Ball
{
public:
    Ball();
    void setscene(QGraphicsScene *_scene);
    void set(int _x,int _y,QBrush brush);
    void move();
    void go(double vel, double _sin, double _cos);
    bool moveable();
    void collision(Ball *collisionball);
    bool out;
    double x,y;
private:
    double velocity;
    double sin;
    double cos;
    double friction;
    QGraphicsEllipseItem* ball;
};

#endif // BALL_H
