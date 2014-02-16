#include "prioritywindow.h"
#include "ui_prioritywindow.h"

priorityWindow::priorityWindow(QWidget *parent, TaskManager *tm, int pid, QString name, int currentPriority) :
    QDialog(parent),
    ui(new Ui::priorityWindow)
{
    ui->setupUi(this);
    this->mPid = pid;
    this->mPname = name;
    this->mCurrentP = currentPriority;
    this->mTm = tm;
    this->setWindowTitle("Priority");
    this->ui->pnameLabel->setText(this->mPname);
    this->ui->currentPriorityLabel->setText(QString("%1").arg(mCurrentP));
}


priorityWindow::~priorityWindow()
{
    delete ui;
}


void priorityWindow::on_setPB_clicked()
{
    if (!ui->priLE->text().isEmpty()){
        this->mTm->execute(QString("renice %1 -p %2").arg(ui->priLE->text(),QString("%1").arg(this->mPid)).toStdString().c_str());
        this->close();
    }
}

void priorityWindow::on_setPB_2_clicked()
{
    this->close();
}
