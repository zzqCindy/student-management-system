#include "adminwidget.h"
#include "compulmessage.h"
#include "electmessage.h"
#include "changepassword.h"
#include <QLayout>
#include <fstream>
#include <sstream>
#include <QTextCodec>
#include <QMessageBox>
#include <QDir>
#include <QtGui>
#include <QDebug>
#include <windows.h>
using namespace std;

AdminWidget::AdminWidget(Admin a,QWidget *parent) :
    QWidget(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    admin =a;

    // 设置欢迎语
    string str="欢迎你，";
    string temp = admin.getID();
    str += temp;
    str += "管理员";
    welcomeLabel = new QLabel(QString::fromStdString(str));
    tabWidget = new QTabWidget();
    changePassword = new QPushButton;
    changePassword->setText(" 修改密码 ");
    connect(changePassword,SIGNAL(clicked()),this,SLOT(changePasswordClicked()));

    // 文件存放位置
    aLocate = "E:\\Qt\\scutStatistic\\admin\\";
    tLocate = "E:\\Qt\\scutStatistic\\teacher\\";
    sLocate = "E:\\Qt\\scutStatistic\\student\\";

    fstream inputComp((aLocate+"compulsory\\list.txt").c_str());
    while(!inputComp.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        inputComp >> cn ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(cn==-1)
            break;
        inputComp >> sn >> w >> ct >> c >> cna >> t;
        Course temp(sn,cn,w,ct,c,cna,t);
        admin.compul.push_back(temp);
    }
    inputComp.close();

    fstream inputElet((aLocate+"elective\\list.txt").c_str());
    while(!inputElet.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        bool s;
        inputElet >> cn ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(cn==-1)
            break;
        inputElet >> s >> sn >> w >> ct >> c >> cna >> t;    
        Course temp(sn,cn,w,ct,c,cna,t,s);
        admin.elect.push_back(temp);
    }
    inputElet.close();

    fstream inputAppl("E:\\Qt\\scutStatistic\\admin\\apply.txt");
    while(!inputAppl.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        inputAppl >> cn ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(cn==-1)
            break;
        inputAppl >> sn >> w >> ct >> c >> cna >> t;
        Course temp(sn,cn,w,ct,c,cna,t);
        admin.apply.push_back(temp);
    }
    inputAppl.close();

    fstream inputTeacher((tLocate+"login.txt").c_str());
    while(!inputTeacher.eof()){
        char id[10],pw[20];
        string n;
        inputTeacher >> id ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(!strcmp(id,"-1"))
            break;
        inputTeacher >> pw >> n;
        Teacher teacher(id,pw,n);
        admin.teacher.push_back(teacher);
    }
    inputAppl.close();

    applyTable = new QTableWidget(0,8);
    compulTable = new QTableWidget(0,8);
    electTable = new QTableWidget(0,9);

    initApplyTable(applyTable);
    initCompulTable(compulTable);
    initElectTable(electTable);

    tabWidget->addTab(applyTable,"申请列表");
    tabWidget->addTab(compulTable,"必修课");
    tabWidget->addTab(electTable,"选修课");

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QVBoxLayout *vLayout1 = new QVBoxLayout;
    hLayout1->addWidget(welcomeLabel);
    hLayout1->addStretch(20);
    hLayout1->addWidget(changePassword);
    vLayout1->addLayout(hLayout1);
    vLayout1->addWidget(tabWidget);
    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(fresh()));

    this->setLayout(vLayout1);
    this->resize(900, 600);
    this->move(220,80);
    this->setWindowTitle("学生选课系统");
}

