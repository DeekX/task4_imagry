#include "ourproducts.h"
#include "ui_ourproducts.h"
#include <QDebug>
#include "shared.h"
#include <string.h>
#include <QJsonArray>

struct Product {
    QString name;
    QMap<QString, int> requirements;
    int sellPrice;
};

QList<Product> readProductsFromJson(const QString &path) {
    QList<Product> products;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open the file.");
        return products;  // Return an empty list
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();

        Product product;
        product.name = obj["name"].toString();
        product.sellPrice = obj["sell price"].toInt();

        QJsonObject requirementsObj = obj["requirments"].toObject();
        for (const QString &key : requirementsObj.keys()) {
            product.requirements.insert(key, requirementsObj[key].toInt());
        }

        products.append(product);
    }

    return products;
}




OurProducts::OurProducts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OurProducts)
{
    ui->setupUi(this);
    //qDebug()<<availabelIngredients.size();
    int current = 100;
    QList<Product> products = readProductsFromJson("/home/deek/task4/productsData.json");
    for (const Product &product : products) {
        QLabel *name = new QLabel(this);
        name->setText(product.name);
        name->setGeometry(QRect(50, current - 90, 200, 50));
        name->show();

        QLabel *price = new QLabel(this);
        price->setText(QString::number(product.sellPrice));
        price->setGeometry(QRect(330, current - 90, 200, 50));
        price->show();

        current+=200;
        int cu = current-200;
        for (auto it = product.requirements.begin(); it != product.requirements.end(); ++it) {
            QLabel *req = new QLabel(this);
            req->setText(it.key());
            req->setGeometry(QRect(530, cu, 200, 50));
            req->show();
            qDebug() << it.key() << ":" << it.value();
            cu-=45;
        }
            QPushButton *buyButton = new QPushButton("Buy", this);
        buyButton->setGeometry(QRect(930,current-250,150,50));
        connect(buyButton, &QPushButton::clicked, [this, product](){
            buyProduct(product.name);
        });
        buyButton->show();
    }
}

Product getProductDetails(const QString &productName, const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open the file.");
        return Product();  // Return an empty Product if the file can't be opened
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();
        if (obj["name"].toString() == productName) {
            Product product;
            product.name = obj["name"].toString();
            product.sellPrice = obj["sell price"].toInt();

            QJsonObject requirementsObj = obj["requirments"].toObject();
            for (const QString &key : requirementsObj.keys()) {
                product.requirements.insert(key, requirementsObj[key].toInt());
            }

            return product;
        }
    }

    return Product();  // Return an empty Product if the product is not found
}


void OurProducts::buyProduct(const QString &productName){
    // Get the product's requirements from the first JSON file
    Product product = getProductDetails(productName, "/home/deek/task4/productsData.json");

    QJsonArray ingredients = getAvailableIngredients();
    bool canBuy = true;

    for (auto it = product.requirements.begin(); it != product.requirements.end(); ++it) {
        int availableQuantity = getQuantityOfIngredient(it.key(), ingredients);
        if (availableQuantity < it.value()) {
            canBuy = false;
            qDebug() << "Not enough" << it.key();
            break;
        }
    }

    if (canBuy) {
        // Decrement the quantities in the ingredients array
        for (int i = 0; i < ingredients.size(); ++i) {
            QJsonObject obj = ingredients[i].toObject();
            if (product.requirements.contains(obj["name"].toString())) {
                int newQuantity = obj["quantity"].toInt() - product.requirements[obj["name"].toString()];
                obj["quantity"] = newQuantity;
                ingredients[i] = obj;
            }
        }

        // Save the updated quantities back to the JSON file
        QFile file("/home/deek/task4/currentProducts.json");
        if (file.open(QIODevice::WriteOnly)) {
            QJsonDocument doc(ingredients);
            file.write(doc.toJson());
            file.close();
        }

        qDebug() << "Bought product:" << productName;
        // ... [Additional buying logic here, if any]
    } else {
        qDebug() << "Cannot buy product:" << productName;
    }

}

QJsonArray OurProducts::getAvailableIngredients(){
    QFile file("/home/deek/task4/currentProducts.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Failed to open the file.");
        return QJsonArray();  // Return an empty array if the file can't be opened
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    return doc.array();
}

int OurProducts::getQuantityOfIngredient(const QString &ingredientName, const QJsonArray &ingredients) {
    for (const QJsonValue &value : ingredients) {
        QJsonObject obj = value.toObject();
        if (obj["name"].toString() == ingredientName) {
            return obj["quantity"].toInt();
        }
    }
    return 0;
}

OurProducts::~OurProducts()
{
    delete ui;
}
