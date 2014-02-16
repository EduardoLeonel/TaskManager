#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->mTaskManager = new TaskManager();
    this->setTasks(mTaskManager->getTasks());
}


void MainWindow::setTasks(QMap<int,Task*>* tareas){
    QTableWidget* tabla = this->ui->task_table;
    QMap<int,Task*>::iterator iterador;

    int pCount = 0;

    for(iterador = tareas->begin(); iterador != tareas->end(); iterador++){
        int cCount = 0;
        Task* tarea = iterador.value();
        char pid[128];
        char cpuUse[128];
        char memUse[128];
        char diskUse[128];
        sprintf(pid,"%d",tarea->getID());
        sprintf(cpuUse,"%0.2f",tarea->getCpuUse());
        sprintf(memUse,"%0.2f",tarea->getMemoryUse());
        sprintf(diskUse,"%0.2f",tarea->getDiskUse());

        tabla->insertRow(pCount);

        tabla->setItem(pCount,cCount,new QTableWidgetItem(pid));
        tabla->setItem(pCount,cCount + 1,new QTableWidgetItem(tarea->getDescription()));
        tabla->setItem(pCount,cCount + 2,new QTableWidgetItem(tarea->getState()));
        tabla->setItem(pCount,cCount + 3,new QTableWidgetItem(cpuUse));
        tabla->setItem(pCount,cCount + 4,new QTableWidgetItem(memUse));
        tabla->setItem(pCount,cCount + 5,new QTableWidgetItem(diskUse));
        tarea->setRowID(pCount);
        QObject::connect(tarea,SIGNAL(updated(Task*)),this,SLOT(updateTask(Task*)));
        pCount++;
    }
}

void MainWindow::updateTask(Task* tarea){
    QTableWidget* tabla = this->ui->task_table;
    int cCount = 0;
    int row  =tarea->getRow();
    char pid[128];
    char cpuUse[128];
    char memUse[128];
    char diskUse[128];
    sprintf(pid,"%d",tarea->getID());
    sprintf(cpuUse,"%0.2f",tarea->getCpuUse());
    sprintf(memUse,"%0.2f",tarea->getMemoryUse());
    sprintf(diskUse,"%0.2f",tarea->getDiskUse());

    tabla->setItem(row,cCount,new QTableWidgetItem(pid));
    tabla->setItem(row,cCount + 1,new QTableWidgetItem(tarea->getDescription()));
    tabla->setItem(row,cCount + 2,new QTableWidgetItem(tarea->getState()));
    tabla->setItem(row,cCount + 3,new QTableWidgetItem(cpuUse));
    tabla->setItem(row,cCount + 4,new QTableWidgetItem(memUse));
    tabla->setItem(row,cCount + 5,new QTableWidgetItem(diskUse));
}

//Destructor
MainWindow::~MainWindow(){
    delete ui;
    delete mTaskManager;
}


