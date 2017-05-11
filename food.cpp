#include "food.h"

Food::Food(QString name, QString comp, int expirationDate, int amount) :
    m_name(name), m_comp(comp), m_expirationDate(expirationDate), m_amount(amount)
{

}

Food::Food(const Food &f) :
    m_name(f.name()), m_comp(f.comp()), m_expirationDate(f.expirationDate()), m_amount(f.amount())
{

}

QString Food::name() const
{
    return m_name;
}

void Food::setName(const QString &name)
{
    m_name = name;
}

QString Food::comp() const
{
    return m_comp;
}

void Food::setComp(const QString &comp)
{
    m_comp = comp;
}

int Food::expirationDate() const
{
    return m_expirationDate;
}

void Food::setExpirationDate(int expirationDate)
{
    m_expirationDate = expirationDate;
}

int Food::amount() const
{
    return m_amount;
}

void Food::setAmount(int amount)
{
    m_amount = amount;
}
