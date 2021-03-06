#include "openedfiles.h"
#include "ui_openedfiles.h"

int openedfiles::UPDATE_INTERVAL;
int openedfiles::UPDATE;

openedfiles::openedfiles(QWidget *parent, TaskManager *tm, int pid) :
    QWidget(parent),
    ui(new Ui::openedfiles)
{
    UPDATE_INTERVAL = 2;
    UPDATE = 1;
    ui->setupUi(this); this->ui->filesTable->setColumnWidth(0,420);
    this->ui->filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->filesTable->setSelectionMode( QAbstractItemView::SingleSelection );
    this->ui->filesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->mtm = tm;
    this->mpid = pid;
    this->mDataString = QString("lsof -p %1 -s -Fns").arg(this->mpid);
    mUpdateThread = new pthread_t();
    pthread_create( mUpdateThread, NULL, &(openedfiles::updateFiles), (void*)this);
    this->loadFiles();
}

void openedfiles::loadFiles(){
    QStringList x = this->mtm->execute(QString("lsof -p %1 -s ").arg(this->mpid).toStdString().c_str()).split("\n");
    this->cFiles = x.size() - 1;

    QString data = this->mtm->execute(this->mDataString.toStdString().c_str());
    this->mfiles = data.split("\n");
    setData();
}

void* openedfiles::updateFiles(void* param){
    openedfiles* uf = (openedfiles*)param;
    while(UPDATE){
        uf->loadFiles();
        sleep(UPDATE_INTERVAL);
    }
    return (void*)0;
}


void openedfiles::setData(){
     QTableWidget* tabla = this->ui->filesTable;
    if(this->cFiles < 1){
        for (int i = 0 ; i < tabla->rowCount() ; i++)
            tabla->removeRow(i);
        return;
    }

    int c = 1;
    /*if (tabla->rowCount() > 0)
        for (int i = 0 ; i < tabla->rowCount() ; i++)
            tabla->removeRow(i);
    */
    for (int i = 0 ; i <= this->cFiles ; i++){
        if(tabla->rowCount() < i + 1)
            tabla->insertRow(i);

        QString dato = this->mfiles.at(c);

        if(dato.mid(1,dato.size()).toInt() ){
            if (c+2 < this->mfiles.size()){
                tabla->setItem((i),1,new QTableWidgetItem(dato.mid(1,dato.size())));
                tabla->setItem((i),0,new QTableWidgetItem(mfiles.at(c+1).mid(1,mfiles.at(c+1).size())));
                c+=2;
            }
        }else{
            if (c+2 < this->mfiles.size()){
                if (dato.mid(1,dato.size())=="0"){
                    tabla->setItem((i),1,new QTableWidgetItem("0"));
                    tabla->setItem((i),0,new QTableWidgetItem(mfiles.at(c+1).mid(1,mfiles.at(c+1).size())));
                    c+=2;
                }else{
                    tabla->setItem((i),1,new QTableWidgetItem("-"));
                    tabla->setItem((i),0,new QTableWidgetItem(dato.mid(1,dato.size())));
                    c++;
                }
            }
        }
    }


    //limpiar
    for(int x = this->cFiles; x < tabla->rowCount(); x++){
        tabla->removeRow(x);
    }
}

openedfiles::~openedfiles()
{
    UPDATE = 0;
    delete ui;
}

void openedfiles::on_pushButton_clicked()
{
    this->close();
}
