#include "gameboard.h"

#include <QTimer>


Gameboard::Gameboard(QWidget *parent) : QGraphicsView(parent)
{
    black=8;
    white=8;

    scene=new QGraphicsScene;
    this->setScene(scene);
    endline=scene->addRect(0,0,800-2,800-12,Qt::NoPen,Qt::NoBrush);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(5);
    QGraphicsRectItem*endrect=scene->addRect(100,100,600,600,pen,QBrush(QColor(0xdc,0xb3,0x5c)));
    endrect->setVisible(true);



    pen.setWidth(2);
    for(int i=0;i<19;i++)
    {
        scene->addLine(150,150+i*500/18,650,150+i*500/18,pen);
    }
    for(int i=0;i<19;i++)
    {
        scene->addLine(150+i*500/18,150,150+i*500/18,650,pen);
    }

    goline=scene->addLine(0,0,0,0,QPen(Qt::black));
    goline->setVisible(false);

    drag=false;
    ball=new Ball[16];
    for(int i=0;i<16;i++)
    {
        ball[i].setscene(scene);
    }

    gameend=scene->addRect(100,300,600,200,QPen(Qt::black),QBrush(Qt::white));
    gameend->setVisible(false);
    endtext=scene->addText("     black win!!\n    press restart");

}


void Gameboard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton&&play) {
        if(player)
        {
            for(int i=0;i<8;i++){
                if(sqrt(pow(event->pos().x()-ball[i].x,2)+pow(event->pos().y()-ball[i].y,2))<15&&!ball[i].out)
                {
                    goline->setVisible(true);
                    QPen pen;
                    pen.setColor(Qt::white);
                    pen.setWidth(2);
                    goline->setPen(pen);
                    goline->setLine(event->pos().x(),event->pos().y(),event->pos().x(),event->pos().y());
                    firstpoint.setX(ball[i].x);
                    firstpoint.setY(ball[i].y);
                    drag=true;
                    play=false;
                    selectball=i;
                }
            }
        }
        else
        {
            for(int i=8;i<16;i++){
                if(sqrt(pow(event->pos().x()-ball[i].x,2)+pow(event->pos().y()-ball[i].y,2))<15&&!ball[i].out)
                {
                    goline->setVisible(true);
                    QPen pen;
                    pen.setColor(Qt::white);
                    pen.setWidth(2);
                    goline->setPen(pen);
                    goline->setLine(event->pos().x(),event->pos().y(),event->pos().x(),event->pos().y());
                    firstpoint.setX(ball[i].x);
                    firstpoint.setY(ball[i].y);
                    drag=true;
                    play=false;
                    selectball=i;
                }
            }
        }
    }
}

void Gameboard::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drag){
        length=sqrt(pow(firstpoint.x()-event->pos().x(),2)+pow(firstpoint.y()-event->pos().y(),2));
        QPen pen;
        pen.setColor(Qt::blue);
        double cos=(event->pos().x()-firstpoint.x())/length;
        double sin=(event->pos().y()-firstpoint.y())/length;
        if(length>=90)
        {
            length=90;
        }
        pen.setWidth(length/5+2);
        pen.setWidth(length/5+2);
        goline->setPen(pen);
        goline->setLine(firstpoint.x(),firstpoint.y(),firstpoint.x()+length*cos,firstpoint.y()+length*sin);

    }
}

void Gameboard::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drag)
    {
        length=sqrt(pow(firstpoint.x()-event->pos().x(),2)+pow(firstpoint.y()-event->pos().y(),2));
        double cos=(event->pos().x()-firstpoint.x())/length;
        double sin=(event->pos().y()-firstpoint.y())/length;
        if(length>=90)
        {
            length=90;
        }
        if(length>15)
        {
            player=!player;
            ball[selectball].go(length,-sin,-cos);
        }
        goline->setVisible(false);
        drag=false;
    }

}
void Gameboard::restart()
{
    if(!text)
    {
        endtext->setVisible(false);
        delete endtext;
        text=true;
    }
    player=1;
    for(int i=0;i<8;i++)
    {
        ball[i].go(0,0,1);
        ball[i].set(150+2*(i+1)*500/18,150+2*500/18+i%2*500/6,QBrush(Qt::black));
    }
    for(int i=0;i<8;i++)
    {
        ball[i+8].go(0,0,1);
        ball[i+8].set(150+2*(i+1)*500/18,150+13*500/18+i%2*500/6,QBrush(Qt::white));
    }
    gameend->setVisible(false);
}
void Gameboard::ballmove()
{
    bool ap=true;
    for(int i=0;i<16;i++)
    {
        if(ball[i].moveable())
        {
            ap=false;
            for(int j=0;j<16;j++)
            {
                if(j!=i)
                {
                    ball[i].collision(&(ball[j]));
                }
            }
            ball[i].move();
        }
    }
    black=0;
    white=0;
    for(int i=0;i<8;i++)
    {
        if(!ball[i].out)
        {
            black++;
        }
    }
    for(int i=8;i<16;i++)
    {
        if(!ball[i].out)
        {
            white++;
        }
    }
    if(black==0)
    {
        ap=false;
        if(text)
        {
            endtext=scene->addText("     white win!!\n    press restart");
            endtext->setPos(100,300);
            QFont font;
            font.setPointSize(50);
            endtext->setFont(font);
            gameend->setVisible(true);
            text=false;
        }
    }
    else if(white==0)
    {

        ap=false;
        if(text)
        {
            endtext=scene->addText("     black win!!\n    press restart");
            endtext->setPos(100,300);
            QFont font;
            font.setPointSize(50);
            endtext->setFont(font);
            gameend->setVisible(true);
            text=false;
        }
    }
    play=ap;
}
