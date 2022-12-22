#include "dlg_addstu.h"
#include "ui_dlg_addstu.h"
#include <QDebug>

#include <QMessageBox>


Dlg_AddStu::Dlg_AddStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_AddStu)
{
    ui->setupUi(this);

}

Dlg_AddStu::~Dlg_AddStu()
{
    delete ui;
    ui->lE_name->clear();
    ui->sB_age->setValue(18);
    ui->lE_class->clear();
    ui->lE_grade->clear();
    ui->lE_student->clear();
    ui->lE_phone->clear();
    ui->lE_wechat->clear();
    ui->lE_qq->clear();
}

void Dlg_AddStu::setType(bool isAdd,StuInfo info)
{
    m_isAdd = isAdd;
    m_info = info;
    if(m_isAdd == false)
    {
        m_info.id = info.id;
        ui->lE_name->setText(info.name);
        ui->sB_age->setValue(info.age);
        ui->lE_class->setText(info.uiclass);
        ui->lE_grade->setText(info.grade);
        ui->lE_student->setText(QString::number(info.studentid));
        ui->lE_phone->setText(info.phone);
        ui->lE_wechat->setText(info.wechat);
        ui->lE_qq->setText(info.QQ);
    }
    if(m_isAdd == true)
    {
        ui->lE_name->clear();
        ui->sB_age->setValue(18);
        ui->lE_class->clear();
        ui->lE_grade->clear();
        ui->lE_student->clear();
        ui->lE_phone->clear();
        ui->lE_wechat->clear();
        ui->lE_qq->clear();
    }
}

void Dlg_AddStu::on_btn_baocun_clicked()
{
   StuInfo info;
   auto ptr = stuSql::getinstance();
   int cnt = ptr->getStuCnt();

   info.id =cnt+1;
   info.name = ui->lE_name->text();
   info.age = ui->sB_age->text().toUInt();
   info.uiclass = ui->lE_class->text();
   info.grade = ui->lE_grade->text();
   info.studentid = ui->lE_student->text().toUInt();
   info.phone = ui->lE_phone->text();
   info.wechat = ui->lE_wechat->text();
   info.QQ = ui->lE_qq->text();

   if(m_isAdd)
   {

       ptr->addstu(info);
       QMessageBox::information(nullptr,"提示","存储成功");

   }
   else
   {
       info.id = m_info.id;
       ptr->UpdateStuInfo(info);
       QMessageBox::information(nullptr,"提示","修改成功");
   }


   //列表清空
   ui->lE_name->clear();
   ui->sB_age->setValue(18);
   ui->lE_class->clear();
   ui->lE_grade->clear();
   ui->lE_student->clear();
   ui->lE_phone->clear();
   ui->lE_wechat->clear();
   ui->lE_qq->clear();

   this->hide();
}

void Dlg_AddStu::on_btn_quxiao_clicked()
{
    this->hide();
}
