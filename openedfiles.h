#ifndef OPENEDFILES_H
#define OPENEDFILES_H

#include <QWidget>
#include "taskmanager.h"
#include <pthread.h>
#include <iostream>

using namespace std;

namespace Ui {
class openedfiles;
}

class openedfiles : public QWidget
{
    Q_OBJECT

public:
    explicit openedfiles(QWidget *parent = 0,TaskManager* tm = 0, int pid = -1);
    ~openedfiles();
    void loadFiles();
    void setData();
    static void* updateFiles(void*);
private slots:
    void on_pushButton_clicked();

private:
    Ui::openedfiles *ui;
    pthread_t* mUpdateThread;
    TaskManager* mtm;
    int mpid;
    QStringList mfiles;
    QString mDataString;
    int cFiles;  //how many files are open!
    static int UPDATE_INTERVAL;
    static int UPDATE;
};

#endif // OPENEDFILES_H
