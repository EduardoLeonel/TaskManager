#ifndef TASK_H
#define TASK_H

#include <QString>
#include <qstringlist.h>
#include <QMap>
#include <QObject>
#include <pthread.h>

class Task : public QObject {
    Q_OBJECT
public:
    Task(QString);
    ~Task();
    int getID();
    QString getDescription();
    QString getState();
    double  getCpuUse();
    double  getMemoryUse();
    double  getDiskUse();
    int     getPriority();
    int     getRow();
    static void setStatesHumanvalues();
    static void setKeysStates();
    static void setKeysValues();
    QString setmState(QString);
    void setRowID(int);
    void doUpdate(const char* );
    static void* update(void*);
    QString execute(const char *);
    pthread_t* getUpdateThread();

signals:
     void updated(Task*);

private:
    static QMap<QString,QString> statesHumanValues;
    static int RUNNING;
    void parseData();
    void emitUpdated();
    int mPid;
    int mRowId;
    pthread_t* mUpdateThread;
    QString mDescription;
    QString mState;
    QString mDataString;
    double mCPUUse;
    double mMemoryUse;
    double mDiskUse;
    int mPriority;
    static QStringList keysStates;
    static QStringList valueofStates;


};

#endif // TASK_H
