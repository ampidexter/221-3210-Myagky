// Ваш файл details.h

#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>

namespace Ui {
class Details;
}

class Details : public QDialog
{
    Q_OBJECT

public:
    explicit Details(QWidget *parent = nullptr);
    ~Details();

    void displayDetails(const QString &website, const QString &username, const QString &password); // Метод для отображения деталей

private:
    Ui::Details *ui;
};

#endif // DETAILS_H
