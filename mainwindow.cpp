#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "page_login.h"


#include <QFile>
#include <QFont>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QHeaderView>
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QRandomGenerator64>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_ptrStrSql = stuSql::getinstance();
    m_ptrStrSql->init();


    m_dlgLogin.show();
    auto f =[&](){
        //显示 用户名
        this->show();
    };

   // auto auth =[]
    //跳出主界面
    connect(&m_dlgLogin,&Page_login::sendLoginSuccess,this,f);

    connect(&m_dlgLogin,SIGNAL(auth(QString&)),this,SLOT(getauth(QString&)));


//    //设置QtreeWight
//      setQtreeWight();  --这个页面是删除了，没啥用
//    //初始化tableWight的样式
 //  setTableStyle();
//    //添加模拟数据
      addShuju();
      connect(&m_dlgLogin,SIGNAL(Password(int &)),this,SLOT(panduan(int &)));



}

MainWindow::~MainWindow()
{
    delete ui;
}

//删除了没啥用功能没实现
//void MainWindow::setQtreeWight()
//{
//    //设置tree情况

//    ui->treeWidget->setColumnCount(1);
//    ui->treeWidget->setFrameStyle(false);
//    ui->treeWidget->clear();
//    QStringList l("学生信息管理系统");

//    //tree父类
//    QTreeWidgetItem *pf = new QTreeWidgetItem(ui->treeWidget,l);


//    ui->treeWidget->addTopLevelItem(pf);


//    //tree子类
//    l.clear();
//    l<<"管理员管理";
//    QTreeWidgetItem *p2 = new QTreeWidgetItem(pf,l);

//    l.clear();
//    l<<"学生管理";
//    QTreeWidgetItem *p1 = new QTreeWidgetItem(pf,l);


//    pf->addChild(p1);
//    pf->addChild(p2);
//    ui->treeWidget->expandAll();


//}

//刷新
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F6)
    {
        QFile f;
     auto str = QCoreApplication::applicationDirPath();
        f.setFileName(str+"\\"+"stuqss.css");
        f.open(QIODevice::ReadOnly);
        QString strQss = f.readAll();
        this->setStyleSheet(strQss);
        m_dlgLogin.setStyleSheet(strQss);
    }
}


void MainWindow::addShuju()
{
     ui->tableWidget->clear();

     setTableStyle();
     //显示用户名
//     UserInfo info1;
//     QString na = m_ptrStrSql->searchUsername(info1);
//     qDebug()<<na;
//     ui->label_sy->setText(QString("%1").arg(na));
     //显示学生数量



     auto cnt = m_ptrStrSql->getStuCnt();
     ui->lable_cnt->setText(QString("学生数量：%1").arg(cnt));

     QList<StuInfo> lStudent = m_ptrStrSql->getPageStu(0,cnt);
     for (int i=0;i<lStudent.size();i++)
     {
       ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(lStudent[i].id)));
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(lStudent[i].name));
       ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(lStudent[i].age)));
       ui->tableWidget->setItem(i,3,new QTableWidgetItem(lStudent[i].grade));
       ui->tableWidget->setItem(i,4,new QTableWidgetItem(lStudent[i].uiclass));
       ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(lStudent[i].studentid)));
       ui->tableWidget->setItem(i,6,new QTableWidgetItem(lStudent[i].phone));
       ui->tableWidget->setItem(i,7,new QTableWidgetItem(lStudent[i].wechat));
       ui->tableWidget->setItem(i,8,new QTableWidgetItem(lStudent[i].QQ));
     }
}

void MainWindow::getauth(QString &name)
{
    ui->label_sy->setText(QString("%1").arg(name));

}

void MainWindow::panduan(int &guanli)
{

    if(guanli == 0)
    {
     ui->btn_add->hide();
     ui->btn_del->hide();
     ui->btn_moni->hide();
     ui->btn_clear->hide();
     ui->btn_update->hide();
    }
}
void MainWindow::setTableStyle()
{
    ui->tableWidget->clear();
   // ui->treeWidget->expandAll();

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //行头自适应表格
    ui->tableWidget->horizontalHeader()->setFont(QFont("楷体", 15));

    //点击表时不对表头行光亮（获取焦点）
   // ui->tableWidget->horizontalHeader()->setHighlightSections(false);

    //设置表头字体加粗
    //QFont font =  ui->tableWidget->horizontalHeader()->font();
    //  font.setBold(false);
   // ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(81, 163, 243);}"); //skyblue设置表头背景色
    ui->tableWidget->setStyleSheet("selection-background-color:rgb(142, 221, 255);"); //设置选中背景色
    //ui->tableWidget->setStyleSheet(qssTV);

    ui->tableWidget->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    ui->tableWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //所有单元格的字体  设置成一样
    ui->tableWidget->setFont(QFont("楷体", 12));

    ui->tableWidget->setRowCount(2000); //设置行数
    ui->tableWidget->setColumnCount(9); //设置列数
    //ui->tableWidget->setWindowTitle("TABLE演示");
    QStringList header;
    header<<"序号"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话号"<<"微信帐号"<<"QQ帐号";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    //不可编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //去掉默认行号 可以用horizontalHeader() ->setVisible(false)隐藏横向表头
    QHeaderView *header1 =  ui->tableWidget->verticalHeader();
    header1->setHidden(true);

    //自适应表宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列

    //设置单元格大小
//    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(50);  //设置默认宽度
//    ui->tableWidget->verticalHeader()->setDefaultSectionSize(30);   //设置一行默认高度
//    ui->tableWidget->setColumnWidth(0,90);
//    ui->tableWidget->setColumnWidth(1,90);
//    ui->tableWidget->setColumnWidth(2,90);
//    ui->tableWidget->setColumnWidth(2,90);
//    ui->tableWidget->setColumnWidth(4,90);
//    ui->tableWidget->setColumnWidth(5,90);
//    ui->tableWidget->setColumnWidth(6,90);
//    ui->tableWidget->setColumnWidth(7,90);

}


 //制作1000条模拟数据
