#include "food.h"

Food::Food(QString name, QString comp, int expirationDate, int amount) :
    m_name(name),m_expirationDate(expirationDate), m_amount(amount)
{
    QStringList lst = comp.split(",");
    for(QStringList::const_iterator it = lst.begin();
          it != lst.end(); ++it) {
        QString z = *it;
        m_comp.push_back(z);
    }
}

Food::Food(const Food &f) :
    m_name(f.name()), m_comp(f.compVec()), m_expirationDate(f.expirationDate()), m_amount(f.amount())
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

QString concat_strings(const std::vector<QString> &elements,
                       const QString separator)
{
if (!elements.empty())
{
    QString str;
    auto it = elements.cbegin();
    while (true)
    {
        str.append(*it++);
        if (it != elements.cend())
            str.append(separator);
        else
            return str;
    }
}
return QString("");
}

QString Food::comp() const
{
    return concat_strings(m_comp, QString(", "));
}

void Food::setComp(const vector<QString> &comp)
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
