/* Для чтения с БДХК */

#include "mainwindow.h"
#include <QApplication>
#include <windows.h>
#include <QDebug>
#include <QSplashScreen>
#include <QTimer>






int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    //splash->setPixmap((QPixmap("C:/BDHC_030615+GPS+RXO+Database/untitled1/Splash_Finish.png")));
    splash->show();

    MainWindow w;
    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));
    w.show();

    return a.exec();
}
