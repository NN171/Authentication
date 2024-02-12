#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseconnection.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerPushButton_clicked()
{
    {
        QString name = ui->nameLineEdit->text();
        QString email = ui->emailLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        DatabaseConnection connection;

        if (connection.Connect()){
            qDebug() << "Connected" << endl;
        }

        QSqlQuery query;
        if (query.exec("INSERT INTO login_table (Name, Email, Password) VALUES ('"+name+"', '"+email+"', '"+password+"')")){
            qDebug() << "Query executed" << endl;
        }

        connection.Disconnect();
    }

}

void MainWindow::on_loginPushButton_clicked()
{
    QString email = ui->emailLogLineEdit->text();
    QString password = ui->passwordLogLineEdit->text();

    DatabaseConnection con;
    if (con.Connect()){
        qDebug() << "Connected" << endl;
    }
    QSqlQuery query;

    if (query.exec("SELECT * FROM login_table WHERE Email = '"+email+"' and Password = '"+password+"'")){
        qDebug() << "Query executed" << endl;
        int c = 0;
        while (query.next()) ++c;

        if (c >= 1)
            QMessageBox::information(this, "Info", "Login Succesful");
        else
            QMessageBox::information(this, "Info", "Couldn't login");
    }

    con.Disconnect();
}
