#include "delete.h"
#include "ui_delete.h"

delete::delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete)
{
    ui->setupUi(this);
}

delete::~delete()
{
delete ui;
}
