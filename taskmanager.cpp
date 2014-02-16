#include "taskmanager.h"
#include <iostream>
#include <QStringList>
using namespace std;

TaskManager::TaskManager(){
    this->mTasks = new QMap<int,Task*>();
    this->loadTasks();
}


void TaskManager::loadTasks(){
    QString salida = this->execute("ps -e -o user,pid,state,pcpu,pmem,command");
    QStringList procesos = salida.split("\n");
    cout<<"Loaded "<<procesos.size()<<endl;
    for(int i = 1; i < procesos.size(); i++){
        Task* tarea = new Task(procesos.at(i));
        mTasks->insert(i,tarea);
        pthread_create( tarea->getUpdateThread(), NULL, &(Task::update), (void*)tarea);
    }

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

TaskManager::~TaskManager(){
    QMap<int,Task*>::iterator iterador;
    for(iterador = mTasks->begin(); iterador != mTasks->end(); iterador++){
        Task* tarea = iterador.value();
        delete tarea;
    }
    delete mTasks;
}
