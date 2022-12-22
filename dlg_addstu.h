#ifndef DLG_ADDSTU_H
#define DLG_ADDSTU_H

#include <QDialog>
#include "stusql.h"

namespace Ui {
class Dlg_AddStu;
}

class Dlg_AddStu : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_AddStu(QWidget *parent = nullptr);
    ~Dlg_AddStu();

    void setType(bool isAdd,StuInfo info={});
private slots:
    void on_btn_baocun_clicked();

    void on_btn_quxiao_clicked();

private:
    Ui::Dlg_AddStu *ui;
    bool m_isAdd;
    StuInfo m_info;
    QSqlDatabase m_db;
};

#endif // DLG_ADDSTU_H
