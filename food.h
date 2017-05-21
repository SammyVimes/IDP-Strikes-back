#ifndef FOOD_H
#define FOOD_H

#include <QString>
#include <iostream>
#include <vector>
#include <QStringList>

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

    void printStream(ostream& os) {
        os << "<food>";
        os << "<name>" << endl;
        os << m_name.toStdString() << endl;
        os << "</name>" << endl;
        os << "<comp>" << endl;
        os << comp().toStdString() << endl;
        os << "</comp>" << endl;
        os << "<expiration>" << endl;
        os << QString::number(m_expirationDate).toStdString() << endl;
        os << "</expiration>" << endl;
        os << "<amount>" << endl;
        os << QString::number(m_amount).toStdString() << endl;
        os << "</amount>" << endl;
        os << "</food>";
    }

private:
    QString m_name;
    vector<QString> m_comp;
    int m_expirationDate;
    int m_amount;
};

#endif // FOOD_H
