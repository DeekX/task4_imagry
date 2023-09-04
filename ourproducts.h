#ifndef OURPRODUCTS_H
#define OURPRODUCTS_H

#include <QDialog>
#include <QJsonArray>
namespace Ui {
class OurProducts;
}

class OurProducts : public QDialog
{
    Q_OBJECT

public:
    explicit OurProducts(QWidget *parent = nullptr);
    ~OurProducts();

private:
    Ui::OurProducts *ui;

public slots:
    void buyProduct(const QString &productName);
    QJsonArray getAvailableIngredients();
    int getQuantityOfIngredient(const QString &ingredientName, const QJsonArray &ingredients);
};



#endif // OURPRODUCTS_H
