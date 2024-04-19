// Ваш файл pininputdialog.h

#ifndef PININPUTDIALOG_H
#define PININPUTDIALOG_H

#include <QDialog>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QPushButton>

namespace Ui {
class pininputdialog;
}

class pininputdialog : public QDialog
{
    Q_OBJECT

public:
    explicit pininputdialog(QWidget *parent = nullptr);
    ~pininputdialog();

    QString getKey(const QString &password); // Объявление метода для вычисления хеша пароля
    Ui::pininputdialog *ui;

private slots:
    void handleContinueButtonClick(); // Объявление слота для обработки нажатия кнопки "continueBtn"


};

#endif // PININPUTDIALOG_H
