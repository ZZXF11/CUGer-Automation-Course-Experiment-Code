#include "load.h"
#include "ui_load.h"
int tell=0;
load::load(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::load)
{
    ui->setupUi(this);
}

load::~load()
{
    delete ui;
}



