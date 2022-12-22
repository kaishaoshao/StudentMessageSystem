#ifndef STUSQL_H
#define STUSQL_H

#include <QObject>
//数据库类头文件
#include <QSqlDatabase>
//定义数据库类型类
struct StuInfo
{
    int id;
    QString name;
    quint8 age;
    QString grade;
    QString uiclass;
    quint32 studentid;
    QString phone;
    QString wechat;
    QString QQ;
};
//定义用户数据库
struct UserInfo
{
   QString username;
   QString password;
   QString aut;
   quint8  guanli;
};


class stuSql : public QObject
{
    Q_OBJECT
public:

    //不知道啥作用,作用大
    static stuSql *ptrstuSql;
    static stuSql *getinstance()
    {
        if(nullptr == ptrstuSql)
        {
            ptrstuSql = new stuSql;
        }
        return ptrstuSql;
    }

    explicit stuSql(QObject *parent = nullptr);

    //数据库初始化
    void init();

    //查询所有学生的数量
    quint32 getStuCnt();

    //查询第几页学生数据
    QList<StuInfo> getPageStu(quint32 page,quint32 uiCnt);//page页数，uiCmt数量

    //增加学生
    bool addstu(StuInfo);
    bool addStu(QList<StuInfo> l);


    //删除学生
    bool delStu(int id);

    //清空学生表
    void clearStuTable();

    //修改学生信息
    void UpdateStuInfo(StuInfo info);

    //查询所有用户 qt里面QList和QVector数据是一样的
    QList<UserInfo> getAllUser();

    //查询用户名是否存在
    bool isExit(QString strUser);

    //更新用户信息
    void updateUser(UserInfo info);

    //添加单个用户
    bool AddUser(UserInfo info);

    //删除单个用户
    bool delUser(QString strUserName);

    //登录信息判断
    bool Password(UserInfo info);

    //查找用户名
    QString searchUsername(UserInfo info);

    //判断是否为管理员
    int boolguanli(UserInfo info);

signals:

private:
    QSqlDatabase m_db;

};

#endif // STUSQL_H
