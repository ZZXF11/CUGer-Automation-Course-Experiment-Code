#include "find_sc.h"
#include "ui_find_sc.h"

Find_sc::Find_sc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Find_sc)
{
    ui->setupUi(this);
}

Find_sc::~Find_sc()
{
    delete ui;
}

void Find_sc::on_find_sure_3_clicked()
{
    emit send_sno(ui->input_sno_1->text());
    ui->input_sno_1->clear();
}


void Find_sc::on_find_sure_4_clicked()
{
    emit send_sname(ui->input_sname_1->text());
    ui->input_sname_1->clear();
}

