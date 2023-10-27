#include "find.h"
#include "ui_find.h"

Find::Find(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Find)
{
    ui->setupUi(this);
}

Find::~Find()
{
    delete ui;
}


void Find::on_find_sure_clicked()
{

    emit send_sno(ui->input_sno->text());
    ui->input_sno->clear();

}


void Find::on_find_sure_2_clicked()
{
    emit send_sname(ui->input_sname->text());
    ui->input_sname->clear();
}

