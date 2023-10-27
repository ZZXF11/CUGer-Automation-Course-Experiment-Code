#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

namespace Ui {
class Logindlg;
}

class Logindlg : public QDialog
{
    Q_OBJECT

public:
    explicit Logindlg(QWidget *parent = nullptr);
    ~Logindlg();

private:
    Ui::Logindlg *ui;
};

#endif // LOGINDLG_H
