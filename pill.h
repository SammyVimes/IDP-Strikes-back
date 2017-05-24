#ifndef PILL_H
#define PILL_H

#include <QString>
#include <iostream>
#include <QtXml>

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

    static Pill deserialize(QDomNode node) {
        QDomNode fElem = node.firstChild();
        QString name;
        int lifeTime;
        bool beforeFlag;
        int takeTimeMask;
        QString amount;
        while (!fElem.isNull()) {
            QString tagName = fElem.nodeName();
            if (tagName == "name") {
               name = fElem.firstChild().nodeValue();
            } else if (tagName == "amount") {
                amount = fElem.firstChild().nodeValue();
            } else if (tagName == "beforeFlag") {
                beforeFlag = fElem.firstChild().nodeValue().toInt() == 1;
            } else if (tagName == "lifeTime") {
                lifeTime = fElem.firstChild().nodeValue().toInt();
            } else if (tagName == "takeTimeMask") {
                takeTimeMask = fElem.firstChild().nodeValue().toInt();
            }
            fElem = fElem.nextSibling();
        }
        return Pill(name, lifeTime, beforeFlag, takeTimeMask, amount);
    }

    void printStream(ostream& os) {
        os << "<pill>";
        os << "<name>";
        os << m_name.toStdString();
        os << "</name>";
        os << "<lifeTime>";
        os << QString::number(m_lifeTime).toStdString();
        os << "</lifeTime>";
        os << "<beforeFlag>";
        os << QString::number(m_beforeFlag ? 1 : 0).toStdString();
        os << "</beforeFlag>";
        os << "<takeTimeMask>";
        os << QString::number(m_takeTimeMask).toStdString();
        os << "</takeTimeMask>";
        os << "<amount>";
        os << m_amount.toStdString();
        os << "</amount>";
        os << "</pill>";
    }

private:
    QString m_name;
    int m_lifeTime;
    bool m_beforeFlag;
    int m_takeTimeMask;
    QString m_amount;
};

#endif // PILL_H
