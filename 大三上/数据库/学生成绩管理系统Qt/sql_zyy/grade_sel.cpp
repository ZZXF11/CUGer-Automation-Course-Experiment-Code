#include "grade_sel.h"
#include "ui_grade_sel.h"

grade_sel::grade_sel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::grade_sel)
{
    ui->setupUi(this);
}

grade_sel::~grade_sel()
{
    delete ui;
}

void grade_sel::on_stu_sel_clicked()
{
    emit stu_sel(ui->lineEdit->text());
    ui->lineEdit->clear();
}


void grade_sel::on_coure_sel_clicked()
{
    emit course_sel(ui->lineEdit_2->text());
    ui->lineEdit_2->clear();
}

