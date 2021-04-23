#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

#include "cel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void dodajPunkty();
    void ruch();
    void startgry();
    void on_pushButton_clicked();
    void liczCzas();

    void on_fivemin_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Cel *cel;
    QTimer *timer;
    QTimer *czas;
    qint64 time;
    QString spin;
    int best=0;
    int current;
    int mins;
    int pkt;
};
#endif // MAINWINDOW_H
