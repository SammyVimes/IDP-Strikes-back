#include "pill.h"

Pill::Pill(QString name, int lifeTime, bool beforeFlag, int takeTimeMask, QString amount) :
    m_name(name), m_lifeTime(lifeTime), m_beforeFlag(beforeFlag), m_takeTimeMask(takeTimeMask), m_amount(amount)
{

}

Pill::Pill(const Pill &p) :
    m_name(p.name()), m_lifeTime(p.getLifeTime()), m_beforeFlag(p.beforeFlag()), m_takeTimeMask(p.takeTimeMask()), m_amount(p.getAmount())
{

}

QString Pill::name() const
{
    return m_name;
}

void Pill::setName(const QString &name)
{
    m_name = name;
}

bool Pill::beforeFlag() const
{
    return m_beforeFlag;
}

void Pill::setBeforeFlag(bool beforeFlag)
{
    m_beforeFlag = beforeFlag;
}

int Pill::takeTimeMask() const
{
    return m_takeTimeMask;
}

void Pill::setTakeTimeMask(int takeTimeMask)
{
    m_takeTimeMask = takeTimeMask;
}

QString Pill::getAmount() const
{
    return m_amount;
}

void Pill::setAmount(const QString &value)
{
    m_amount = value;
}

int Pill::getLifeTime() const
{
    return m_lifeTime;
}

void Pill::setLifeTime(int lifeTime)
{
    m_lifeTime = lifeTime;
}
