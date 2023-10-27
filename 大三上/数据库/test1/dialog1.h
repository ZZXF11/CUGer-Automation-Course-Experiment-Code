#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include"dialog.h"

namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

private:
    QSqlQueryModel*lookqrModel;


public:
    explicit Dialog1(QWidget *parent = nullptr);
    ~Dialog1();

private slots:
    void on_pushButton_clicked();

    void on_delete_sure_clicked();

    void on_pushButton_2_clicked();

    void on_delete_sure_2_clicked();

    void on_pushButton_3_clicked();

    void on_delete_sure_3_clicked();

private:
    Ui::Dialog1 *ui;
};

#endif // DIALOG1_H
