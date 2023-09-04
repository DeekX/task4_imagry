#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include "shared.h"
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
#include "ourproducts.h"
#include "shared.h"

void updateAllQuantities(const QMap<QSpinBox*, QString> &spinBoxMap, const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open the file.");
        return;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonArray = doc.array();

    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject obj = jsonArray[i].toObject();
        for (auto spinBox : spinBoxMap.keys()) {
            if (obj["name"].toString() == spinBoxMap[spinBox]) {
                obj["quantity"] = spinBox->value();
                jsonArray[i] = obj;
                break;
            }
        }
    }

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Failed to open the file for writing.");
        return;
    }
    QJsonDocument updatedDoc(jsonArray);
    file.write(updatedDoc.toJson());
    file.close();
}

void MainWindow::displayAvailableIngredients(const QString &path) {
    QFile file(path);
    QMap<QSpinBox*, QString> spinBoxMap;
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open the file.");
        return;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonArray = doc.array();

    int current = 100;

    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();

        QPixmap pixmap(obj["photo path"].toString());
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setPixmap(pixmap.scaled(151,131, Qt::KeepAspectRatio));
        imageLabel->setGeometry(QRect(30, current, 151, 131));
        imageLabel->show();
        current+=150;


        QLabel *name = new QLabel(this);
        name->setText(obj["name"].toString());
        name->setGeometry(QRect(330, current - 90, 200, 50));
        name->show();

        QSpinBox *spinBox = new QSpinBox(this);
        spinBox->setValue(obj["quantity"].toInt());
        spinBox->setSingleStep(1);  // Increment/Decrement by 5
        spinBox->setGeometry(630,current-90 , 80, 30); // x, y, width, height
        spinBox->show();

        spinBoxMap.insert(spinBox, obj["name"].toString());

        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this, spinBoxMap, path](){
            updateAllQuantities(spinBoxMap, path);
        });
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    displayAvailableIngredients("/home/deek/task4/currentProducts.json");

    QPushButton *button = new QPushButton("Our products", this); // Assuming 'this' is a QWidget or QMainWindow
    button->setGeometry(10, 50, 300, 50); // x, y, width, height
    connect(button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));


}

void MainWindow::onButtonClicked() {

    OurProducts p;
    p.setModal(true);
    hide();
    p.exec();
}


MainWindow::~MainWindow()
{
    delete ui;
}

