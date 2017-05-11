#ifndef PILL_H
#define PILL_H

#include <QString>

class Pill
{
public:
    Pill(QString name, int lifeTime, bool beforeFlag, int takeTimeMask, QString amount);
    Pill(const Pill &p);

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

private:
    QString m_name;
    int m_lifeTime;
    bool m_beforeFlag;
    int m_takeTimeMask;
    QString m_amount;
};

#endif // PILL_H
