#ifndef DELETE_H
#define DELETE_H

#include <QDialog>

namespace Ui {
class delete;
}

class delete : public QDialog
{
    Q_OBJECT

public:
    explicit delete(QWidget *parent = nullptr);
    ~delete();

private:
    Ui::delete *ui;
};

#endif // DELETE_H
