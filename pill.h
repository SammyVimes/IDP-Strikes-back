#ifndef PILL_H
#define PILL_H

#include <QString>
#include <iostream>

using namespace std;

class Pill
{
public:
    Pill(QString name, int lifeTime, bool beforeFlag, int takeTimeMask, QString amount);
    Pill(const Pill &p);
    Pill() {

    }

    QString name() const;
    void setName(const QString &name);

    bool beforeFlag() const;
    void setBeforeFlag(bool beforeFlag);

    int takeTimeMask() const;
    void setTakeTimeMask(int takeTimeMask);

    QString getAmount() const;
    void setAmount(const QString &value);

    int getLifeTime() const;
    void setLifeTime(int lifeTime);

    void printStream(ostream& os) {
        os << "<pill>" << endl;
        os << "<name>" << endl;
        os << m_name.toStdString() << endl;
        os << "</name>" << endl;
        os << "<lifeTime>" << endl;
        os << QString::number(m_lifeTime).toStdString() << endl;
        os << "</lifeTime>" << endl;
        os << "<beforeFlag>" << endl;
        os << m_beforeFlag << endl;
        os << "</beforeFlag>" << endl;
        os << "<takeTimeMask>" << endl;
        os << QString::number(m_takeTimeMask).toStdString() << endl;
        os << "</takeTimeMask>" << endl;
        os << "<amount>" << endl;
        os << m_amount.toStdString() << endl;
        os << "</amount>" << endl;
        os << "</pill>" << endl;
    }

private:
    QString m_name;
    int m_lifeTime;
    bool m_beforeFlag;
    int m_takeTimeMask;
    QString m_amount;
};

#endif // PILL_H
