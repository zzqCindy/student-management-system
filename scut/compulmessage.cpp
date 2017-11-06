#include "compulmessage.h"
#include "ui_compulmessage.h"
#include "compuldetail.h"
#include "addstudent.h"
#include <QTextCodec>
#include <QLayout>
#include <sstream>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <algorithm>
#include <fstream>

CompulMessage::CompulMessage(AdminWidget *parent,Course &c,int cn) :
    QDialog(parent),
    ui(new Ui::CompulMessage),
    currentNumber(cn)
{
    ui->setupUi(this);
    aWidget = parent;
    course = c;
    type=0;
    classNumber = course.getClassNumber();

    initialize();
    initTable(sTable);
    initWidget();
}

CompulMessage::CompulMessage(int cNumber,int type,QWidget *parent,int cn):
    QDialog(parent),
    ui(new Ui::CompulMessage),
    currentNumber(cn),
    classNumber(cNumber),
    type(type)
{
    ui->setupUi(this);

    initialize();
    add->setVisible(false);
    initTable(sTable);
    initWidget();

    // 显示成绩
}

CompulMessage::~CompulMessage()
{
    delete ui;
}

void CompulMessage::initialize(){
    curNumber = new QLabel;
    add = new QPushButton;
    back = new QPushButton;
    add->setText("添加学生");
    back->setText("返回");
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    if(type)
        sTable = new QTableWidget(0,5);
    else
        sTable = new QTableWidget(0,4);
    stringstream s2;
    s2 << classNumber;
    s2 >> location;
    location = "E:\\Qt\\scutStatistic\\admin\\compulsory\\"+location+".txt";
    connect(back,SIGNAL(clicked()),this,SLOT(onBackClicked()));
    connect(add,SIGNAL(clicked()),this,SLOT(onAddClicked()));
}

void CompulMessage::initTable(QTableWidget *sTable){
    // 计算人数
    QDir *calNumber = new QDir;
    bool exist;

    //设置表格行标题
    QStringList headerLabels;
    headerLabels << "专业代号" << "入学时间" << "班号";
    sTable->setHorizontalHeaderLabels(headerLabels);

    //sTable->verticalHeader()->setVisible(false);   //隐藏列表头

    //设置编辑方式
    sTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i = 0;
    string str = "";
    fstream list(location.c_str());
    while(str != "-1"){
        int mn,cy,cn;
        list >> mn;
        if(mn == -1)
            break;
        list >> cy >> cn;
        sTable->setRowCount(i+1);

        string classLocate = "E:\\Qt\\scutStatistic\\student\\";

        // 初始化表格
        QTableWidgetItem *item0 = new QTableWidgetItem;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;

        QString mNumber = QString::number(mn,10);
        item0->setText(mNumber);
        sTable->setItem(i,0,item0);
        classLocate += mNumber.toStdString() + "\\";

        QString year = QString::number(cy,10);
        item1->setText(year);
        sTable->setItem(i,1,item1);
        classLocate += year.toStdString() + "\\";

        QString cNumber = QString::number(cn,10);
        item2->setText(cNumber);
        sTable->setItem(i,2,item2);
        classLocate += cNumber.toStdString() + "\\";

        detail[i] = new QPushButton;
        detail[i]->setText("详细信息");
        connect(detail[i],SIGNAL(clicked()),this,SLOT(onDetailClicked()));
        sTable->setCellWidget(i,3,detail[i]);

        if(type){
            setGrade[i] = new QPushButton;
            setGrade[i]->setText("设置成绩");
            connect(setGrade[i],SIGNAL(clicked()),this,SLOT(onSetGradeClicked()));
            sTable->setCellWidget(i,4,setGrade[i]);
        }

        // 初始化现有人数
        string curNumString = year.toStdString() + mNumber.toStdString()
                + cNumber.toStdString() + "01";
        int curNum = atoi(curNumString.c_str());
        for(curNum; curNum>0; curNum++){
            stringstream ss;
            ss << curNum;
            string tempNumber;
            ss >> tempNumber;
            exist = calNumber->exists((classLocate+tempNumber).c_str());
            if(!exist)
                break;
        }
        currentNumber += curNum - atoi(curNumString.c_str());

        i++;
    }
    list.close();

    stringstream s1;
    string cNumber;
    s1 << currentNumber;
    s1 >> cNumber;
    curNumber->setText(QString::fromStdString("现在的人数："+cNumber));
}

void CompulMessage::initWidget(){

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout1->addStretch(30);
    hLayout1->addWidget(curNumber);
    hLayout2->addStretch(20);
    hLayout2->addWidget(add);
    hLayout2->addWidget(back);
    vLayout->addLayout(hLayout1);
    vLayout->addWidget(sTable);
    vLayout->addLayout(hLayout2);

    this->setLayout(vLayout);
    this->resize(500, 350);
    this->move(400,150);
    this->setWindowTitle("学生");
}

void CompulMessage::onBackClicked(){
    close();
}

void CompulMessage::onAddClicked(){
    AddStudent as(this);
    as.exec();
}

void CompulMessage::onDetailClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = sTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();

    CompulDetail cd(classNumber,row,this);
    cd.exec();
}

bool strict_weak_order(const pair<double, string> a, const pair<double, string> b)
{
   return a.first > b.first;
}

void CompulMessage::onSetGradeClicked(){

    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = sTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();

    // 获取表格内容
    QTableWidgetItem *item0 = sTable->item(row,0);
    QTableWidgetItem *item1 = sTable->item(row,1);
    QTableWidgetItem *item2 = sTable->item(row,2);
    string mNumber = item0->text().toStdString();
    string year = item1->text().toStdString();
    string cNumber = item2->text().toStdString();
    string locate = "(" + year + mNumber + cNumber + ")";

    // 选取文件
    QString filename = QFileDialog::getOpenFileName(
       this,
       "Open Document",
       QDir::currentPath(),
       "Document files (*.doc *.rtf);;All files(*.*)");
    if (!filename.isNull()) { //用户选择了文件
       QMessageBox::information(this, "提示", "成功获得文件", QMessageBox::Ok);
    }
    else
        return;

    string classLocation = "E:\\Qt\\scutStatistic\\admin\\";
    string temp;
    stringstream ss;
    ss << classNumber;
    ss >> temp;
    classLocation += "compulsory\\" + temp + locate + "grade.txt";

    // 修改文件
    string sNumber = "";
    double grade;
    vector<pair<double, string> > vec;
    fstream readGrade(filename.toStdString().c_str());
    while(sNumber != "-1"){
        readGrade >> sNumber;
        if(sNumber != "-1"){
            readGrade >> grade;
            vec.push_back(make_pair<double,string>(grade,sNumber));
        }
    }
    readGrade.close();
    sort(vec.begin(),vec.end(),strict_weak_order);

    qDebug() << classLocation.c_str();

    int i = 1,count = 0;
    fstream grade1(classLocation.c_str(),ios::trunc|ios::out);
    for(unsigned int j=0;j<vec.size();j++){
        if(j != 0 && vec[j].first == vec[j-1].first )
            count++;
        else
            count = 0;
        grade1 << vec[j].second << " " << vec[j].first << " " << i-count <<endl;
        i++;
    }
    grade1 << -1;
    grade1.close();
}
