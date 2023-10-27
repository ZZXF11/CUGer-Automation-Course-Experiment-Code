#ifndef GRADE_SEL_H
#define GRADE_SEL_H

#include <QWidget>

namespace Ui {
class grade_sel;
}

class grade_sel : public QWidget
{
    Q_OBJECT

public:
    explicit grade_sel(QWidget *parent = nullptr);
    ~grade_sel();

private slots:
    void on_stu_sel_clicked();
    void on_coure_sel_clicked();

signals:
    void stu_sel(QString);
    void course_sel(QString);
private:
    Ui::grade_sel *ui;
};

#endif // GRADE_SEL_H
