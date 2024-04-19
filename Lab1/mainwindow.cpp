#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datawindow.h"
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


void MainWindow::on_login_button_clicked()
{
    QString password = ui->pass->text();
    if(password == master_password){
        hide();
        datawindow = new DataWindow(this);
        datawindow->getKey(password);
        datawindow->show();
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Введён неверный пароль!");
    }
}

