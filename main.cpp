#include "mainwindow.h"
#include "stusql.h"
#include <QApplication>
#include <QDialog>
#include"mainwindow.h"





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    stuSql sql;

    return a.exec();
}
