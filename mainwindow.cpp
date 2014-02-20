#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "numericitem.h"
#include <QTableWidgetItem>
#include <iostream>
#include <stdio.h>
#include <QAction>
#include <QObject>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    setTableOptions();
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
        char priority[16];
        sprintf(pid,"%d",tarea->getID());
        sprintf(cpuUse,"%0.2f",tarea->getCpuUse());
        sprintf(memUse,"%0.2f",tarea->getMemoryUse());
        sprintf(diskUse,"%0.2f",tarea->getDiskUse());
        sprintf(priority,"%d",tarea->getPriority());

        if(tabla->rowCount() < pCount+1)
            tabla->insertRow(pCount);

        tabla->setItem(pCount,cCount,new NumericItem(pid));
        tabla->setItem(pCount,cCount + 1,new QTableWidgetItem(tarea->getDescription()));
        tabla->setItem(pCount,cCount + 2,new QTableWidgetItem(tarea->getState()));
        tabla->setItem(pCount,cCount + 3,new QTableWidgetItem(cpuUse));
        tabla->setItem(pCount,cCount + 4,new QTableWidgetItem(memUse));
        //tabla->setItem(pCount,cCount + 5,new QTableWidgetItem(diskUse));
        tabla->setItem(pCount,cCount + 5,new QTableWidgetItem(priority));
        tarea->setRowID(pCount);
        //QObject::connect(tarea,SIGNAL(updated(Task*)),this,SLOT(updateTask(Task*)));
    }

    for(int x = tareas->size(); x < tabla->rowCount(); x++){
        tabla->removeRow(x);
    }

    ui->task_table->sortByColumn(mSortColumn);
}

void MainWindow::updateTask(Task* tarea){

}


void MainWindow::ShowContextMenu(const QPoint& pos){
    // for most widgets
    QPoint globalPos = ui->task_table->mapToGlobal(pos);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    int cRow = ui->task_table->currentRow();

    QMenu myMenu;

    //acciones
    QAction* killAction = new QAction(this);
    QAction* priorityAction = new QAction(this);
    QAction* openedFilesAction = new QAction(this);

    myMenu.setTitle("Menu");
    if(cRow >= 0){
        QString name = ui->task_table->item(cRow,1)->text();
        //myMenu.addAction("Kill " + name);
        if (name.size() > 50){
            killAction->setText("Kill " + name.mid(1,45)+"...");
        }else{
            killAction->setText("Kill " + name);
        }
        priorityAction->setText("Priority");
        openedFilesAction->setText("Show opened files");
        myMenu.addAction(killAction);
        myMenu.addAction(priorityAction);
        myMenu.addAction(openedFilesAction);
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
        if( selectedItem->text().compare("Name") == 0){
            mSortColumn = 1;
        }else if( selectedItem->text().compare("PID") == 0 ){
            mSortColumn = 0;
        }else if(selectedItem == killAction){
            this->mTaskManager->killProcess(ui->task_table->item(cRow,0)->text().toInt());
        }else if (selectedItem == openedFilesAction){
            openedfiles* openedFilesW = new openedfiles(0,this->mTaskManager,ui->task_table->item(cRow,0)->text().toInt());
            openedFilesW->show();
        }else if (selectedItem == priorityAction){
            priorityWindow* priorityW = new priorityWindow(this,this->mTaskManager,ui->task_table->item(cRow,0)->text().toInt(),
                                                           ui->task_table->item(cRow,1)->text(),ui->task_table->item(cRow,5)->text().toInt());
            priorityW->show();
        }
        ui->task_table->sortByColumn(mSortColumn,Qt::AscendingOrder);
    }else{
        // nothing was chosen
    }
}

void MainWindow::setTableOptions(){
    this->setWindowTitle("TaskManager");
    this->ui->task_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->task_table->setSelectionMode( QAbstractItemView::SingleSelection );
    this->ui->task_table->setColumnWidth(1,250);
    this->ui->task_table->setColumnWidth(5,135);
    this->ui->task_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


//Destructor
MainWindow::~MainWindow(){
    delete ui;
    delete mTaskManager;
}




