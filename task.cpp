#include "task.h"
#include <QStringList>
#include <iostream>
#include <QString>


using namespace std;

//Static Fields
QStringList Task::keysStates;
QStringList Task::valueofStates;
QMap<QString,QString> Task::statesHumanValues;
int Task::RUNNING;

Task::Task(QString data){
    mUpdateThread = new pthread_t();
    this->mDataString = data;
    this->parseData();
    Task::RUNNING = 1;
}

void Task::parseData(){
    QStringList datos = this->mDataString.split(QRegExp("\\s+|\\t+"),QString::SkipEmptyParts);

    if(datos.size() >= 6){
        this->mPid = datos.at(1).toInt(0,10);
        this->mState = this->setmState(datos.at(2));
        this->mCPUUse = datos.at(3).toDouble(0);
        this->mMemoryUse = datos.at(4).toDouble(0);
        this->mDescription = datos.at(5);
        this->mDiskUse = 0.0;
        if(datos.size() > 6){
            for(int i = 6; i < datos.size(); i++){
                this->mDescription += " " +datos.at(i);
            }
        }
    }

}

void Task::doUpdate(const char* command){
    QString data = this->execute(command);
    QStringList salida = data.split("\n");
    if(salida.size() < 2){
        return;
    }
    data = salida.at(1);
    if(this->mDataString.compare(data) != 0){
        this->mDataString = data;
        this->parseData();
        //this->emitUpdated();
        emit updated(this);
    }
}


void* Task::update(void* param){
    Task* tarea =(Task*)param;
    char command[256];
    sprintf(command,"ps -o user,pid,state,pcpu,pmem,command -p %d",tarea->getID());
    //cout<<"trying to update process with: "<<command;
    while(Task::RUNNING == 1){
        if(tarea != 0){
            tarea->doUpdate(command);
        }
        sleep(2);
    }
    return (void*)0;
}
QString Task::execute(const char * cmd){
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

void Task::setRowID(int id){
    this->mRowId = id;
}

pthread_t* Task::getUpdateThread(){
    return this->mUpdateThread;
}

int Task::getID(){
    return this->mPid;
}

int Task::getRow(){
    return this->mRowId;
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
    //cout<<val.toStdString()<<endl;
    QMap<QString,QString>::iterator it;
    for (int i = 0; i < val.size(); i++){
        it = Task::statesHumanValues.find(val.at(i));
        if(it != Task::statesHumanValues.end()){
            ret+=it.value()+" ";
        }
    }
    return ret;
}

Task::~Task(){
    Task::RUNNING = 0;
}

