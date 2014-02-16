#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#import <qmap>
#import <task.h>
#import <QString>
#import <stdio.h>
#include <QObject>
#include <pthread.h>

class TaskManager : public QObject{
    Q_OBJECT
    public:
        TaskManager();
        ~TaskManager();
        void loadTasks();
        static QString execute(const char *);
        QMap<int,Task*>* getTasks();
        static void* updateProcessData(void*);
        static int UPDATE_INTERVAL;
        static int UPDATE;

signals:
     void updated(QMap<int,Task*>*);


    private:
        QMap<int,Task*>* mTasks;
};

#endif // TASKMANAGER_H
