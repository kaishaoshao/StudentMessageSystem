#include "page_login.h"
#include "ui_page_login.h"
#include <QPushButton>
#include <QSqlQuery>
#include "stusql.h"
#include <QMessageBox>
#include <QDebug>

Page_login::Page_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_login)
{
    ui->setupUi(this);
    m_ptrStrSql = stuSql::getinstance();
    //m_ptrStrSql->init();
}

Page_login::~Page_login()
{
    delete ui;
}

void Page_login::on_btn_passwd_clicked()
{

    //数据库查找账户和密码
    //与数据库连接
  UserInfo info;
  QString username = ui->lineEdit_zhanghu->text();
  QString password = ui->lineEdit_mima->text();


  info.username = username;
  info.password = password;

//  QString name = m_ptrStrSql->searchUsername(info);
//  qDebug()<<name;
   bool b=m_ptrStrSql->Password(info);
  if(username.isEmpty()&& password != "")
   {
       QMessageBox::warning(nullptr,"警告","账号不能为空");
       ui->lineEdit_mima->clear();
   }


  else if(password.isEmpty() && username != ""){
         QMessageBox::warning(nullptr,"警告","密码不能为空");      
         ui->lineEdit_zhanghu->clear();
 }

  else if(username.isEmpty()&& password.isEmpty())
  {
      QMessageBox::warning(nullptr,"警告","账号和密码不能为空");
  }

  else
  {

      if(b == true)
        {
            //成功进入主界面
             QMessageBox::information(nullptr,"提示","登录成功",QMessageBox::Yes);
             QString name = m_ptrStrSql->searchUsername(info);
             int guanli = m_ptrStrSql->boolguanli(info);

             emit Password(guanli);
             emit auth(name);
             emit sendLoginSuccess();


        }

      else
      {
             QMessageBox::warning(nullptr,"警告","登录失败，请重试！");
             ui->lineEdit_mima->clear();
             ui->lineEdit_zhanghu->clear();

       }

     }

}


void Page_login::on_btn_exit_clicked()
{
    exit(0);
}
