#include "planfilesmanager.h"


QString PlanFilesManager::getNextFileNameAvailable()
{
    QStringList list = PlanFilesManager::getPlanList();
    if (list.isEmpty()) {
        return "plan1.mdp";
    }
    list.sort();
    QString res = list.last();
    res.chop(4);
    QString n;
    while (res[res.size() - 1].isDigit()) {
        n.append(res[res.size() - 1]);
        res.chop(1);
    }
    std::reverse(n.begin(), n.end());
    bool ok;
    int ri = n.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(NULL, "Не могу узнать последний номер созданного плана", "Будет использован файл plan1.mdp", QMessageBox::Ok);
        res = "plan1.mdp";
    }
    else {
        ri++;
        res = "plan" + QString::number(ri) + ".mdp";
    }
    return res;
}

QStringList PlanFilesManager::getPlanList()
{
    QDir qd;
    QStringList res;
    for (QString s : qd.entryList()) {
        QFile f(s);
        QFileInfo fi(f);
        if (fi.isFile() && fi.fileName().endsWith(".mdp") && fi.fileName().startsWith("plan")) {
            res.append(fi.fileName());
        }
    }
    return res;
}