void MainWindow::on_btn_moni_clicked()
{

    StuInfo info;
    QStringList l;
    QRandomGenerator g;
    QList<StuInfo> l1;
    //添加模拟数据名字
    text(l);

    for (int i=1;i<l.size();i++)
    {

     auto w=g.bounded(1,5);
     auto phone=g.bounded(9999999,99999999);
     auto qq=g.bounded(20,30);

     info.name = l[i];
     info.id = i;
     info.phone = "138"+QString::number(phone);
     info.QQ =QString::number(qq)+QString::number(phone);
     info.wechat= "wx"+info.phone;
     int m=i+w;

     if(m%2)
     {
        info.uiclass="计科"+QString::number(w)+"班";
     }
     else if(m%3)
     {
        info.uiclass="电子"+QString::number(w)+"班";
     }
     else if(m%5)
     {
        info.uiclass="造价"+QString::number(w)+"班";
     }
     else
     {
        info.uiclass="管理"+QString::number(w)+"班";
     }

     if(i%2)
     {
         info.age = 19;
         info.grade = "21级";
         info.studentid=20210000+i;
     }
     else if(i%3)
     {
         info.age = 20;
         info.grade = "20级";
         info.studentid=20200000+i;
     }
     else if(i%5)
     {
         info.age = 21;
         info.grade = "19级";
         info.studentid=20190000+i;
     }
     else if(i%7)
     {
         info.age = 22;
         info.grade = "18级";
         info.studentid=20180000+i;
     }

     l1.append(info);

    }
  m_ptrStrSql->addStu(l1);
  addShuju();
}

void MainWindow::on_btn_find_clicked()
{
    QString strFilter = ui->lE_search->text();
    int index = 0;
    if(strFilter.isEmpty())
    {
        QMessageBox::information(nullptr,"警告","搜索数据为空");
        addShuju();
        return;
    }
    ui->tableWidget->clear();
    setTableStyle();
    auto cnt = m_ptrStrSql->getStuCnt();
    ui->lable_cnt->setText(QString("学生数量：%1").arg(cnt));
    QList<StuInfo> lStudent = m_ptrStrSql->getPageStu(0,cnt);

    for (int i=0;i<lStudent.size();i++)
    {
        if(!QString::number(lStudent[i].studentid).contains(strFilter))
        {
            continue;
        }

      ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(lStudent[i].id)));
      ui->tableWidget->setItem(index,1,new QTableWidgetItem(lStudent[i].name));
      ui->tableWidget->setItem(index,2,new QTableWidgetItem(QString::number(lStudent[i].age)));
      ui->tableWidget->setItem(index,3,new QTableWidgetItem(lStudent[i].grade));
      ui->tableWidget->setItem(index,4,new QTableWidgetItem(lStudent[i].uiclass));
      ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(lStudent[i].studentid)));
      ui->tableWidget->setItem(index,6,new QTableWidgetItem(lStudent[i].phone));
      ui->tableWidget->setItem(index,7,new QTableWidgetItem(lStudent[i].wechat));
      ui->tableWidget->setItem(index,8,new QTableWidgetItem(lStudent[i].QQ));
      index++;
   }
    ui->tableWidget->setRowCount(index);
}
void MainWindow::on_btn_add_clicked()
{
     StuInfo info;
     m_dlgAddStu.setType(true,info);
    //非模态对话框（后面的窗口任然可以拖动）
    // m_dlgAddStu.show();
    //模态对话框（后面的窗口不可以拖动）
     m_dlgAddStu.exec();
     addShuju();

}
void MainWindow::on_btn_clear_clicked()
{
    m_ptrStrSql->clearStuTable();
    addShuju();

}

void MainWindow::on_btn_update_clicked()
{
   StuInfo info;

   int i= ui->tableWidget->currentRow();
   if(i>=0)
   {
   //header<<"序号"<<"id"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话号"<<"微信帐号"<<"QQ帐号";
     info.id = ui->tableWidget->item(i,0)->text().toUInt();

     info.name = ui->tableWidget->item(i,1)->text();
     info.age = ui->tableWidget->item(i,2)->text().toUInt();
     info.grade = ui->tableWidget->item(i,3)->text();
     info.uiclass = ui->tableWidget->item(i,4)->text();
     info.studentid = ui->tableWidget->item(i,5)->text().toUInt();
     info.phone = ui->tableWidget->item(i,6)->text();
     info.wechat = ui->tableWidget->item(i,7)->text();
     info.QQ = ui->tableWidget->item(i,8)->text();
     m_dlgAddStu.setType(false,info);
     m_dlgAddStu.exec();

   }

    addShuju();


}

