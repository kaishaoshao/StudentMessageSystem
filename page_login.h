#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include "stusql.h"


namespace Ui {
class Page_login;
}

class Page_login : public QWidget
{
    Q_OBJECT

public:
    explicit Page_login(QWidget *parent = nullptr);
    ~Page_login();

private slots:
    void on_btn_passwd_clicked();


    void on_btn_exit_clicked();

signals:
    void sendLoginSuccess();

    void auth(QString &name);

    void Password(int &guanli);

private:
    Ui::Page_login *ui;

    stuSql *m_ptrStrSql;

};

#endif // PAGE_LOGIN_H
