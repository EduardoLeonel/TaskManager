#include "taskmanager.h"
#include <iostream>
#include <stdio.h>
#include <QStringList>
using namespace std;

int TaskManager::UPDATE;
int TaskManager::UPDATE_INTERVAL;

TaskManager::TaskManager(){
    UPDATE = 1;
    UPDATE_INTERVAL = 3;
    this->mTasks = new QMap<int,Task*>();
    this->loadTasks();
}


void TaskManager::loadTasks(){
    QString salida = this->execute("ps -e -c -o user,pid,state,pcpu,pmem,pri,command");
    QStringList procesos = salida.split("\n");
    //cout<<"Loaded "<<procesos.size()<<endl;
    for(int i = 1; i < procesos.size(); i++){
        Task* tarea = new Task(procesos.at(i));
        mTasks->insert(i,tarea);     
    }
    emit updated(mTasks);
}

void* TaskManager::updateProcessData(void* tm){
    TaskManager* taskManager = (TaskManager*)tm;
    while(TaskManager::UPDATE == 1){
        taskManager->loadTasks();
        sleep(TaskManager::UPDATE_INTERVAL);
    }   
    return (void*)0;
}

QString TaskManager::execute(const char * cmd){
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return QString("ERROR");
    char buffer[128];
    QString result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

QMap<int,Task*>* TaskManager::getTasks(){
    return this->mTasks;
}

void TaskManager::killProcess(int pid){
    this->execute(QString("kill -9 %1").arg(pid).toStdString().c_str());
}


TaskManager::~TaskManager(){
    QMap<int,Task*>::iterator iterador;
    UPDATE = 0;
    for(iterador = mTasks->begin(); iterador != mTasks->end(); iterador++){
        Task* tarea = iterador.value();
        delete tarea;
    }
    delete mTasks;
}
