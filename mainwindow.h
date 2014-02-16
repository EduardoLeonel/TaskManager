#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <taskmanager.h>
#include <QMap>
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
private:
    Ui::MainWindow *ui;
    TaskManager* mTaskManager;
    pthread_t* mUpdateThread;
    int mSortColumn;
};

#endif // MAINWINDOW_H
