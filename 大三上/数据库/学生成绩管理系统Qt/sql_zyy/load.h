#ifndef LOAD_H
#define LOAD_H
#include "logindlg.h"
#include <QWidget>
extern QString flag_log;
namespace Ui {
class load;
}

class load : public QWidget
{
    Q_OBJECT

public:
    explicit load(QWidget *parent = nullptr);
    ~load();

private slots:
    void on_pushButton_clicked();
signals:
    void man_mode(QString);
private:
    Logindlg *log= new Logindlg;
    Ui::load *ui;
};

#endif // LOAD_H
