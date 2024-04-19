#ifndef DATA_H
#define DATA_H

#include <QDialog>

namespace Ui {
class data;
}

class data : public QDialog
{
    Q_OBJECT

public:
    explicit data(QWidget *parent = nullptr);
    ~data();

private:
    Ui::data *ui;
};

#endif // DATA_H
