#ifndef SHARED_H
#define SHARED_H
#include <bits/stdc++.h>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QDialog>

//struct requirments{
//    int flowerwater;
//    int teaBag;
//    int khal;
//    int beet;
//};

//struct products{
//    QString productName;
//    requirments req;
//    int sellPrice;
//};

//struct ingredients{
//    QString name;
//    QString path;
//    int quantity;
//};

//static std::vector<products>currentProducts;
//static std::vector<ingredients>availabelIngredients;

//void initcurrentProducts(){
//        QFile file("/home/deek/task4/productsData.json");
//        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//            qWarning("Failed to open the file.");
//            return;
//        }

//        // Read the file content
//        QByteArray jsonData = file.readAll();
//        file.close();

//        // Parse the JSON data
//        QJsonDocument document = QJsonDocument::fromJson(jsonData);
//        if (document.isNull()) {
//            qWarning("Failed to parse the file as JSON.");
//            return;
//        }

//        if (!document.isArray()) {
//            qWarning("JSON is not an array.");
//            return;
//        }

//        QJsonArray productss = document.array();

//        // Iterate over each product and print its details
//        for (const QJsonValue &value : productss) {
//            products p;
//            QJsonObject product = value.toObject();
//            p.productName = product["name"].toString();
//            p.sellPrice = product["sell price"].toInt();
//            QJsonObject requirementss = product["requirments"].toObject();
//            requirments r;
//            for (const QString &key : requirementss.keys()) {
//                if(key == "flower water")
//                    r.flowerwater = requirementss[key].toInt();
//                else if(key == "tea bag")
//                    r.teaBag = requirementss[key].toInt();
//                else if(key == "khal")
//                    r.khal = requirementss[key].toInt();
//                else
//                    r.beet = requirementss[key].toInt();
//            }
//            p.req = r;
//            currentProducts.push_back(p);
//        }

////            for(auto &x : currentProducts){
////                qDebug()<<x.productName<<" , "<<x.req.beet<<" , "<<x.req.flowerwater<<" , "<<x.req.khal<<" , "<<x.req.teaBag<<" , "<<x.sellPrice;
////            }
//}

//void initavailabelIngredients(){
//            QFile file("/home/deek/task4/currentProducts.json");
//            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//                qWarning("Failed to open the file.");
//                return;
//            }
//            QByteArray jsonData = file.readAll();
//            file.close();
//            QJsonDocument document = QJsonDocument::fromJson(jsonData);
//            if (document.isNull()) {
//                qWarning("Failed to parse the file as JSON.");
//                return;
//            }

//            if (!document.isArray()) {
//                qWarning("JSON is not an array.");
//                return;
//            }

//            QJsonArray ing = document.array();

//            for (const QJsonValue &value : ing) {
//                ingredients in;
//                QJsonObject product = value.toObject();
//                in.name = product["name"].toString();
//                in.path = product["photo path"].toString();
//                in.quantity = product["quantity"].toInt();
//                availabelIngredients.push_back(in);
//            }

//}

/*
    initcurrentProducts();
    initavailabelIngredients();
    QMap<QSpinBox*, QString> spinBoxMap;
    int current = 100;
    for(auto &x : availabelIngredients){
        QPixmap pixmap(x.path);
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setPixmap(pixmap.scaled(151,131, Qt::KeepAspectRatio));
        imageLabel->setGeometry(QRect(30, current, 151, 131));
        imageLabel->show();
        current+=150;

        QLabel *name = new QLabel(this);
        name->setText(x.name);
        name->setGeometry(QRect(330, current - 90, 200, 50));
        name->show();

        QSpinBox *spinBox = new QSpinBox(this); // Assuming 'this' is a QWidget or QMainWindow
        spinBox->setRange(0, 100);  // Set range from 0 to 100
        spinBox->setValue(x.quantity);      // Set initial value to 50
        spinBox->setSingleStep(1);  // Increment/Decrement by 5
        spinBox->setGeometry(630,current-90 , 80, 30); // x, y, width, height
        spinBox->show();
        spinBoxMap.insert(spinBox, x.name);  // Store the spin box and its associated item name
        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this, spinBoxMap](){
            updateAllQuantities(spinBoxMap, "/home/deek/task4/currentProducts.json");  // Replace with your actual path
        });

    }
*/

#endif
