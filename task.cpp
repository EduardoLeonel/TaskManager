#include "task.h"
#include <QStringList>
#include <iostream>

using namespace std;

Task::Task(QString data){
    QStringList datos = data.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    //cout<<"part 0 is : "<< datos.at(0).toStdString()<<" splited into "<<datos.size()<<" parts"<<endl;
    if(datos.size()>0)
        mPid = datos.at(0).toInt(0,10);
}

int Task::getID(){
    return this->mPid;
}