void AdminWidget::initApplyTable(QTableWidget *table){
    //设置表格行标题
    QStringList headerLabels;
    headerLabels << "课程名称" << "课程性质" << "教师姓名" << "学分" << "上课人数" << "上课时间"
                 << "" << "";
    table->setHorizontalHeaderLabels(headerLabels);

    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowCount(admin.apply.size());
    for(unsigned int i=0; i<admin.apply.size(); i++){
        QTableWidgetItem *item0 = new QTableWidgetItem;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QTableWidgetItem *item3 = new QTableWidgetItem;
        QTableWidgetItem *item4 = new QTableWidgetItem;
        QTableWidgetItem *item5 = new QTableWidgetItem;

        string c = admin.apply[i].getClassName();
        QString cName = QString::fromStdString(c);
        item0->setText(cName);
        table->setItem(i,0,item0);

        QString type;
        if(admin.apply[i].getClassNumber() == 1000)
            type = QString::fromStdString("必修课");
        else
            type = QString::fromStdString("选修课");
        item1->setText(type);
        table->setItem(i,1,item1);

        string t = admin.apply[i].getTeacher();
        QString tName = QString::fromStdString(t);
        item2->setText(tName);
        table->setItem(i,2,item2);

        int cre = admin.apply[i].getCredit();
        QString cred = QString::number(cre,10);
        item3->setText(cred);
        table->setItem(i,3,item3);

        int sNumber = admin.apply[i].getStudentNumber();
        QString stNumber = QString::number(sNumber,10);
        item4->setText(stNumber);
        table->setItem(i,4,item4);

        string timeForClass = getTimeForClass(admin.apply[i].getWeek(),admin.apply[i].getClassTime());
        QString timeFC = QString::fromStdString(timeForClass);
        item5->setText(timeFC);
        table->setItem(i,5,item5);

        agree[i] = new QPushButton;
        agree[i]->setText("同意");
        connect(agree[i],SIGNAL(clicked()),this,SLOT(agreeClicked()));
        table->setCellWidget(i,6,agree[i]);

        disagree[i] = new QPushButton;
        disagree[i]->setText("拒绝");
        connect(disagree[i],SIGNAL(clicked()),this,SLOT(disagreeClicked()));
        table->setCellWidget(i,7,disagree[i]);

        // 是否停止选课
    }
}

void AdminWidget::initCompulTable(QTableWidget *table){
    //设置表格行标题
    QStringList headerLabels;
    headerLabels << "课程代码" << "课程名称" << "课程性质" << "教师姓名" << "学分" << "上课人数" << "上课时间" << "";
    table->setHorizontalHeaderLabels(headerLabels);

    //table->verticalHeader()->setVisible(false);   //隐藏列表头

    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowCount(admin.compul.size());
    for(unsigned int i=0; i<admin.compul.size(); i++){
        QTableWidgetItem *item0 = new QTableWidgetItem;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QTableWidgetItem *item3 = new QTableWidgetItem;
        QTableWidgetItem *item4 = new QTableWidgetItem;
        QTableWidgetItem *item5 = new QTableWidgetItem;
        QTableWidgetItem *item6 = new QTableWidgetItem;

        int cNumber = admin.compul[i].getClassNumber();
        QString clNumber = QString::number(cNumber,10);
        item0->setText(clNumber);
        table->setItem(i,0,item0);

        string c = admin.compul[i].getClassName();
        QString cName = QString::fromStdString(c);
        item1->setText(cName);
        table->setItem(i,1,item1);

        QString type = QString::fromStdString("必修课");
        item2->setText(type);
        table->setItem(i,2,item2);

        string t = admin.compul[i].getTeacher();
        QString tName = QString::fromStdString(t);
        item3->setText(tName);
        table->setItem(i,3,item3);

        int cre = admin.compul[i].getCredit();
        QString cred = QString::number(cre,10);
        item4->setText(cred);
        table->setItem(i,4,item4);

        int sNumber = admin.compul[i].getStudentNumber();
        QString stNumber = QString::number(sNumber,10);
        item5->setText(stNumber);
        table->setItem(i,5,item5);

        string timeForClass = getTimeForClass(admin.compul[i].getWeek(),admin.compul[i].getClassTime());
        QString timeFC = QString::fromStdString(timeForClass);
        item6->setText(timeFC);
        table->setItem(i,6,item6);

        compulMessage[i] = new QPushButton;
        compulMessage[i]->setText("详细信息");
        connect(compulMessage[i],SIGNAL(clicked()),this,SLOT(cMessageClicked()));
        table->setCellWidget(i,7,compulMessage[i]);
    }
}

