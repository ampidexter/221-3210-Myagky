#ifndef ACCOUNTDETAILSDIALOG_H
#define ACCOUNTDETAILSDIALOG_H

#include <QDialog>

namespace Ui {
class AccountDetailsDialog;
}

class AccountDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDetailsDialog(QWidget *parent = nullptr);
    ~AccountDetailsDialog(); // Объявление деструктора
    // Добавляем статический метод для создания экземпляра класса
    static AccountDetailsDialog* create(const QString &website, const QString &username, const QString &password, QWidget *parent = nullptr)
    {
        return new AccountDetailsDialog(website, username, password, parent);
    }

private:
    Ui::AccountDetailsDialog *ui;
    // Приватный конструктор
    AccountDetailsDialog(const QString &website, const QString &username, const QString &password, QWidget *parent = nullptr)
        : QDialog(parent), m_website(website), m_username(username), m_password(password)
    {
        // Остальная инициализация окна
    }

    QString m_website;
    QString m_username;
    QString m_password;
};


#endif // ACCOUNTDETAILSDIALOG_H
