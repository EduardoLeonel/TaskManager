#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <taskmanager.h>
#include <QMap>
#include <prioritywindow.h>
#include <openedfiles.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void updateTask(Task*);
    void setTasks(QMap<int,Task*>*);
    void ShowContextMenu(const QPoint&);
    void setTableOptions();
private:
    Ui::MainWindow *ui;
    TaskManager* mTaskManager;
    pthread_t* mUpdateThread;
    openedfiles* mOpenedFiles;
    int mSortColumn;
};

#endif // MAINWINDOW_H
