#include "electmessage.h"
#include "ui_electmessage.h"
#include <QLayout>
#include <QTextCodec>
#include <sstream>
#include <QDir>
#include <QDebug>

ElectMessage::ElectMessage(int number,AdminWidget *parent) :
    QDialog(parent),
    ui(new Ui::ElectMessage),
    classNumber(number)
{
    ui->setupUi(this);
    aWidget = parent;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    initialize();
    initTable(sTable);
    initWidget();
}

ElectMessage::~ElectMessage()
{
    delete ui;
}

void ElectMessage::initialize(){
    curNumber = new QLabel;
    back = new QPushButton;
    back->setText("����");

    sTable = new QTableWidget(0,4);
    stringstream ss;
    ss << classNumber;
    ss >> location;
    location = "E:\\Qt\\scutStatistic\\admin\\elective\\"+location;
    connect(back,SIGNAL(clicked()),this,SLOT(onBackClicked()));
}

void ElectMessage::initTable(QTableWidget *sTable){

    QFileInfo file((location+"grade.txt").c_str());
    bool exist = file.isFile();

    //���ñ���б���
    QStringList headerLabels;

    if(!exist)
        headerLabels << "ѧ��" << "רҵ����" << "��ѧʱ��" << "���";
    else{
        sTable->setColumnCount(6);
        headerLabels << "ѧ��" << "רҵ����" << "��ѧʱ��" << "���" << "�ɼ�" << "����";
    }
    sTable->setHorizontalHeaderLabels(headerLabels);

    //sTable->verticalHeader()->setVisible(false);   //�����б�ͷ

    //���ñ༭��ʽ
    sTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i = 0;
    string str = "";
    fstream list((location+".txt").c_str());
    while(str != "-1"){
        getline(list,str);
        if(str == "-1")
            break;
        sTable->setRowCount(i+1);
        // ��ʼ�����
        QTableWidgetItem *item0 = new QTableWidgetItem;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QTableWidgetItem *item3 = new QTableWidgetItem;
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

        i++;
    }
    list.close();

    // ��ʼ������
    stringstream ss;
    string cNumber;
    ss << i;
    ss >> cNumber;
    curNumber->setText(QString::fromStdString("���ڵ�������"+cNumber));

    //��ʼ���ɼ�������
    if(exist){
        fstream grade((location+"grade.txt").c_str());
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

void ElectMessage::addWidget(QTableWidget *table,int row,string grade, string rank){

    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
    QString g = QString::fromStdString(grade);
    QString r = QString::fromStdString(rank);
    item1->setText(g);
    item2->setText(r);
    table->setItem(row,4,item1);
    table->setItem(row,5,item2);

}

void ElectMessage::initWidget(){
    // init widget
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout1->addStretch(30);
    hLayout1->addWidget(curNumber);
    hLayout2->addStretch(40);
    hLayout2->addWidget(back);
    vLayout->addLayout(hLayout1);
    vLayout->addWidget(sTable);
    vLayout->addLayout(hLayout2);

    this->setLayout(vLayout);
    this->resize(500, 350);
    this->move(400,150);
    this->setWindowTitle("��ѡѧ��");
}

void ElectMessage::onBackClicked(){
    close();
}
