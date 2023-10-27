#include "logindlg.h"
#include "ui_logindlg.h"

Logindlg::Logindlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logindlg)
{
    ui->setupUi(this);
}

Logindlg::~Logindlg()
{
    delete ui;
}
