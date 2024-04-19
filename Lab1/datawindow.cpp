#include "datawindow.h"
#include "ui_datawindow.h"
#include "pininputdialog.h"
#include "ui_pininputdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <QCryptographicHash>
#include <QDebug>
#include <QPushButton>



//static const QString IV = "000102030405060708090a0b0c0d0e0f"; // Инициализируем IV


DataWindow::DataWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataWindow)
{
    ui->setupUi(this);
    connect(this, &DataWindow::accountDetailsRequested, this, &DataWindow::openAccountDetails);

}

DataWindow::~DataWindow()
{
    delete ui;
}

void DataWindow::populateData(const QString &decryptedText, const QString &filterText)
{
    // Парсим расшифрованный текст в JSON-массив
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(decryptedText.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing decrypted JSON:" << parseError.errorString();
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();

    // Очистка существующего макета
    QLayout *existingLayout = ui->scrollAreaWidgetContents->layout();
    if (existingLayout) {
        QLayoutItem *child;
        while ((child = existingLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        delete existingLayout;
    }

    QVBoxLayout *outerLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);

    for (const QJsonValue &value : jsonArray) {
        if (!value.isObject()) {
            qDebug() << "Array element is not an object.";
            continue;
        }

        QJsonObject jsonObj = value.toObject();
        QString website = jsonObj.value("website").toString();
        QString username = jsonObj.value("username").toString();
        QString password = jsonObj.value("password").toString();

        // Проверяем, соответствует ли запись фильтру
        if (!filterText.isEmpty() && !website.contains(filterText, Qt::CaseInsensitive))
            continue;

        QFrame *frame = new QFrame();
        frame->setFrameShape(QFrame::Box); // Устанавливаем форму рамки
        frame->setFrameShadow(QFrame::Raised); // Устанавливаем тень для рамки

        QHBoxLayout *entryLayout = new QHBoxLayout(frame);

        QLabel *imageLabel = new QLabel();
        QPixmap placeholder("/Users/ampidexter/Lab1/placeholder.svg"); // Путь к изображению заглушки
        imageLabel->setPixmap(placeholder.scaled(32, 32)); // Устанавливаем размер изображения

        QLabel *urlLabel = new QLabel(website);
        QLabel *usernameLabel = new QLabel("******"); // Используем имя пользователя из JSON
        QLabel *passwordLabel = new QLabel("*****"); // Используем пароль из JSON

        entryLayout->addWidget(imageLabel);
        entryLayout->addWidget(urlLabel);
        entryLayout->addWidget(usernameLabel);
        entryLayout->addWidget(passwordLabel);

        // Установка стилей для изменения цвета при наведении курсора
        frame->setStyleSheet("QFrame:hover { background-color: #696969; }");

        // Create a button for each account entry
        QPushButton *detailsButton = new QPushButton("Details");
        connect(detailsButton, &QPushButton::clicked, this, [this, website, username, password]() {
            emit accountDetailsRequested(website, username, password);
        });

        entryLayout->addWidget(detailsButton);

        outerLayout->addWidget(frame);
        ui->scrollAreaWidgetContents->setLayout(outerLayout);
    }

}


void DataWindow::getKey(const QString &pin)
{
    // Хешируем пин-код
    QByteArray hashedPin = QCryptographicHash::hash(pin.toUtf8(), QCryptographicHash::Sha256);
    // Преобразуем хэш в строку в шестнадцатеричном формате
    QString key = hashedPin.toHex();

    qDebug() << "Key:" << key;

    // Инициализируем вектор инициализации (IV) в соответствии с требованиями
    std::string ivHex = "000102030405060708090a0b0c0d0e0f";


    // Открываем файл с зашифрованными данными
    QFile file("/Users/ampidexter/Lab1/aes_accounts.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open encrypted JSON file:" << file.errorString();
        return;
    }

    // Читаем зашифрованные данные из файла
    QByteArray encryptedData = file.readAll();
    file.close();

    qDebug() << "encryptedData:" << encryptedData;

    std::vector<unsigned char> ivBin = hexStringToBytes(ivHex);
    std::vector<unsigned char> keyBin = hexStringToBytes(key.toStdString());
    std::vector<unsigned char> cipherBin = hexStringToBytes(encryptedData.toStdString());

    // Расшифровываем данные

    std::string decryptedText = decryptAES_CBC(
        std::string(cipherBin.begin(), cipherBin.end()),
        std::string(keyBin.begin(), keyBin.end()),
        std::string(ivBin.begin(), ivBin.end()));

    // Выводим расшифрованный текст в консоль для дебага
    qDebug() << "Decrypted text:" << QString::fromStdString(decryptedText);
    populateData(QString::fromStdString(decryptedText), "");
}


std::string DataWindow::decryptAES_CBC(const std::string &cipherText, const std::string &key, const std::string &iv) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plainTextLen;
    std::vector<unsigned char> plainText(1024);

    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, reinterpret_cast<const unsigned char *>(key.c_str()), reinterpret_cast<const unsigned char *>(iv.c_str()));

    EVP_DecryptUpdate(ctx, plainText.data(), &len, reinterpret_cast<const unsigned char *>(cipherText.c_str()), cipherText.size());
    plainTextLen = len;

    EVP_DecryptFinal_ex(ctx, plainText.data() + len, &len);
    plainTextLen += len;

    EVP_CIPHER_CTX_free(ctx);

    return std::string(reinterpret_cast<char *>(plainText.data()), plainTextLen);
}


std::vector<unsigned char> DataWindow::hexStringToBytes(const std::string &hexString) {
    std::vector<unsigned char> bytes;

    for (unsigned int i = 0; i < hexString.length(); i += 2) {
        std::string byteString = hexString.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

void DataWindow::openAccountDetails()
{
    pininputdialog pinDialog(this);

    if (pinDialog.exec() == QDialog::Accepted) {
        QString pin = pinDialog.ui->pinLineEdit->text();

        qDebug() << "Entered pin:" << pin;
    }
}


