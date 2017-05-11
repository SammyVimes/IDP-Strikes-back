#ifndef FOOD_H
#define FOOD_H

#include <QString>

class Food
{
public:
    Food(QString name, QString comp, int expirationDate, int amount);
    Food(const Food &f);

    QString name() const;
    void setName(const QString &name);

    QString comp() const;
    void setComp(const QString &comp);

    int expirationDate() const;
    void setExpirationDate(int expirationDate);

    int amount() const;
    void setAmount(int amount);

private:
    QString m_name;
    QString m_comp;
    int m_expirationDate;
    int m_amount;
};

#endif // FOOD_H