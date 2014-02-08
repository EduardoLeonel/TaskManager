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
        Task* tarea = iterador.value();
        char pid[128];
        sprintf(pid,"%d",tarea->getID() );
        tabla->insertRow(pCount);
        QTableWidgetItem* item= new QTableWidgetItem(pid);
        tabla->setItem(pCount,0,item); //choose the cell u want for your item
        pCount++;
    }
}

//Destructor
MainWindow::~MainWindow(){
    delete ui;
}


