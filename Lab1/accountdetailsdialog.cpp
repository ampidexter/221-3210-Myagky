#include "accountdetailsdialog.h"
#include "ui_accountdetailsdialog.h"

AccountDetailsDialog::AccountDetailsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountDetailsDialog)
{
    ui->setupUi(this);
}

AccountDetailsDialog::~AccountDetailsDialog()
{
    delete ui;
}
