#include "stusql.h"
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

stuSql * stuSql::ptrstuSql = nullptr;
stuSql::stuSql(QObject *parent)
    : QObject(parent)
{
  // init();
 // delStu(1);
//  StuInfo s;

}


//数据库初始化
void stuSql::init()
{
    //判断是否与SQL Sverve数据库连接成功
     m_db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server

     QString dsn = QString::fromLocal8Bit("KAISHAOSHAO");      //数据源名称
     m_db.setHostName("localhost");                        //选择本地主机，127.0.1.1
     m_db.setDatabaseName(dsn);                            //设置数据源名称
     m_db.setUserName("KAISHAOSHAO");                               //登录用户
     m_db.setPassword("");                           //密码
     
#if 1
     auto str = QCoreApplication::applicationDirPath()+"/kk.mdf";
     qDebug()<<str;
#endif
    // m_db.setDatabaseName("D:\\qtbug\\Student_Message");
     if(!m_db.open())                                      //打开数据库
     {
         qDebug()<<"database not open";                              //打开失败
     }
     else
         qDebug()<<"database open success!";
}


//查询所有学生的数量
quint32 stuSql::getStuCnt()
{
   QSqlQuery sql(m_db);
   sql.exec("select count (id) from student");
   quint32 uicnt=0;
   while (sql.next())
   {
    uicnt = sql.value(0).toUInt();
   }
   return uicnt;
}


//查询第几页学生数据and 这个page从0开始
QList<StuInfo> stuSql::getPageStu(quint32 page, quint32 uiCnt)
{
    QList<StuInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from student order by id	offset %1 rows fetch next %2 rows only")//没搞明白，limit限制你查询的数量
            .arg(page*uiCnt)
            .arg(uiCnt);

    sql.exec(strsql);

    StuInfo info;
    while (sql.next())
    {
     info.id = sql.value(0).toUInt();
     info.name = sql.value(1).toString();
     info.age = sql.value(2).toUInt();
     info.grade = sql.value(3).toString();
     info.uiclass = sql.value(4).toString();
     info.studentid = sql.value(5).toUInt();
     info.phone = sql.value(6).toString();
     info.wechat = sql.value(7).toString();
     info.QQ = sql.value(8).toString();
     l.push_back(info);
    }
    return l;
}


//增加学生
bool stuSql::addstu(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into student values(%0,'%1',%2,'%3','%4',%5,'%6','%7','%8')")
        .arg(info.id)
        .arg(info.name)
        .arg(info.age)
        .arg(info.grade)
        .arg(info.uiclass)
        .arg(info.studentid)
        .arg(info.phone)
        .arg(info.wechat)
        .arg(info.QQ);
    qDebug()<<sql.exec(strSql);
    return true;
}

//模拟数据的快速添加
bool stuSql::addStu(QList<StuInfo> l)
{
    QSqlQuery sql(m_db);
    m_db.transaction();
    for(auto info:l)
    {
      QString strSql = QString("insert into student values(%0,'%1',%2,'%3','%4',%5,'%6','%7','%8')")
        .arg(info.id)
        .arg(info.name)
        .arg(info.age)
        .arg(info.grade)
        .arg(info.uiclass)
        .arg(info.studentid)
        .arg(info.phone)
        .arg(info.wechat)
        .arg(info.QQ);
      sql.exec(strSql);

    }
    m_db.commit();
    return true;
}

//删除学生
bool stuSql::delStu(int id)
{
    QSqlQuery sql(m_db);
    return  sql.exec(QString("delete from student where id = %1").arg(id));
}


//清空学生表
void stuSql::clearStuTable()
{
    QSqlQuery sql(m_db);
    sql.exec("delete from student");
}


//修改学生信息
void stuSql::UpdateStuInfo(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update student set name='%1',age=%2, grade='%3',uiclass='%4',student_id=%5,phone='%6',wechat='%7',QQ='%8' where id=%0")
        .arg(info.id)
        .arg(info.name)
        .arg(info.age)
        .arg(info.grade)
        .arg(info.uiclass)
        .arg(info.studentid)
        .arg(info.phone)
        .arg(info.wechat)
        .arg(info.QQ);

    qDebug()<<sql.exec(strSql);
}


//查询所有用户 qt里面QList和QVector数据是一样的
QList<UserInfo> stuSql::getAllUser()
{
    QList<UserInfo> l;
    QSqlQuery sql(m_db);

    sql.exec("select * from username");

    UserInfo info;
    while (sql.next())
    {
     info.username = sql.value(0).toUInt();
     info.password = sql.value(1).toString();
     info.aut = sql.value(2).toUInt();
     l.push_back(info);
     }
    return l;
}


//查询用户名是否存在
bool stuSql::isExit(QString strUser)
{
    QSqlQuery sql(m_db);
    sql.exec(QString("select * from Username where username='%1'").arg(strUser));
    return sql.next();
}


//更新用户信息
void stuSql::updateUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update Username set password='%1', auth='%2' where username='%0'")
            .arg(info.username)
            .arg(info.password)
            .arg(info.aut);
    qDebug()<<sql.exec(strSql);
}


//添加单个用户
bool stuSql::AddUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into Username values('%0','%1','%2')")
        .arg(info.username)
        .arg(info.password)
        .arg(info.aut);
    qDebug()<<sql.exec(strSql);
    return true;
}


bool stuSql::Password(UserInfo info)
{
   QSqlQuery sql(m_db);

   QString s=QString("select * from Username  where username ='%1' and password='%2' ")
                     .arg(info.username)
                     .arg(info.password);
            sql.exec(s);

            return sql.next();
}

QString stuSql::searchUsername(UserInfo info)
{
    QSqlQuery sql(m_db);

    QString s=QString("select auth from Username  where username ='%1' and password='%2' ")
                      .arg(info.username)
                      .arg(info.password);
             sql.exec(s);
             QString auth;

             while (sql.next())
             {
             auth = sql.value(0).toString();
             }
             return auth;
}

int stuSql::boolguanli(UserInfo info)
{
    QSqlQuery sql(m_db);

    QString s=QString("select guanli from Username  where username ='%1' and password='%2' ")
                      .arg(info.username)
                      .arg(info.password);
             sql.exec(s);
             int guanli;

             while (sql.next())
             {
             guanli = sql.value(0).toUInt();
             }
             return guanli;
}


//删除单个用户
bool stuSql::delUser(QString strUserName)
{
    QSqlQuery sql(m_db);
    qDebug()<<sql.exec(QString("delete from Username where username = '%1'").arg(strUserName));
    return  sql.next();
}











