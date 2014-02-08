#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#import <qmap>
#import <task.h>
#import <QString>
#import <stdio.h>

class TaskManager{
    public:
        TaskManager();
        void loadTasks();
        QString execute(const char *);
        QMap<int,Task*>* getTasks();

    private:
        QMap<int,Task*>* mTasks;
};

#endif // TASKMANAGER_H
