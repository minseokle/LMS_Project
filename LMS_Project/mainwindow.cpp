#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board=new Gameboard(this);
    ui->mainboard->addWidget(board);

    board->restart();

    QTimer *timer=new QTimer;
    timer->start();
    timer->setInterval(1);
    connect(timer,SIGNAL(timeout()),this,SLOT(ballmove()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ballmove()
{
    board->ballmove();
    ui->whitenum->setText(QString::number(board->white));
    ui->blacknum->setText(QString::number(board->black));
    if(board->white==0)
    {
        ui->turn->setText("black win!\npress restart");
    }
    else if(board->black==0)
    {
        ui->turn->setText("white win!\npress restart");
    }
    else if(board->player)
    {
        ui->turn->setText("black turn");
    }
    else
    {
        ui->turn->setText("white turn");
    }
}

void MainWindow::on_restart_clicked()
{
    board->restart();
}

