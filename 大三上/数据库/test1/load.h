#ifndef LOAD_H
#define LOAD_H

#include <QMainWindow>
#include"mainwindow.h"
extern int tell;
namespace Ui {
class load;
}

class load : public QMainWindow
{
    Q_OBJECT

public:
    explicit load(QWidget *parent = nullptr);
    ~load();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_loadsure_clicked();

private:
    Ui::load *ui;
    MainWindow * u;
};

#endif // LOAD_H
