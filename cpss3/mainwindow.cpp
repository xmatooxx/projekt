#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QtCore>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    cel = new Cel();


    connect(cel, SIGNAL(mousePressSignal()), this, SLOT(dodajPunkty()));

    pkt = 0;
    time = 1;


    timer = new QTimer(this);
    timer->setInterval(500);

    czas = new QTimer(this);
    czas->setInterval(1);

    connect(timer, SIGNAL(timeout()), this, SLOT(ruch()));
    connect(czas, SIGNAL(timeout()), this, SLOT(liczCzas()));
    ui->label->setText( QDateTime::fromMSecsSinceEpoch(time, Qt::UTC).toString("hh:mm:ss") );

    QSettings settings("cpss", "prgr");
    settings.beginGroup("MainWindow");
    best = settings.value("best").toInt();
    settings.endGroup();

    ui->bestlabel->setText(QString::number(best));
}

MainWindow::~MainWindow()
{
    QSettings settings("cpss", "prgr");

    settings.beginGroup("MainWindow");
    settings.setValue("best", best);
    settings.endGroup();

    delete ui;
}

void MainWindow::dodajPunkty()
{
    if(time != 0)
    {
        pkt++;
        ui->wynik->setText(QString::number(pkt));
    }
}

void MainWindow::ruch()
{
    if (time == 0)
    {
        timer->stop();
        return;
    }
    else
    {
        int x = QRandomGenerator::global()->bounded(420) -420;
        int y = QRandomGenerator::global()->bounded(330) -330;
        cel->setPos(x,y);
    }

}

void MainWindow::startgry()
{
    pkt = 0;
    ui->wynik->setText(QString::number(pkt));
    scene->addItem(cel);
    timer->start();
    czas->start();
}


void MainWindow::on_pushButton_clicked()
{
    spin = ui->spinBox->text();

    mins = spin.toUInt() * 1000;
    startgry();
}

void MainWindow::liczCzas()
{

    time++;
    ui->label->setText( QDateTime::fromMSecsSinceEpoch(time, Qt::UTC).toString("hh:mm:ss") );
    if (pkt > best)
    {
        best = pkt;
        ui->bestlabel->setText(QString::number(best));
    }
    if(time != 0 and time == mins)
    {
        time = 0;
        czas->stop();
    }

}

void MainWindow::on_fivemin_clicked()
{
    best = 0;
    ui->bestlabel->setText(QString::number(best));
}
