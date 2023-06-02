#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegularExpression rx("^(-?)[1-9][0-9]{1,15}([\.][0-9]{1,2})?$");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit->setValidator(validator);

    QSqlDatabase mybd=QSqlDatabase::addDatabase("QSQLITE");
    mybd.setDatabaseName("new.db");
    if (mybd.open())
    {
        ui->label->setText("База даних відкрита");
    }
    else
    {
        ui->label->setText("Закрита");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QString amount = ui->lineEdit->text();
    QString type = ui->lineEdit_2->text();
    QString account = ui->lineEdit_3->text();
    QSqlQuery query;
    if(ui->comboBox->currentText()=="income"){
        QString query_string = "insert into income(account, type, sum) values("+account+","+"'"+type+"',"+amount+");";
        if (query.exec(query_string))
        {
          ui->label->setText("Запис додано");
        }
        else
        {
          ui->label->setText("Запис не додано");
          qDebug() << query.lastError();
        }
    }else{
        QString query_string = "insert into expence(account, type, sum) values("+account+","+"'"+type+"',"+amount+");";
        if (query.exec(query_string))
        {
          ui->label->setText("Запис додано");
        }
        else
        {
          ui->label->setText("Запис не додано");
          qDebug() << query.lastError();
        }
    }
}

