#include "my_insert.h"
#include "ui_my_insert.h"

my_insert::my_insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::my_insert)
{
    ui->setupUi(this);
}

my_insert::~my_insert()
{
    delete ui;
}
