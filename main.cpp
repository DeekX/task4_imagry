#include "mainwindow.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>



int main(int argc, char *argv[])
{
    //readProductsData("/home/deek/task4/productsData.json");
    //readIngredients("/home/deek/task4/currentProducts.json");
    //qDebug()<<availabelIngredients.size();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
