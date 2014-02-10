#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QStringlist>
#include <QMap>

class Task{
public:
    Task(QString);
    int getID();
    QString getDescription();
    QString getState();
    double  getCpuUse();
    double  getMemoryUse();
    double  getDiskUse();
    static void setStatesHumanvalues();
    static void setKeysStates();
    static void setKeysValues();
    QString setmState(QString);


private:
    static QMap<QString,QString> statesHumanValues;
    int mPid;
    QString mDescription;
    QString mState;
    double mCPUUse;
    double mMemoryUse;
    double mDiskUse;
    static QStringList keysStates;
    static QStringList valueofStates;
};

#endif // TASK_H
