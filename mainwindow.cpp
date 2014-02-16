#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "numericitem.h"
#include <QTableWidgetItem>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->mTaskManager = new TaskManager();
    this->setTasks(mTaskManager->getTasks());
    mUpdateThread = new pthread_t();
    pthread_create( mUpdateThread, NULL, &(TaskManager::updateProcessData), (void*)mTaskManager);
    QObject::connect(mTaskManager,SIGNAL(updated(QMap<int,Task*>*)),this,SLOT(setTasks(QMap<int,Task*>*)));

    ui->task_table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->task_table, SIGNAL(customContextMenuRequested(const QPoint&)),
                this, SLOT(ShowContextMenu(const QPoint&)));
}


void MainWindow::setTasks(QMap<int,Task*>* tareas){
    QTableWidget* tabla = this->ui->task_table;
    QMap<int,Task*>::iterator iterador;


    for(iterador = tareas->begin(); iterador != tareas->end(); iterador++){
        int cCount = 0;
        int pCount = iterador.key()-1;
        Task* tarea = iterador.value();
        char pid[128];
        char cpuUse[128];
        char memUse[128];
        char diskUse[128];
        sprintf(pid,"%d",tarea->getID());
        sprintf(cpuUse,"%0.2f",tarea->getCpuUse());
        sprintf(memUse,"%0.2f",tarea->getMemoryUse());
        sprintf(diskUse,"%0.2f",tarea->getDiskUse());

        if(tabla->rowCount() < pCount+1)
            tabla->insertRow(pCount);

        tabla->setItem(pCount,cCount,new NumericItem(pid));
        tabla->setItem(pCount,cCount + 1,new QTableWidgetItem(tarea->getDescription()));
        tabla->setItem(pCount,cCount + 2,new QTableWidgetItem(tarea->getState()));
        tabla->setItem(pCount,cCount + 3,new QTableWidgetItem(cpuUse));
        tabla->setItem(pCount,cCount + 4,new QTableWidgetItem(memUse));
        tabla->setItem(pCount,cCount + 5,new QTableWidgetItem(diskUse));
        tarea->setRowID(pCount);
        //QObject::connect(tarea,SIGNAL(updated(Task*)),this,SLOT(updateTask(Task*)));
    }
    ui->task_table->sortByColumn(mSortColumn);
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


void MainWindow::ShowContextMenu(const QPoint& pos){
    // for most widgets
    QPoint globalPos = ui->task_table->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    int cRow = ui->task_table->currentRow();

    QMenu myMenu;
    myMenu.setTitle("Menu");
    if(cRow >= 0){
        QString name = ui->task_table->item(cRow,1)->text();
        myMenu.addAction("Kill " + name);
    }
    QMenu sortMenu;
    sortMenu.setTitle("Sort by");
    sortMenu.addAction("PID");
    sortMenu.addAction("Name");
    sortMenu.addAction("CPU");
    sortMenu.addAction("MEM");

    myMenu.addMenu(&sortMenu);

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem){
        if( selectedItem->text().compare("Name") == 0 ){
            mSortColumn = 1;
        }else if( selectedItem->text().compare("PID") == 0 ){
            mSortColumn = 0;
        }
        ui->task_table->sortByColumn(mSortColumn,Qt::AscendingOrder);
    }else{
        // nothing was chosen
    }
}


//Destructor
MainWindow::~MainWindow(){
    delete ui;
    delete mTaskManager;
}


