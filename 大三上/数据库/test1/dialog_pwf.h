#ifndef DIALOG_PWF_H
#define DIALOG_PWF_H

#include <QDialog>
#include"dialog.h"
#include"my_load.h"
#include <QStringList>
namespace Ui {
class Dialog_pwf;
}

class Dialog_pwf : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_pwf(QWidget *parent = nullptr);
    ~Dialog_pwf();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog_pwf *ui;
};

#endif // DIALOG_PWF_H
