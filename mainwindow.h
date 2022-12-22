#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "page_login.h"
#include "stusql.h"
#include "dlg_addstu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    virtual void  keyPressEvent(QKeyEvent *event);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //设置QtreeWight
    void  setQtreeWight();

    //添加模拟数据名字
     void text(QStringList &l);
    //初始化tableWight的样式
     void setTableStyle();
    //添加模拟数据
     void addShuju();


private slots:

    void getauth(QString &name);

    void panduan(int &guanli);

    void on_pushButton_clicked();

    void on_btn_moni_clicked();

    void on_btn_add_clicked();

    void on_btn_clear_clicked();

    void on_btn_del_clicked();

    void on_btn_update_clicked();

    void on_btn_find_clicked();



private:
    Ui::MainWindow *ui;

    Page_login m_dlgLogin;

    Page_login *name;


    stuSql *m_ptrStrSql;

    QStringList m_lNames;

    Dlg_AddStu m_dlgAddStu;
};
#endif // MAINWINDOW_H
