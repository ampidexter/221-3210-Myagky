// Ваш файл details.cpp

#include "details.h"
#include "ui_details.h"

Details::Details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Details)
{
    ui->setupUi(this);
}

Details::~Details()
{
    delete ui;
}

// Обновленный слот для отображения деталей
void Details::displayDetails(const QString &website, const QString &username, const QString &password)
{
    ui->websiteLabel->setText(website);
    ui->usernameLabel->setText(username);
    ui->passwordLabel->setText(password);
}