void AdminWidget::initElectTable(QTableWidget *table){
    //设置表格行标题
    QStringList headerLabels;
    headerLabels << "课程代码" << "课程名称" << "课程性质" << "教师姓名" << "学分" << "上课人数" << "上课时间" << "" << "";
    table->setHorizontalHeaderLabels(headerLabels);

    //table->verticalHeader()->setVisible(false);   //隐藏列表头

    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowCount(0);
    table->setRowCount(admin.elect.size());
    for(unsigned int i=0; i<admin.elect.size(); i++){
        QTableWidgetItem *item0 = new QTableWidgetItem;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QTableWidgetItem *item3 = new QTableWidgetItem;
        QTableWidgetItem *item4 = new QTableWidgetItem;
        QTableWidgetItem *item5 = new QTableWidgetItem;
        QTableWidgetItem *item6 = new QTableWidgetItem;
        QTableWidgetItem *item7 = new QTableWidgetItem;

        int cNumber = admin.elect[i].getClassNumber();
        QString clNumber = QString::number(cNumber,10);
        item0->setText(clNumber);
        table->setItem(i,0,item0);

        string c = admin.elect[i].getClassName();
        QString cName = QString::fromStdString(c);
        item1->setText(cName);
        table->setItem(i,1,item1);

        QString type = QString::fromStdString("选修课");
        item2->setText(type);
        table->setItem(i,2,item2);

        string t = admin.elect[i].getTeacher();
        QString tName = QString::fromStdString(t);
        item3->setText(tName);
        table->setItem(i,3,item3);

        int cre = admin.elect[i].getCredit();
        QString cred = QString::number(cre,10);
        item4->setText(cred);
        table->setItem(i,4,item4);

        int sNumber = admin.elect[i].getStudentNumber();
        QString stNumber = QString::number(sNumber,10);
        item5->setText(stNumber);
        table->setItem(i,5,item5);

        string timeForClass = getTimeForClass(admin.elect[i].getWeek(),admin.elect[i].getClassTime());
        QString timeFC = QString::fromStdString(timeForClass);
        item6->setText(timeFC);
        table->setItem(i,6,item6);

        electMessage[i] = new QPushButton;
        electMessage[i]->setText("详细信息");
        connect(electMessage[i],SIGNAL(clicked()),this,SLOT(eMessageClicked()));
        table->setCellWidget(i,7,electMessage[i]);

        if(admin.elect[i].getStop()){
            QString clicked = QString::fromStdString("已停止");
            item7->setText(clicked);
            table->setItem(i,8,item7);
        }
        else{
            stopSelect[i] = new QPushButton;
            stopSelect[i]->setText("停止选课");
            connect(stopSelect[i],SIGNAL(clicked()),this,SLOT(stopSelectClicked()));
            table->setCellWidget(i,8,stopSelect[i]);
        }
    }
}

string AdminWidget::getTimeForClass(int w,int t){
    string timeForClass = "";
    switch(w){
        case 1:
            timeForClass += "星期一 第";
            break;
        case 2:
            timeForClass += "星期二 第";
            break;
        case 3:
            timeForClass += "星期三 第";
            break;
        case 4:
            timeForClass += "星期四 第";
            break;
        case 5:
            timeForClass += "星期五 第";
            break;
        case 6:
            timeForClass += "星期六 第";
            break;
        case 7:
            timeForClass += "星期天 第";
            break;
    }
    stringstream ss;
    string tr;
    ss<<t;
    ss>>tr;
    timeForClass = timeForClass + tr + "节";
    return timeForClass;
}

void AdminWidget::delApply(string loc,int row){
    int count = 0;
    string str = "";
    fstream del1((loc+"apply.txt").c_str());
    fstream del2((loc+"temp.txt").c_str(),ios::trunc|ios::out);
    while(str != "-1"){
        getline(del1,str);
        if(count != row)
            del2 << str << endl;
        count++;
    }
    del1.close();
    del2.close();
    str = "";
    fstream del3((loc+"apply.txt").c_str(),ios::trunc|ios::out);
    fstream del4((loc+"temp.txt").c_str());
    while(str != "-1"){
        getline(del4,str);
        del3 << str << endl;
    }
    del3.close();
    del4.close();

    WinExec(("cmd /c del "+loc+"temp.txt").c_str(), SW_HIDE);
}

