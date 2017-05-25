#ifndef PLANFILESMANAGER_H
#define PLANFILESMANAGER_H

#include <QString>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

class PlanFilesManager
{
public:
    static QString getNextFileNameAvailable();
    static QStringList getPlanList();
};

#endif // PLANFILESMANAGER_H
