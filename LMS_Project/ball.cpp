#include "ball.h"

#include <cmath>
Ball::Ball()
{
    x=0;
    y=0;
    velocity=0;
    sin=0;
    cos=1;
    out=true;
    friction=1;
}

void Ball::setscene(QGraphicsScene *_scene)
{
    ball=_scene->addEllipse(x-15,y-15,30,30,QPen(Qt::black),Qt::NoBrush);
    ball->setVisible(false);
}

void Ball::set(int _x, int _y, QBrush brush)
{
    out=false;
    x=_x;
    y=_y;
    ball->setBrush(brush);
    ball->setPos(x,y);
    ball->setVisible(true);
}
void Ball::go(double vel,double _sin,double _cos)
{
    velocity=vel;
    sin=_sin;
    cos=_cos;
}
bool Ball::moveable()
{
    if(velocity==0||out)
    {
        return 0;
    }
    return 1;
}

void Ball::move()
{
    x+=velocity*cos/90;
    y+=velocity*sin/90;
    velocity-=friction/10.0;
    ball->setPos(x,y);
    if(velocity<0)
    {
        velocity=0;
    }
    if(x>700||x<100||y<100||y>700)
    {
        out=true;
        velocity=0;
        ball->setVisible(false);
    }

}
void Ball::collision(Ball *collisionball)
{
    double length=sqrt(pow(collisionball->x-this->x,2)+pow(collisionball->y-this->y,2));
    if(length<29&&!collisionball->out)
    {
        double sina=this->sin;
        double cosa=this->cos;
        double a;
        if(sina<0)
        {
            a=acos(-1)*2-acos(cosa);
        }
        else
        {
            a=acos(cosa);
        }
        double sinb=(collisionball->y-this->y)/length;
        double cosb=(collisionball->x-this->x)/length;
        double b;
        if(sinb<0)
        {
            b=acos(-1)*2-acos(cosb);
        }
        else
        {
            b=acos(cosb);
        }
        double sins1=sinb*cosa-sina*cosb;
        double coss1=cosa*cosb+sina*sinb;

        double sins2;
        double coss2;
        if(a<b)
        {
            if(b-a>3.1415)
            {
                sins2=cosb;
                coss2=-sinb;
            }
            else
            {
                sins2=-cosb;
                coss2=sinb;
            }
        }
        else
        {
            if(a-b>3.1415)
            {
                sins2=-cosb;
                coss2=sinb;
            }
            else
            {
                sins2=cosb;
                coss2=-sinb;
            }
        }

        double velocity1=velocity*coss1;
        if(velocity1<0)
            velocity1=-velocity1;
        double velocity2=velocity*sins1;
        if(velocity2<0)
            velocity2=-velocity2;

        collisionball->go(velocity1,sinb,cosb);

        velocity=velocity2;
        this->sin=sins2;
        this->cos=coss2;
        collisionball->move();
        this->move();

    }
}
