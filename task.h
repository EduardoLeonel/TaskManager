#ifndef TASK_H
#define TASK_H

#include <QString>


class Task{
public:
    Task(QString);
    int getID();

private:
    int mPid;
    QString mDescription;
    QString mState;
    double mCPUUse;
    double mMemoryUse;
    double mDiskUse;
};

#endif // TASK_H
