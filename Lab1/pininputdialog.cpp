// Ваш файл pininputdialog.cpp

#include "pininputdialog.h"
#include "ui_pininputdialog.h"
#include "details.h" // Подключаем заголовочный файл details.h, если это не сделано ранее

pininputdialog::pininputdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pininputdialog)
{
    ui->setupUi(this);

    // Подключаем обработчик событий для кнопки "continueBtn"
    connect(ui->continueBtn, &QPushButton::clicked, this, &pininputdialog::handleContinueButtonClick);
}

pininputdialog::~pininputdialog()
{
    delete ui;
}

void pininputdialog::handleContinueButtonClick()
{
    QString password = ui->pinLineEdit->text();

    QString hashedPassword = getKey(password);

    QString constantHash = "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4";

    if (hashedPassword == constantHash) {
        accept();
        Details detailsWindow;
        detailsWindow.exec();

    } else {
        QMessageBox::warning(this, tr("Warning"), tr("Invalid password. Please try again."));
    }
}

QString pininputdialog::getKey(const QString &password)
{
    // Вычисляем хеш SHA-256 пароля
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    qDebug() << hashedPassword.toHex();
    return QString(hashedPassword.toHex());
}
