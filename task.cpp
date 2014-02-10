#include "task.h"
#include <QStringList>
#include <iostream>
#include <QString>

using namespace std;

//Static Fields
QStringList Task::keysStates;
QStringList Task::valueofStates;
QMap<QString,QString> Task::statesHumanValues;

Task::Task(QString data){

    QStringList datos = data.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    if(datos.size() > 0){
        this->mPid = datos.at(1).toInt(0,10);
        this->mDescription = datos.at(2);
        this->mState = this->setmState(datos.at(3));
        this->mCPUUse = datos.at(4).toDouble(0);
        this->mMemoryUse = datos.at(5).toDouble(0);
        this->mDiskUse = 0.0;
    }

}

int Task::getID(){
    return this->mPid;
}

QString Task::getDescription(){
    return this->mDescription;
}

QString Task::getState(){

    return this->mState;
}

double Task::getCpuUse(){
    return this->mCPUUse;
}

double Task::getMemoryUse(){
    return this->mMemoryUse;
}

double Task::getDiskUse(){
    return this->mDiskUse;
}

void Task::setStatesHumanvalues(){
    for (int i = 0 ; i < 17; i++)
        Task::statesHumanValues.insert(Task::keysStates[i],Task::valueofStates[i]);
}

void Task::setKeysStates(){
    QString x = "I,R,S,T,U,Z,+,<,>,A,E,L,N,s,V,W,X";
    Task::keysStates = x.split(",");
}

void Task::setKeysValues(){
    QString x =  "Idle,Running,Sleeping,Stopped,Uninterruptible wait,Zombie,Foreground,<,>, Asked for random page, Trying to exit,Has pages locked in core,N,Session leader,Suspended during a vfork,Swapped out, Being traced or debugged";
    Task::valueofStates = x.split(",");
}

QString Task::setmState(QString val){
    //lazy loader
    if(Task::statesHumanValues.size() <= 0){
        this->setKeysStates();
        this->setKeysValues();
        this->setStatesHumanvalues();
    }
    QString ret = val+":";
    cout<<val.toStdString()<<endl;
    for (int i = 0; i < val.size(); i++){
        ret+=Task::statesHumanValues.find(val.at(i)).value()+" ";
    }
    return ret;
}

