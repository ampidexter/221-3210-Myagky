#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QTableWidget>

namespace Ui {
class DataWindow;
}

class DataWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataWindow(QWidget *parent = nullptr);
    ~DataWindow();

    void getKey(const QString &pin);

signals:
    void accountDetailsRequested(const QString &website, const QString &username, const QString &password);

private slots:
    void openAccountDetails();

private:
    Ui::DataWindow *ui;
    void populateData(const QString &decryptedText, const QString &filterText);
    std::string decryptAES_CBC(const std::string &cipherText, const std::string &key, const std::string &iv);
    std::vector<unsigned char> hexStringToBytes(const std::string &hexString);

};

#endif // DATAWINDOW_H
