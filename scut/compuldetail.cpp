#include "compuldetail.h"
#include "ui_compuldetail.h"
#include <QLayout>
#include <QTextCodec>
#include <sstream>
#include <QDir>
#include <QDebug>

CompulDetail::CompulDetail(int number,int row,CompulMessage *parent) :
    QDialog(parent),
    ui(new Ui::CompulDetail),
    classNumber(number),
    cWidget(parent),
    row(row)
{
    ui->setupUi(this);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    initialize();
    initTable(sTable);
    initWidget();
}

CompulDetail::~CompulDetail()
{
    delete ui;
}

void CompulDetail::initialize(){
    back = new QPushButton;
    back->setText("返回");

    sTable = new QTableWidget(0,4);
    stringstream ss;
    ss << classNumber;
    ss >> location;
    location = "E:\\Qt\\scutStatistic\\admin\\compulsory\\"+location;
    connect(back,SIGNAL(clicked()),this,SLOT(onBackClicked()));
}

void CompulDetail::initTable(QTableWidget *sTable){

    QTableWidgetItem *item1 = cWidget->sTable->item(row,1);
    QTableWidgetItem *item2 = cWidget->sTable->item(row,0);
    QTableWidgetItem *item3 = cWidget->sTable->item(row,2);

    QString syear = item1->text();
    QString smajor = item2->text();
    QString snumber = item3->text();

    string year = syear.toStdString();
    string major = smajor.toStdString();
    string number = snumber.toStdString();

    string stuItem = year + major + number;

    // 计算班别人数
    QDir *calNumber = new QDir;
    bool existing = true;
    int calculate = atoi((year+major+number+"01").c_str());
    string loc = "E:\\Qt\\scutStatistic\\student\\" + major + "\\" + year +
                 "\\" + number + "\\";
    while(existing){
        stringstream ss;
        string calString;
        ss << calculate;
        ss >> calString;
        existing = calNumber->exists((loc+calString).c_str());
        calculate++;
    }
    calculate-=2;//进行完该操作后为该班最大的学号
    int stuAmount = calculate - atoi((year+major+number+"00").c_str());

    QFileInfo file((location+"("+stuItem+")grade.txt").c_str());
    bool exist = file.isFile();

    //设置表格行标题
    QStringList headerLabels;

    if(!exist)
        headerLabels << "学号" << "专业代号" << "入学时间" << "班号";
    else{
        sTable->setColumnCount(6);
        headerLabels << "学号" << "专业代号" << "入学时间" << "班号" << "成绩" << "排名";
    }
    sTable->setHorizontalHeaderLabels(headerLabels);

    //sTable->verticalHeader()->setVisible(false);   //隐藏列表头

    //设置编辑方式
    sTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    sTable->setRowCount(stuAmount);

    for(int i=0;i<stuAmount;i++){
        int temp = atoi((year+major+number+"01").c_str())+i;
        // 初始化表格
        QTableWidgetItem *item0 = new QTableWidgetItem;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QTableWidgetItem *item3 = new QTableWidgetItem;
        stringstream s1;
        string str;
        s1 << temp;
        s1 >> str;

        string s;

        QString sNumber = QString::fromStdString(str);
        item0->setText(sNumber);
        sTable->setItem(i,0,item0);

        s = str[4];
        QString mNumber = QString::fromStdString(s);
        item1->setText(mNumber);
        sTable->setItem(i,1,item1);

        s.assign(str,0,4);
        QString year = QString::fromStdString(s);
        item2->setText(year);
        sTable->setItem(i,2,item2);

        s = str[5];
        QString cNumber = QString::fromStdString(s);
        item3->setText(cNumber);
        sTable->setItem(i,3,item3);
    }
    //初始化成绩与排名
    if(exist){
        fstream grade((location+"("+stuItem+")grade.txt").c_str());
        string sn = "",g,r;
        while(sn != "-1"){
            grade >> sn;
            if(sn == "-1")
                break;
            grade >> g >> r;
            QList<QTableWidgetItem*> itemVec=sTable->findItems(QString::fromStdString(sn),Qt::MatchExactly);
            int row = itemVec.at(0)->row();
            addWidget(sTable,row,g,r);
        }
        grade.close();
    }
}

void CompulDetail::addWidget(QTableWidget *table,int row,string grade, string rank){

    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
    QString g = QString::fromStdString(grade);
    QString r = QString::fromStdString(rank);
    item1->setText(g);
    item2->setText(r);
    table->setItem(row,4,item1);
    table->setItem(row,5,item2);

}

void CompulDetail::initWidget(){
    // init widget
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(40);
    hLayout->addWidget(back);
    vLayout->addWidget(sTable);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);
    this->resize(500, 350);
    this->move(400,150);
    this->setWindowTitle("已选学生");
}

void CompulDetail::onBackClicked(){
    close();
}

