#ifndef PRIORITYWINDOW_H
#define PRIORITYWINDOW_H

#include <QDialog>
#include <taskmanager.h>
#include <iostream>
namespace Ui {
class priorityWindow;
}

class priorityWindow : public QDialog
{
    Q_OBJECT

public:
    explicit priorityWindow(QWidget *parent = 0,TaskManager *tm = 0, int pid = -1, QString name = "", int currentPriority = -1);
    ~priorityWindow();

private slots:
    void on_setPB_clicked();

    void on_setPB_2_clicked();

private:
    Ui::priorityWindow *ui;
    int mPid;
    QString mPname;
    int mCurrentP;
    TaskManager* mTm;

};

#endif // PRIORITYWINDOW_H