void MainWindow::on_btn_del_clicked()
{
  //获取当前的行

   int i= ui->tableWidget->currentRow();
   if(i>=0)
   {
     int id = ui->tableWidget->item(i,0)->text().toUInt();
     m_ptrStrSql->delStu(id);
     addShuju();
     QMessageBox::information(nullptr,"提示","删除成功");

   }

}

void MainWindow::on_pushButton_clicked()
{
    exit(0);
}



void MainWindow::text(QStringList &l)
{
   l<<"郭菀 ";
   l<<"靳奎悒";
   l<<"殳丰茂";
   l<<"闫荆荧";
   l<<"韩菁怡";
   l<<"裘宛 ";
   l<<"亢邴 ";
   l<<"端木珠";
   l<<"闻允红";
   l<<"霍孱乌";
   l<<"古柔 ";
   l<<"殳妍烙";
   l<<"姜博雅";
   l<<"弓悲 ";
   l<<"澹台璎";
   l<<"黄襄纹";
   l<<"裘鹤 ";
   l<<"曾达 ";
   l<<"邬秋瑛";
   l<<"花丝 ";
   l<<"亓官筝";
   l<<"段伊 ";
   l<<"施用凯";
   l<<"谈炳嫣";
   l<<"梁丘孤";
   l<<"禹汲 ";
   l<<"姚扬 ";
   l<<"褚伊 ";
   l<<"隆焦彤";
   l<<"简鹤苠";
   l<<"松鞯祥";
   l<<"家宛奄";
   l<<"毋鹤戎";
   l<<"诸葛贞";
   l<<"裘绮 ";
   l<<"谈绫海";
   l<<"翟京爨";
   l<<"计淑然";
   l<<"廉惮 ";
   l<<"昌葶衣";
   l<<"弓捕隶";
   l<<"叶涑 ";
   l<<"沙博捕";
   l<<"廉靳沅";
   l<<"牛斌珊";
   l<<"贾娩班";
   l<<"靳苠 ";
   l<<"双囧笙";
   l<<"廉京爨";
   l<<"裘谷兰";
   l<<"汲芮戾";
   l<<"慕容戾";
   l<<"通寄云";
   l<<"扈匪 ";
   l<<"伊瑛稀";
   l<<"解颜裘";
   l<<"成巧芝";
   l<<"柯靖莺";
   l<<"庄翔迎";
   l<<"艾诗云";
   l<<"任瑛忻";
   l<<"羊舌思";
   l<<"程弼 ";
   l<<"鄂博裕";
   l<<"汪邑彤";
   l<<"公婧涵";
   l<<"相沂 ";
   l<<"屠友瑶";
   l<<"贺邑豁";
   l<<"游晓霜";
   l<<"宿凯唱";
   l<<"益清欣";
   l<<"籍鹤邴";
   l<<"宁紫涵";
   l<<"皇甫涛";
   l<<"辛岩珍";
   l<<"弓沁斩";
   l<<"芮戾斌";
   l<<"黎笑卉";
   l<<"伊凤 ";
   l<<"崔契若";
   l<<"胡紫夏";
   l<<"全君昊";
   l<<"宰父鹤";
   l<<"毛清水";
   l<<"闾丘茈";
   l<<"毕荧 ";
   l<<"刁囧 ";
   l<<"澹台寒";
   l<<"解稀衣";
   l<<"殷靖 ";
   l<<"沃莆 ";
   l<<"盛瑛淇";
   l<<"韦靳 ";
   l<<"澹台乞";
   l<<"滑增敏";
   l<<"墨苡妍";
   l<<"雍鹏天";
   l<<"聂鸿畅";
   l<<"裴函姒";
   l<<"能婴莞";
   l<<"钟离雍";
   l<<"席襄沁";
   l<<"简鹰萍";
   l<<"薛高杰";
   l<<"翟芹炳";
   l<<"褚匕 ";
   l<<"东郭绮";
   l<<"单瑛 ";
   l<<"石擎 ";
   l<<"郦霸邴";
   l<<"茹驳伊";
   l<<"红敏苠";
   l<<"訾明诚";
   l<<"王雯悒";
   l<<"滑兰湘";
   l<<"韶半蕾";
   l<<"席穆 ";
   l<<"凌丑芙";
   l<<"闾丘枫";
   l<<"隆灵 ";
   l<<"羿卿萍";
   l<<"荆骁蓝";
   l<<"申紊葶";
   l<<"叶富班";
   l<<"巫泰和";
   l<<"诸葛败";
   l<<"韩焱契";
   l<<"桑筮 ";
   l<<"邱蔚然";
   l<<"漆雕汇";
   l<<"段葶苡";
   l<<"胡戾 ";
   l<<"厉源智";
   l<<"伏珊香";
   l<<"肖衣剑";
   l<<"惠芯 ";
   l<<"暨霞姝";
   l<<"浦匪 ";
   l<<"颛孙芯";
   l<<"耳河灵";
   l<<"莫戎惠";
   l<<"冀钧 ";
   l<<"哈昭郁";
   l<<"仉督败";
   l<<"邴大有";
   l<<"危丑邑";
   l<<"司蓉靳";
   l<<"南宫匡";
   l<<"谷梁穆";
   l<<"蔚斌 ";
   l<<"乌荟颖";
   l<<"乌湘 ";
   l<<"夏候达";
   l<<"晏豁芫";
   l<<"计芾 ";
   l<<"蓟莹契";
   l<<"茹疾 ";
   l<<"瞿艳 ";
   l<<"扈筮岩";
   l<<"终威萧";
   l<<"申清芸";
   l<<"茅静馨";
   l<<"羿伊苠";
   l<<"肖裘 ";
   l<<"卞香松";
   l<<"蔚碧威";
   l<<"法无颜";
   l<<"魏无极";
   l<<"南门晔";
   l<<"幸捕裘";
   l<<"能芯桐";
   l<<"隙颦 ";
   l<<"勾笙 ";
   l<<"皇甫筝";
   l<<"钟荟奄";
   l<<"司绫桐";
   l<<"宗政增";
   l<<"慕德泽";
   l<<"宫乌婴";
   l<<"芮含征";
   l<<"仰姒 ";
   l<<"崔瑛珩";
   l<<"易樱契";
   l<<"左丘筮";
   l<<"湛玲芳";
   l<<"厉清绫";
   l<<"司雅清";
   l<<"禄茈契";
   l<<"公孙驳";
   l<<"胡穆 ";
   l<<"钱珩耷";
   l<<"欧邑若";
   l<<"解罡茗";
   l<<"段娩 ";
   l<<"晋萍敏";
   l<<"都伟志";
   l<<"霍雁 ";
   l<<"爱秋芳";
   l<<"耳豁碧";
   l<<"杜博琳";
   l<<"琴素囧";
   l<<"长孙桐";
   l<<"冯翼秀";
   l<<"南宫羿";
   l<<"习达 ";
   l<<"宋涑卿";
   l<<"裘冰烟";
   l<<"终敏 ";
   l<<"邢秀荧";
   l<<"谯笪鹰";
   l<<"闫紊涔";
   l<<"晏贞莛";
   l<<"毕芷 ";
   l<<"弘婉然";
   l<<"慕容敏";
   l<<"闵胜芾";
   l<<"应益年";
   l<<"尚铭剑";
   l<<"齐羿姝";
   l<<"刘斩富";
   l<<"娄苠 ";
   l<<"谷梁弼";
   l<<"昌悒弼";
   l<<"付萍 ";
   l<<"冀咏志";
   l<<"严玟玉";
   l<<"邴海衣";
   l<<"束姝匕";
   l<<"蓟继现";
   l<<"曲匪 ";
   l<<"厉芸 ";
   l<<"隙莞 ";
   l<<"訾驳垣";
   l<<"弓宏深";
   l<<"隙刚 ";
   l<<"居鞅 ";
   l<<"尹颖荧";
   l<<"麻和宜";
   l<<"佟竺康";
   l<<"曲翎 ";
   l<<"归海月";
   l<<"吴祥 ";
   l<<"俟玉轩";
   l<<"单于斓";
   l<<"党悒鹤";
   l<<"郁悒契";
   l<<"侯涵琛";
   l<<"文铭 ";
   l<<"逄逊荧";
   l<<"宗笙凤";
   l<<"公冶函";
   l<<"宋续 ";
   l<<"司寇湉";
   l<<"闵雁芙";
   l<<"许颖 ";
   l<<"麻香 ";
   l<<"詹贞香";
   l<<"宰炳驳";
   l<<"彭紫菡";
   l<<"佟歌韵";
   l<<"常师荟";
   l<<"爱涔捕";
   l<<"太叔弘";
   l<<"姜无心";
   l<<"晁匪 ";
   l<<"赵奇正";
   l<<"关戾鞅";
   l<<"应杰秀";
   l<<"利姝盈";
   l<<"仲契珍";
   l<<"束葶 ";
   l<<"濮阳兰";
   l<<"武银柳";
   l<<"徐思凡";
   l<<"曾又夏";
   l<<"车芙弱";
   l<<"龚天睿";
   l<<"宗一德";
   l<<"匡英华";
   l<<"宋秋衫";
   l<<"从捕乞";
   l<<"房紊炳";
   l<<"巩匪 ";
   l<<"璩菀荠";
   l<<"羿萤败";
   l<<"满莞颤";
   l<<"吴雍秀";
   l<<"葛柔霆";
   l<<"百里荆";
   l<<"赵思云";
   l<<"通嵩斌";
   l<<"容纲 ";
   l<<"闵奎芙";
   l<<"景荠苠";
   l<<"融紫城";
   l<<"冷淇骁";
   l<<"郗珍苠";
   l<<"鲁幼柏";
   l<<"长孙湘";
   l<<"杨戾 ";
   l<<"法剑伊";
   l<<"广娩娩";
   l<<"阴青艳";
   l<<"徐敏菀";
   l<<"阙颤霆";
   l<<"宣晓丝";
   l<<"仇沂灵";
   l<<"翁鞅 ";
   l<<"第五涫";
   l<<"危莹遥";
   l<<"敖苠卿";
   l<<"马茈忻";
   l<<"楚枫蹇";
   l<<"洪萤储";
   l<<"堵松 ";
   l<<"勾霆妍";
   l<<"孙唱月";
   l<<"步奇胜";
   l<<"汲钧 ";
   l<<"子车优";
   l<<"濮友巧";
   l<<"程波涛";
   l<<"狄颜康";
   l<<"盖芷 ";
   l<<"司洙 ";
   l<<"宫怡凤";
   l<<"仰姒彤";
   l<<"沃芮绫";
   l<<"湛瑞绣";
   l<<"米高芬";
   l<<"空西华";
   l<<"东郭姒";
   l<<"戎寄灵";
   l<<"糜芫靳";
   l<<"容红沐";
   l<<"廖栾 ";
   l<<"岳傲丝";
   l<<"诸葛香";
   l<<"颛孙嵩";
   l<<"薛嘉德";
   l<<"扈靖井";
   l<<"甘天思";
   l<<"益坤 ";
   l<<"祖汲涑";
   l<<"井仰 ";
   l<<"孔焱弱";
   l<<"麻涔 ";
   l<<"阚颖初";
   l<<"时凤 ";
   l<<"戎钐榳";
   l<<"包擎秀";
   l<<"呼延斌";
   l<<"毕乌 ";
   l<<"廉蓝颜";
   l<<"靳茈芯";
   l<<"须悒 ";
   l<<"富樱囧";
   l<<"亢悦乐";
   l<<"关思雅";
   l<<"洪笙 ";
   l<<"钮莛 ";
   l<<"俟雁 ";
   l<<"璩清婉";
   l<<"习颜葶";
   l<<"骆炳 ";
   l<<"西门珩";
   l<<"能契筝";
   l<<"杨乾 ";
   l<<"牟豁颤";
   l<<"蓝鸿畅";
   l<<"淳于焱";
   l<<"扈威钧";
   l<<"路妍绯";
   l<<"汲淇涑";
   l<<"刁襄纹";
   l<<"弘竺剑";
   l<<"厉翎 ";
   l<<"辛穆嚣";
   l<<"佘鸿 ";
   l<<"燕骁茈";
   l<<"卞芮契";
   l<<"终康 ";
   l<<"吉誉茗";
   l<<"帅雍靖";
   l<<"胡灵凡";
   l<<"公败岩";
   l<<"元淑静";
   l<<"戈绫 ";
   l<<"荣鞯琳";
   l<<"蒋莺垣";
   l<<"秋成危";
   l<<"甘翎 ";
   l<<"胡清 ";
   l<<"梁丘灵";
   l<<"子车兰";
   l<<"水储 ";
   l<<"顾储垣";
   l<<"昌娩戾";
   l<<"利雯 ";
   l<<"侯悠奕";
   l<<"别悒 ";
   l<<"舒苇然";
   l<<"司纲 ";
   l<<"冯访儿";
   l<<"法水蓝";
   l<<"盖荧沁";
   l<<"张愫宛";
   l<<"敖樱澜";
   l<<"昌雅昶";
   l<<"鄢筝 ";
   l<<"邢雍垣";
   l<<"计萤 ";
   l<<"卞棠华";
   l<<"公阁芫";
   l<<"池访烟";
   l<<"金莛 ";
   l<<"邰彦慧";
   l<<"养芷卉";
   l<<"匡葶鞅";
   l<<"俟勒 ";
   l<<"陶淇瑛";
   l<<"白栾卿";
   l<<"靳稀惮";
   l<<"栾宛师";
   l<<"裘沂 ";
   l<<"詹疾绫";
   l<<"支桐瑛";
   l<<"喻衣真";
   l<<"岑茗 ";
   l<<"郏匪驳";
   l<<"樊妍玲";
   l<<"居珠悲";
   l<<"孙莞樱";
   l<<"王筝芝";
   l<<"纪昊空";
   l<<"方宛清";
   l<<"凤栾 ";
   l<<"党垣 ";
   l<<"步玲威";
   l<<"冯寇卿";
   l<<"曾婴 ";
   l<<"文香伊";
   l<<"陆绯莛";
   l<<"咸秀悲";
   l<<"叶珊 ";
   l<<"奚伟宸";
   l<<"白匪班";
   l<<"颜鞯驳";
   l<<"权羿晖";
   l<<"娄冥傥";
   l<<"缪澜 ";
   l<<"山匕 ";
   l<<"缪栾邴";
   l<<"程莛 ";
   l<<"屠琦 ";
   l<<"缑雁衫";
   l<<"国代真";
   l<<"谈罡嫣";
   l<<"慕棋机";
   l<<"哈柔清";
   l<<"年晰晖";
   l<<"邰莺邑";
   l<<"葛正志";
   l<<"刘炳 ";
   l<<"荣蹇康";
   l<<"终刚 ";
   l<<"宰父井";
   l<<"唐彬彬";
   l<<"沙师 ";
   l<<"鞠修真";
   l<<"薛芮芫";
   l<<"安勒 ";
   l<<"嵇笙焦";
   l<<"杜秋翼";
   l<<"相茗 ";
   l<<"邱茹妖";
   l<<"石瀚海";
   l<<"闾丘宛";
   l<<"索汲蓉";
   l<<"罗智鑫";
   l<<"汤紫翎";
   l<<"卫月旭";
   l<<"通颦 ";
   l<<"应若祥";
   l<<"乜翎悲";
   l<<"单于丝";
   l<<"扶晓亦";
   l<<"严竺愫";
   l<<"华媛媛";
   l<<"糜雁 ";
   l<<"鄢星河";
   l<<"郁彤嫣";
   l<<"仰佳臣";
   l<<"訾莛 ";
   l<<"翟隶 ";
   l<<"鲁秋萌";
   l<<"巩鞯芫";
   l<<"惠枫惮";
   l<<"能乾香";
   l<<"周鑫青";
   l<<"宗康 ";
   l<<"袁寇 ";
   l<<"充芯紫";
   l<<"伊宏邈";
   l<<"闫翰 ";
   l<<"侯弼 ";
   l<<"毋傥 ";
   l<<"伍易蓉";
   l<<"任婴 ";
   l<<"费雁班";
   l<<"厍莆瑛";
   l<<"闾丘豪";
   l<<"孔涛坤";
   l<<"幸颜涔";
   l<<"赫连青";
   l<<"赖纹芝";
   l<<"越盈 ";
   l<<"甄颐和";
   l<<"钭英飙";
   l<<"夔弼 ";
   l<<"钟离秀";
   l<<"宰鹰笙";
   l<<"瞿俊健";
   l<<"薄蹇雍";
   l<<"柯灵紫";
   l<<"福沅乌";
   l<<"鲁擎 ";
   l<<"山芯纹";
   l<<"姜枫淇";
   l<<"冷盈衣";
   l<<"章采文";
   l<<"巩芙寇";
   l<<"魏鹰刚";
   l<<"西门柔";
   l<<"牧罡惠";
   l<<"翁春海";
   l<<"通芳敏";
   l<<"汲宛芷";
   l<<"左广洲";
   l<<"邱芫芙";
   l<<"湛竟泉";
   l<<"尤枫涑";
   l<<"丁文成";
   l<<"封松囧";
   l<<"鞠蓉姝";
   l<<"鲍烙康";
   l<<"师紫 ";
   l<<"申屠朗";
   l<<"那紫裘";
   l<<"濮阳秋";
   l<<"左怡和";
   l<<"西门青";
   l<<"杭澜弱";
   l<<"房英哲";
   l<<"雍丑康";
   l<<"巴箴 ";
   l<<"舒博匕";
   l<<"索莆嚣";
   l<<"余山河";
   l<<"蓟娩铭";
   l<<"姜孱芮";
   l<<"施斌续";
   l<<"肖菀 ";
   l<<"曾艳 ";
   l<<"余凤储";
   l<<"爱康邑";
   l<<"帅盈 ";
   l<<"乌书芹";
   l<<"年若云";
   l<<"张凡茗";
   l<<"富菀 ";
   l<<"周康 ";
   l<<"印允醒";
   l<<"蒙沅逊";
   l<<"归海绎";
   l<<"昝葶荟";
   l<<"卜莞彤";
   l<<"钟离会";
   l<<"昝澜鑫";
   l<<"焦小佳";
   l<<"子车明";
   l<<"勾芷 ";
   l<<"宗鹤羿";
   l<<"令狐瑛";
   l<<"段芮婴";
   l<<"别涛婴";
   l<<"乌梓颖";
   l<<"公西婴";
   l<<"堵博 ";
   l<<"能芷 ";
   l<<"左淇裘";
   l<<"湛绫澜";
   l<<"饶函 ";
   l<<"祝紊茈";
   l<<"越豁 ";
   l<<"全颖裘";
   l<<"林竺荧";
   l<<"那邴雁";
   l<<"闫剑 ";
   l<<"雷绮素";
   l<<"安芙姝";
   l<<"红豁 ";
   l<<"蔺忻 ";
   l<<"步焦扬";
   l<<"魏彤鹤";
   l<<"项盈穆";
   l<<"贲兰邑";
   l<<"居斓淇";
   l<<"顾芯沅";
   l<<"麻疾擎";
   l<<"安翰芙";
   l<<"羿珊 ";
   l<<"居笑天";
   l<<"端木朋";
   l<<"阙正青";
   l<<"隆艳 ";
   l<<"帅靳 ";
   l<<"诸雍涫";
   l<<"缪耷 ";
   l<<"昝宁乐";
   l<<"鲍紫 ";
   l<<"金弼誉";
   l<<"屈卓默";
   l<<"姚遥豪";
   l<<"年翎丑";
   l<<"叶蓝达";
   l<<"鲍稀 ";
   l<<"裴葶澜";
   l<<"江奄乞";
   l<<"窦斩寇";
   l<<"缑臻骁";
   l<<"司徒惮";
   l<<"宁悲 ";
   l<<"法盼曾";
   l<<"胥博超";
   l<<"施芳奎";
   l<<"季元基";
   l<<"史锦程";
   l<<"仰迎夏";
   l<<"陈烙寇";
   l<<"褚海女";
   l<<"贺珊靖";
   l<<"杭鹰 ";
   l<<"翁匪贞";
   l<<"支恬雅";
   l<<"井莺弱";
   l<<"习紊宛";
   l<<"盛涑芹";
   l<<"祝萤 ";
   l<<"轩辕云";
   l<<"宣湘 ";
   l<<"陆语儿";
   l<<"卓邑彤";
   l<<"弘弱 ";
   l<<"富真百";
   l<<"衡柏鸣";
   l<<"羿鲂桐";
   l<<"季莹妍";
   l<<"慎曼易";
   l<<"曲香 ";
   l<<"裴威若";
   l<<"商芫斌";
   l<<"林若翾";
   l<<"越立人";
   l<<"权雁扬";
   l<<"管诗涵";
   l<<"王翰墨";
   l<<"费翔迎";
   l<<"邢珠 ";
   l<<"喻小瑜";
   l<<"吉淇仰";
   l<<"古苏石";
   l<<"欧鑫筝";
   l<<"桂戾栾";
   l<<"从悒琦";
   l<<"夹谷枫";
   l<<"杨宏富";
   l<<"籍珊逊";
   l<<"东郭淑";
   l<<"牟璎囧";
   l<<"沈莹筝";
   l<<"子车苠";
   l<<"禄艳兰";
   l<<"毕城紫";
   l<<"壤驷芮";
   l<<"羿菁怡";
   l<<"白芙洙";
   l<<"卫傥厉";
   l<<"公炳 ";
   l<<"向伊沅";
   l<<"谯笪定";
   l<<"厍阁 ";
   l<<"郦芷瑛";
   l<<"益芝雍";
   l<<"巢雁铭";
   l<<"段糜璎";
   l<<"濮阳念";
   l<<"慕琦城";
   l<<"洪筮井";
   l<<"邬康威";
   l<<"巫马伊";
   l<<"蓬柔 ";
   l<<"弓孱 ";
   l<<"易依风";
   l<<"袁沛凝";
   l<<"皇甫沅";
   l<<"廉珅员";
   l<<"隆悒 ";
   l<<"厍荟惠";
   l<<"雷元思";
   l<<"储捕 ";
   l<<"尚琦荠";
   l<<"魏贞 ";
   l<<"昝瑾梅";
   l<<"查姿 ";
   l<<"阮柔荠";
   l<<"秋鞅艳";
   l<<"钦乐松";
   l<<"庄雁祥";
   l<<"太叔遥";
   l<<"费焦青";
   l<<"辛澜荟";
   l<<"厍嫣 ";
   l<<"姬城 ";
   l<<"糜阁 ";
   l<<"赖剑储";
   l<<"杭子平";
   l<<"张嚣竺";
   l<<"董冥幽";
   l<<"通擎愫";
   l<<"龚颦涑";
   l<<"聂剑筝";
   l<<"曹苡丝";
   l<<"赫连珊";
   l<<"纪戾颜";
   l<<"朱鹰戾";
   l<<"盖蓉绮";
   l<<"耳卿青";
   l<<"姜安彤";
   l<<"彭弼 ";
   l<<"鲜于婉";
   l<<"南门宛";
   l<<"荆琦 ";
   l<<"党乐淏";
   l<<"贝钧焦";
   l<<"吴寇盈";
   l<<"桂莛 ";
   l<<"幸克晗";
   l<<"墨竺鹤";
   l<<"邢松涫";
   l<<"蒋荆荟";
   l<<"羊舌桄";
   l<<"左嚣柔";
   l<<"严洙傥";
   l<<"汪无血";
   l<<"皇甫达";
   l<<"纪翰艳";
   l<<"魏华桐";
   l<<"俞扬洙";
   l<<"闻荠 ";
   l<<"藏烙耷";
   l<<"罗芹 ";
   l<<"邹蹇豁";
   l<<"闻文彦";
   l<<"叶姝糜";
   l<<"习颦襄";
   l<<"甘高洁";
   l<<"辛荧 ";
   l<<"晋湘擎";
   l<<"双涔 ";
   l<<"靳丝捕";
   l<<"梁灵珊";
   l<<"戈愫厉";
   l<<"俞豁铭";
   l<<"施傀儡";
   l<<"闾丘孱";
   l<<"虞涫荟";
   l<<"藏政举";
   l<<"宰父囧";
   l<<"欧芷卿";
   l<<"谈沁 ";
   l<<"邹阁若";
   l<<"师鸿 ";
   l<<"颜疾碧";
   l<<"藤博文";
   l<<"童靳 ";
   l<<"苍萍嫣";
   l<<"管菀沁";
   l<<"周素洙";
   l<<"余匪 ";
   l<<"隗莛珊";
   l<<"倪丑 ";
   l<<"从荧 ";
   l<<"宇文雪";
   l<<"胥婷之";
   l<<"牧瑾兼";
   l<<"文疾汲";
   l<<"吕孱 ";
   l<<"昌芹斩";
   l<<"满傥井";
   l<<"岳高逸";
   l<<"包嘉实";
   l<<"欧祥 ";
   l<<"成弼 ";
   l<<"公俊弼";
   l<<"花卿 ";
   l<<"华泽珲";
   l<<"贝珍班";
   l<<"贝炳鹰";
   l<<"公良彤";
   l<<"穆笙筝";
   l<<"谈班紫";
   l<<"濮乾 ";
   l<<"危沛容";
   l<<"牧洙盈";
   l<<"令狐续";
   l<<"彭竹雨";
   l<<"支彤鑫";
   l<<"诸葛卿";
   l<<"吴紫 ";
   l<<"第五鹤";
   l<<"王珍 ";
   l<<"须姒弼";
   l<<"岳莞姿";
   l<<"郝涛澜";
   l<<"糜香巧";
   l<<"乜光亮";
   l<<"鲍倩语";
   l<<"暨焦厉";
   l<<"暨灵凤";
   l<<"伏珍莛";
   l<<"牧沅 ";
   l<<"牟绮纲";
   l<<"瞿富续";
   l<<"谭丽丽";
   l<<"单于芾";
   l<<"封姿兰";
   l<<"彭惮凛";
   l<<"满兰葶";
   l<<"公莎莎";
   l<<"桑颜 ";
   l<<"谈卓默";
   l<<"诸炳 ";
   l<<"张翼 ";
   l<<"仲紫靖";
   l<<"羿凡 ";
   l<<"习芝阁";
   l<<"仰湘桐";
   l<<"百里衫";
   l<<"端木清";
   l<<"杭基铫";
   l<<"甘丑 ";
   l<<"宗政湘";
   l<<"宰驳 ";
   l<<"微生俊";
   l<<"柳秋伊";
   l<<"杭誉纹";
   l<<"邹依依";
   l<<"微生奄";
   l<<"詹秀桐";
   l<<"司空秀";
   l<<"平惮 ";
   l<<"邹忻姒";
   l<<"闻秀厉";
   l<<"敖骁 ";
   l<<"通炳鞯";
   l<<"崔清嵩";
   l<<"焦霆 ";
   l<<"顾点禄";
   l<<"颛孙擎";
   l<<"公良祥";
   l<<"公孙衣";
   l<<"冀鞯函";
   l<<"呼延耷";
   l<<"牛安民";
   l<<"毕匕隶";
   l<<"饶香 ";
   l<<"管荟 ";
   l<<"毛琳嵩";
   l<<"冀奇思";
   l<<"计雁 ";
   l<<"沙碧惠";
   l<<"端木贞";
   l<<"单于荧";
   l<<"养耷颤";
   l<<"艾戾奄";
   l<<"相子希";
   l<<"毋慧语";
   l<<"戴芳茵";
   l<<"芮芝 ";
   l<<"暨彤霞";
   l<<"廉雁 ";
   l<<"钦妍鲂";
   l<<"钦隶 ";
   l<<"苏娅玟";
   l<<"梁良才";
   l<<"靳淇 ";
   l<<"靳乞 ";
   l<<"富芳 ";
   l<<"东凛弼";
   l<<"耳芳柔";
   l<<"逄依波";
   l<<"方沂鹰";
   l<<"许听蓉";
   l<<"司徒月";
   l<<"盛擎坤";
   l<<"厉筝艳";
   l<<"农兰蕙";
   l<<"禄芳铭";
   l<<"长孙莹";
   l<<"汝立言";
   l<<"简弱纹";
   l<<"曲晓啸";
   l<<"谭文瑞";
   l<<"养芳班";
   l<<"曾靳琳";
   l<<"钟离涑";
   l<<"鄂鞯 ";
   l<<"茹彤臻";
   l<<"堵悒秀";
   l<<"乌囧 ";
   l<<"慕容芯";
   l<<"屠遥鞅";
   l<<"宓凛疾";
   l<<"拓拔誉";
   l<<"包洙 ";
   l<<"谢臻 ";
   l<<"喻荆 ";
   l<<"鄢姿瑛";
   l<<"倪茂德";
   l<<"贲丑斌";
   l<<"易颤 ";
   l<<"许嵩鸿";
   l<<"仲孙涛";
   l<<"孟嘉树";
   l<<"谷雅鑫";
   l<<"法绫磬";
   l<<"公湘驳";
   l<<"闻翎 ";
   l<<"蒋隶 ";
   l<<"夹谷芾";
   l<<"富香葶";
   l<<"容芝 ";
   l<<"裘襄坤";
   l<<"祝悒筝";
   l<<"羿嵩兰";
   l<<"康妍珊";
   l<<"归海凡";
   l<<"羊舌新";
   l<<"燕坤罡";
   l<<"鞠涑 ";
   l<<"鄂芮 ";
   l<<"窦涛穆";
   l<<"全碧曼";
   l<<"莘沅芷";
   l<<"刁焦汲";
   l<<"万芷 ";
   l<<"岑胜城";
   l<<"虞富寇";
   l<<"宰父京";
   l<<"舒卿萧";
   l<<"钮瑛姿";
   l<<"谷梁浩";
   l<<"琴博丽";
   l<<"慕孱绯";
   l<<"于厉凡";
   l<<"朱烙 ";
   l<<"宿英朗";
   l<<"温青烙";
   l<<"訾竺荠";
   l<<"莘储嵩";
   l<<"刘颖鹰";
   l<<"胡茗 ";
   l<<"邰靳靖";
   l<<"满涑 ";
   l<<"尚盈珩";
   l<<"宰父驳";
   l<<"成乌樱";
   l<<"蓬疾 ";
   l<<"元枫珠";
   l<<"邰悒惮";
   l<<"蓟丽玉";
   l<<"蔚傥蓉";
   l<<"益清卓";
   l<<"金垣戎";
   l<<"毋蹇班";
   l<<"慕容誉";
   l<<"公西芝";
   l<<"巫斌雍";
   l<<"宁芹筝";
   l<<"廉颦汲";
   l<<"贾树壮";
   l<<"司寇斩";
   l<<"郜雁 ";
   l<<"端木臻";
   l<<"暨捕续";
   l<<"涂惮沂";
   l<<"昝斌 ";
   l<<"晏玲荧";

}