void AdminWidget::addCourse(string loc,int type,Course &course){
    // 初始化location
    string adLoc;
    int number;
    if(type == 0){
        adLoc=aLocate+"compulsory\\";
        number = 1000;
    }
    else{
        adLoc=aLocate+"elective\\";
        number = 2000;
    }
    int counter = 0;
    string str = "";
    fstream ad1((adLoc+"list.txt").c_str());
    fstream ad2((adLoc+"temp.txt").c_str(),ios::trunc|ios::out);
    while(str != "-1"){
        getline(ad1,str);
        ad2 << str << endl;
        if(str!="-1")
            counter++;
    }
    ad1.close();
    ad2.close();

    // 计算出课程代码
    number += counter;
    course.setClassNumber(number);

    // 更改admin中的list
    str = "";
    fstream ad3((adLoc+"list.txt").c_str(),ios::trunc|ios::out);
    fstream ad4((adLoc+"temp.txt").c_str());
    while(str != "-1"){
        getline(ad4,str);
        if(str == "-1"){
            if(type == 0)
                ad3 << number << " " << course.getStudentNumber() << " "
                    << course.getWeek() << " " << course.getClassTime() << " "
                    << course.getCredit() << " " << course.getClassName() << " "
                    << course.getTeacher() << '\n';
            else
                ad3 << number << " " << course.getStop() << " " << course.getStudentNumber() << " "
                    << course.getWeek() << " " << course.getClassTime() << " "
                    << course.getCredit() << " " << course.getClassName() << " "
                    << course.getTeacher() << '\n';
        }
        ad3 << str << endl;
    }
    ad3.close();
    ad4.close();
    WinExec(("cmd /c del "+adLoc+"temp.txt").c_str(), SW_HIDE);

    // 更改teacher中的course.txt
    str = "";
    fstream add1((loc+"course.txt").c_str());
    fstream add2((loc+"temp.txt").c_str(),ios::trunc|ios::out);
    while(str != "-1"){
        getline(add1,str);
        add2 << str << endl;
    }
    add1.close();
    add2.close();
    str = "";
    fstream add3((loc+"course.txt").c_str(),ios::trunc|ios::out);
    fstream add4((loc+"temp.txt").c_str());
    while(str != "-1"){
        getline(add4,str);
        if(str == "-1"){
            if(type == 0)
                add3 << number << " " << course.getStudentNumber() << " "
                    << course.getWeek() << " " << course.getClassTime() << " "
                    << course.getCredit() << " " << course.getClassName() << " "
                    << course.getTeacher() << '\n';
            else
                add3 << number << " " << course.getStudentNumber() << " "
                    << course.getWeek() << " " << course.getClassTime() << " "
                    << course.getCredit() << " " << course.getClassName() << " "
                    << course.getTeacher() << '\n';
        }
        add3 << str << endl;
    }
    add3.close();
    add4.close();
    WinExec(("cmd /c del "+loc+"temp.txt").c_str(), SW_HIDE);
}

void AdminWidget::fresh(){
    switch(tabWidget->currentIndex()){
        case 0:
            initApplyTable(applyTable);
            break;
        case 1:
            initCompulTable(compulTable);
            break;
        case 2:
            initElectTable(electTable);
            break;
    }
}

void AdminWidget::closeEvent(QCloseEvent *event){
    fstream put((aLocate+"apply.txt").c_str(),ios::trunc|ios::out);
    for(unsigned int i=0;i<admin.apply.size();i++){
        put << admin.apply[i].getClassNumber() << " " << admin.apply[i].getStudentNumber() << " "
             << admin.apply[i].getWeek() << " " << admin.apply[i].getClassTime() << " "
             << admin.apply[i].getCredit() << " " << admin.apply[i].getClassName() << " "
             << admin.apply[i].getTeacher() << '\n';
    }
    put << -1;
    put.close();

    fstream setstop((aLocate+"elective//list.txt").c_str(),ios::trunc|ios::out);
    for(unsigned int i=0;i<admin.elect.size();i++){
        setstop << admin.elect[i].getClassNumber() << " " << admin.elect[i].getStop() << " "
                << admin.elect[i].getStudentNumber() << " "
                << admin.elect[i].getWeek() << " " << admin.elect[i].getClassTime() << " "
                << admin.elect[i].getCredit() << " " << admin.elect[i].getClassName() << " "
                << admin.elect[i].getTeacher() << '\n';
    }
    setstop << -1;
    setstop.close();

    event->accept();
}

