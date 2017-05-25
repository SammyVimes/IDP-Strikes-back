#ifndef FOOD_H
#define FOOD_H

#include <QString>
#include <iostream>
#include <vector>
#include <QStringList>
#include <QtXml>

using namespace std;

class Food
{
public:
    Food(QString name, QString comp, int expirationDate, int amount);
    Food(const Food &f);
    Food() {

    }

    QString name() const;
    void setName(const QString &name);

    QString comp() const;

    vector<QString> compVec() const {
        return m_comp;
    }

    void setComp(const vector<QString> &comp);

    int expirationDate() const;
    void setExpirationDate(int expirationDate);

    int amount() const;
    void setAmount(int amount);

    static Food deserialize(QDomNode node) {
        QDomNode fElem = node.firstChild();
        QString name;
        QString comp;
        int expirationDate;
        int amount;
        while (!fElem.isNull()) {
            QString tagName = fElem.nodeName();
            if (tagName == "name") {
               name = fElem.firstChild().nodeValue();
            } else if (tagName == "comp") {
                comp = fElem.firstChild().nodeValue();
            } else if (tagName == "expiration") {
                expirationDate = fElem.firstChild().nodeValue().toInt();
            } else if (tagName == "amount") {
                amount = fElem.firstChild().nodeValue().toInt();
            }
            fElem = fElem.nextSibling();
        }
        return Food(name, comp, expirationDate, amount);
    }

    void printStream(ostream& os) const {
        os << "<food>";
        os << "<name>";
        os << m_name.toStdString();
        os << "</name>";
        os << "<comp>";
        os << comp().toStdString();
        os << "</comp>";
        os << "<expiration>";
        os << QString::number(m_expirationDate).toStdString();
        os << "</expiration>";
        os << "<amount>";
        os << QString::number(m_amount).toStdString();
        os << "</amount>";
        os << "</food>";
    }

private:
    QString m_name;
    vector<QString> m_comp;
    int m_expirationDate;
    int m_amount;
};

#endif // FOOD_H
