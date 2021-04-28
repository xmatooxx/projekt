#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QtCore>
#include <QTime>
#include <QBrush>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();
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

    //sceneRect = self.sceneRect()

    //pic = QPixmap(":/images/68799212.png")
    //rectf = QRectF(pic.rect())
    //painter.drawPixmap(sceneRect, pic, rectf)
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
        move++;

        ui->trafione->setText(QString::number(pkt));
        ui->nietrafione->setText(QString::number(move - pkt));
        ui->wszystkie->setText(QString::number(move));
    }

}

void MainWindow::startgry()
{
    move = 0;
    pkt = 0;
    ui->wynik->setText(QString::number(pkt));
    ui->trafione->setText(QString::number(pkt));
    ui->nietrafione->setText(QString::number(move - pkt));
    ui->wszystkie->setText(QString::number(move));
    scene->addItem(cel);
    timer->start();
    czas->start();
}


void MainWindow::on_pushButton_clicked()
{
    spin = ui->spinBox->text();

    dwa = spin.toInt();

    mins = spin.toUInt() * 1000;
    startgry();
    ui->pushButton->setEnabled(false);
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

        raz = pkt / dwa;

        percent = (pkt / move) * 100;
        ui->procent->setText(QString::number(percent) + '%');

        delay();
        scene->removeItem(cel);
        ui->pushButton->setEnabled(true);
    }

}

void MainWindow::on_fivemin_clicked()
{
    best = 0;
    ui->bestlabel->setText(QString::number(best));
}

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