void AdminWidget::agreeClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = applyTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();

    QTableWidgetItem *item1 = applyTable->item(row,0);
    QTableWidgetItem *item2 = applyTable->item(row,1);
    QTableWidgetItem *item3 = applyTable->item(row,2);
    QString cName = item1->text();
    QString cType = item2->text();
    QString tName = item3->text();

    // location为申请老师所在文件夹位置
    string location;
    for(unsigned int i=0;i<admin.teacher.size();i++){
        if(admin.teacher[i].getName() == tName.toStdString())
            location = admin.teacher[i].getID();
    }
    location = tLocate + location + "\\";

    // 提示是否确定
    QMessageBox msg;
    msg.setWindowTitle("提示");
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setInformativeText("是否继续");
    int rec=-1;

    // 若已含该老师已含同名课程则发出提醒
    if(cType.toStdString()=="必修课"){
        for(unsigned int i=0;i<admin.compul.size();i++){
            if(cName.toStdString()==admin.compul[i].getClassName() &&
               tName.toStdString()==admin.compul[i].getTeacher()){
                string warming= "该老师已成功申请同名课程，上课时间为" +
                        getTimeForClass(admin.compul[i].getWeek(),admin.compul[i].getClassTime());
                QString cWarming = QString::fromStdString(warming);
                msg.setText(cWarming);
                break;
            }
        }
    }
    else{
        for(unsigned int i=0;i<admin.elect.size();i++){
            if(cName.toStdString()==admin.elect[i].getClassName() &&
               tName.toStdString()==admin.elect[i].getTeacher()){
                string warming= "该老师已成功申请同名课程，上课时间为" +
                        getTimeForClass(admin.elect[i].getWeek(),admin.elect[i].getClassTime());
                QString cWarming = QString::fromStdString(warming);
                msg.setText(cWarming);
                break;
            }
        }
    }

    rec = msg.exec();

    if(rec != -1)
        switch(rec){
            case QMessageBox::Yes:
                break;
            case QMessageBox::Cancel:
                return;
        }

   int type;
   if(cType.toStdString()=="必修课")
       type = 0;
   else
       type = 1;

   addCourse(location,type,admin.apply[row]);
   //　int 转 string
   stringstream ss;
   string cNumber;
   ss << admin.apply[row].getClassNumber();
   ss >> cNumber;
   if(type==0){
        admin.compul.push_back(admin.apply[row]);
        // 创建文件
        fstream c1((aLocate+"compulsory\\"+cNumber+".txt").c_str(),
                   ios::app|ios::out);
        c1 << -1;
        c1.close();
   }
   else{
        admin.elect.push_back(admin.apply[row]);
        // 创建文件
        fstream c2((aLocate+"elective\\"+cNumber+".txt").c_str(),
                   ios::app|ios::out);
        c2 << -1;
        c2.close();
   }

   admin.apply.erase(admin.apply.begin()+row);
   delApply(location,row);
   initApplyTable(applyTable);
}

void AdminWidget::disagreeClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = applyTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();

    QTableWidgetItem *item = applyTable->item(row,2);
    QString tName = item->text();

    string location;
    for(unsigned int i=0;i<admin.teacher.size();i++){
        if(admin.teacher[i].getName() == tName.toStdString())
            location = admin.teacher[i].getID();
    }
    location = tLocate + location + "\\";

    QMessageBox msg;
    msg.setWindowTitle("提示");
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setInformativeText("是否继续");
    int rec=-1;
    rec = msg.exec();

    if(rec != -1)
        switch(rec){
            case QMessageBox::Yes:
                break;
            case QMessageBox::Cancel:
                return;
        }

    admin.apply.erase(admin.apply.begin()+row);
    delApply(location,row);
    initApplyTable(applyTable);
}

void AdminWidget::cMessageClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = compulTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();

    CompulMessage cm(this,admin.compul[row]);
    cm.exec();
}

void AdminWidget::eMessageClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = electTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();
    // 获取表格内容
    QTableWidgetItem *item = electTable->item(row,0);
    QString number = item->text();
    bool ok;
    int cNumber = number.toInt(&ok,10);
    ElectMessage em(cNumber,this);
    em.exec();
}

void AdminWidget::stopSelectClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = electTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();

    admin.elect[row].setStop(true);
    initElectTable(electTable);
}

void AdminWidget::changePasswordClicked(){
    ChangePassword cp(0,admin.getID(),admin.getPassword());
    cp.exec();
}
