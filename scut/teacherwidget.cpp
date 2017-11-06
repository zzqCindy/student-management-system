#include "teacherwidget.h"
#include <QLayout>
#include <QTextCodec>
#include <QtGui>
#include <algorithm>
#include <sstream>
#include <windows.h>
#include "addcourse.h"
#include "changepassword.h"
#include "compulmessage.h"
#include "electmessage.h"

TeacherWidget::TeacherWidget(Teacher t,QWidget *parent) :
    QWidget(parent)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    teacher = t;

    // ���û�ӭ��
    string str="��ӭ�㣬";
    string temp = teacher.getName();
    str += temp;
    str += "��ʦ";
    welcomeLabel = new QLabel(QString::fromStdString(str));
    tabWidget = new QTabWidget();
    courseTable = new QTableWidget(0,7);
    applyTable = new QTableWidget(0,5);
    changePassword = new QPushButton;
    changePassword->setText(" �޸����� ");
    connect(changePassword,SIGNAL(clicked()),this,SLOT(changePasswordClicked()));

    // �����ļ�·��
    locate = "E:\\Qt\\scutStatistic\\teacher\\";
    string teaNumber = teacher.getID();
    locate += teaNumber;

    fstream out1((locate + "\\course.txt").c_str(),ios::in|ios::out);
    while(!out1.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        out1 >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        out1 >> sn >> w >> ct >> c >> cna >> t;
        Course temp(sn,cn,w,ct,c,cna,t);
        teacher.course.push_back(temp);
    }
    out1.close();

    fstream out2((locate + "\\apply.txt").c_str(),ios::in|ios::out);
    while(!out2.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        out2 >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        out2 >> sn >> w >> ct >> c >> cna >> t;
        Course temp(sn,cn,w,ct,c,cna,t);
        teacher.apply.push_back(temp);
    }
    out2.close();

    fstream input("E:\\Qt\\scutStatistic\\admin\\apply.txt",ios::in|ios::out);
    while(!input.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        input >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        input >> sn >> w >> ct >> c >> cna >> t;
        Course temp(sn,cn,w,ct,c,cna,t);
        teacher.save.push_back(temp);
    }
    input.close();

    initCourseTable(courseTable);
    initApplyTable(applyTable);

    tabWidget->addTab(courseTable, "���пγ�");
    tabWidget->addTab(applyTable, "�����б�");

    // initWidget
    add = new QPushButton;
    add->setText(" ���ӿγ� ");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QVBoxLayout *vLayout1 = new QVBoxLayout;
    hLayout1->addWidget(welcomeLabel);
    hLayout1->addStretch(20);
    hLayout1->addWidget(changePassword);
    hLayout2->addStretch(1);
    hLayout2->addWidget(add);
    vLayout1->addLayout(hLayout1);
    vLayout1->addLayout(hLayout2);
    vLayout1->addWidget(tabWidget);
    connect(add,SIGNAL(clicked()),this,SLOT(addClicked()));
    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(fresh()));

    this->setLayout(vLayout1);
    this->resize(900, 600);
    this->move(220,80);
    this->setWindowTitle("ѧ��ѡ��ϵͳ");
}

void TeacherWidget::addClicked(){
    AddCourse ac(this);
    ac.exec();
}

string TeacherWidget::getLocate(){
    return locate;
}

void TeacherWidget::initCourseTable(QTableWidget *table){

    //���ñ���б���
    QStringList headerLabels;
    headerLabels << "�γ̴���" << "�γ�����" << "�γ�����" << "ѧ��" << "�γ�ʱ��" << "" << "";
    table->setHorizontalHeaderLabels(headerLabels);

    //table->verticalHeader()->setVisible(false);   //�����б�ͷ

    //���ñ༭��ʽ
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //���ñ�������
    table->setRowCount(teacher.course.size());
    for(unsigned int i=0; i<teacher.course.size(); i++){
        QTableWidgetItem *item0 = new QTableWidgetItem;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QTableWidgetItem *item3 = new QTableWidgetItem;
        QTableWidgetItem *item4 = new QTableWidgetItem;

        int cNumber = teacher.course[i].getClassNumber();
        QString clNumber = QString::number(cNumber,10);
        item0->setText(clNumber);
        table->setItem(i,0,item0);

        string c = teacher.course[i].getClassName();
        QString cName = QString::fromStdString(c);
        item1->setText(cName);
        table->setItem(i,1,item1);

        QString type;
        if(cNumber>1999)
            type = QString::fromStdString("ѡ�޿�");
        else
            type = QString::fromStdString("���޿�");
        item2->setText(type);
        table->setItem(i,2,item2);

        int cre = teacher.course[i].getCredit();
        QString cred = QString::number(cre,10);
        item3->setText(cred);
        table->setItem(i,3,item3);

        int time = teacher.course[i].getClassTime();
        int week = teacher.course[i].getWeek();
        string classTime = getTimeForClass(week,time);
        QString cTime = QString::fromStdString(classTime);
        item4->setText(cTime);
        table->setItem(i,4,item4);

        // ���óɼ�
        setGrade[i] = new QPushButton;
        setGrade[i]->setText("���óɼ�");
        connect(setGrade[i],SIGNAL(clicked()),this,SLOT(gradeClicked()));
        table->setCellWidget(i,5,setGrade[i]);

        // ��ϸ��Ϣ ��ʾ��ѡ��
        // �гɼ�����ʾ�ɼ���������������ʾ���޳ɼ�
        detail[i] = new QPushButton;
        detail[i]->setText("��ϸ��Ϣ");
        connect(detail[i],SIGNAL(clicked()),this,SLOT(detailClicked()));
        table->setCellWidget(i,6,detail[i]);
    }
}

void TeacherWidget::initApplyTable(QTableWidget *table){
    //���ñ���б���
    QStringList headerLabels;
    headerLabels << "�γ̴���" << "�γ�����" << "�γ�����" << "ѧ��" << "�γ�ʱ��";
    table->setHorizontalHeaderLabels(headerLabels);

    //table->verticalHeader()->setVisible(false);   //�����б�ͷ

    //���ñ༭��ʽ
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //���ñ�������
    table->setRowCount(teacher.apply.size());
    for(unsigned int i=0; i<teacher.apply.size(); i++){
        QTableWidgetItem *item0 = new QTableWidgetItem;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        QTableWidgetItem *item3 = new QTableWidgetItem;
        QTableWidgetItem *item4 = new QTableWidgetItem;

        if(teacher.apply[i].getTeacher() != teacher.getName())
            continue;

        int cNumber = teacher.apply[i].getClassNumber();
        QString clNumber = QString::number(cNumber,10);
        item0->setText(clNumber);
        table->setItem(i,0,item0);

        string c = teacher.apply[i].getClassName();
        QString cName = QString::fromStdString(c);
        item1->setText(cName);
        table->setItem(i,1,item1);

        QString type;
        if(cNumber>1999)
            type = QString::fromStdString("ѡ�޿�");
        else
            type = QString::fromStdString("���޿�");
        item2->setText(type);
        table->setItem(i,2,item2);

        int cre = teacher.apply[i].getCredit();
        QString cred = QString::number(cre,10);
        item3->setText(cred);
        table->setItem(i,3,item3);

        int time = teacher.apply[i].getClassTime();
        int week = teacher.apply[i].getWeek();
        string classTime = getTimeForClass(week,time);
        QString cTime = QString::fromStdString(classTime);
        item4->setText(cTime);
        table->setItem(i,4,item4);
    }
}

void TeacherWidget::fresh(){
    switch(tabWidget->currentIndex()){
        case 0:
            initCourseTable(courseTable);
            break;
        case 1:
            initApplyTable(applyTable);
            break;
    }
}

void TeacherWidget::closeEvent(QCloseEvent *event){
    fstream apply1((getLocate() + "\\apply.txt").c_str(),ios::out|ios::trunc);
    for(unsigned int i=0;i<teacher.apply.size();i++){
        apply1 << teacher.apply[i].getClassNumber() << " "
               << teacher.apply[i].getStudentNumber() << " "
               << teacher.apply[i].getWeek() << " "
               << teacher.apply[i].getClassTime() << " "
               << teacher.apply[i].getCredit() << " "
               << teacher.apply[i].getClassName() << " "
               << teacher.apply[i].getTeacher() << '\n';
    }
    apply1 << -1;
    apply1.close();

    fstream apply2("E:\\Qt\\scutStatistic\\admin\\apply.txt",ios::in|ios::out|ios::trunc);
    for(unsigned int i=0;i<teacher.save.size();i++){
        apply2 << teacher.save[i].getClassNumber() << " " << teacher.save[i].getStudentNumber() << " "
               << teacher.save[i].getWeek() << " " << teacher.save[i].getClassTime() << " "
               << teacher.save[i].getCredit() << " " << teacher.save[i].getClassName() << " "
               << teacher.save[i].getTeacher() << '\n';
    }
    apply2 << -1;
    apply2.close();

    event->accept();
}

void TeacherWidget::changePasswordClicked(){
    ChangePassword cp(1,teacher.getID(),teacher.getPassword());
    cp.exec();
}

void TeacherWidget::detailClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = courseTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();
    // ��ȡ�������
    QTableWidgetItem *item0 = courseTable->item(row,0);
    QTableWidgetItem *item1 = courseTable->item(row,2);
    QString number = item0->text();
    QString type = item1->text();
    bool ok;
    int cNumber = number.toInt(&ok,10);
    if(type.toStdString() == "���޿�"){
        CompulMessage cm(cNumber);
        cm.exec();
    }
    else{
        ElectMessage em(cNumber);
        em.exec();
    }
}

void TeacherWidget::gradeClicked(){

    // ����QTableWidget
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = courseTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();

    // ��ȡ�������
    QTableWidgetItem *item = courseTable->item(row,0);
    QString number = item->text();
    string cNumber = number.toStdString();

    string classLocation = "E:\\Qt\\scutStatistic\\admin\\";
    string temp;
    if(temp.assign(cNumber,0,1) == "1"){
        classLocation += "compulsory\\";
        classLocation += cNumber;

        CompulMessage cm(number.toInt(),1);
        cm.exec();
    }
    else{
        // �ж�ѡ���Ƿ�ֹͣ
        string classNumber = "",line;
        int stop;
        fstream checkStop("E:\\Qt\\scutStatistic\\admin\\elective\\list.txt");
        while(classNumber != "-1"){
            checkStop >> classNumber;
            if(classNumber == "-1")
                break;
            checkStop >> stop;
            if(classNumber == cNumber){
                if(stop)
                    break;
                else{
                    QMessageBox::information(this,"��ʾ","�γ̻�δֹͣѡ�Σ��������óɼ�",QMessageBox::Ok);
                    return;
                }
            }
            getline(checkStop,line);
        }
        checkStop.close();

        // ѡȡ�ļ�
        QString filename = QFileDialog::getOpenFileName(
           this,
           "Open Document",
           QDir::currentPath(),
           "Document files (*.doc *.rtf);;All files(*.*)");
        if (!filename.isNull()) { //�û�ѡ�����ļ�
           QMessageBox::information(this, "��ʾ", "�ɹ�����ļ�", QMessageBox::Ok);
        }
        else
            return;

        classLocation += "elective\\" + cNumber + "grade.txt";
        createGradeTxt(filename.toStdString(),classLocation);
    }
}

bool strict_weak_ordering(const pair<double, std::string> a, const pair<double, std::string> b)
{
   return a.first > b.first;
}

void TeacherWidget::createGradeTxt(string fileLoc,string gradeLoc){

    string sNumber = "";
    double grade;
    vector<pair<double, string> > vec;
    fstream readGrade(fileLoc.c_str());
    while(sNumber != "-1"){
        readGrade >> sNumber >> grade;
        if(sNumber != "-1")
            vec.push_back(make_pair<double,string>(grade,sNumber));
    }
    readGrade.close();
    sort(vec.begin(),vec.end(),strict_weak_ordering);

    int i = 1,count = 0;
    fstream grade1(gradeLoc.c_str(),ios::trunc|ios::out);
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

string TeacherWidget::getTimeForClass(int w,int t){
    string timeForClass = "";
    switch(w){
        case 1:
            timeForClass += "����һ ��";
            break;
        case 2:
            timeForClass += "���ڶ� ��";
            break;
        case 3:
            timeForClass += "������ ��";
            break;
        case 4:
            timeForClass += "������ ��";
            break;
        case 5:
            timeForClass += "������ ��";
            break;
        case 6:
            timeForClass += "������ ��";
            break;
        case 7:
            timeForClass += "������ ��";
            break;
    }
    stringstream ss;
    string tr;
    ss<<t;
    ss>>tr;
    timeForClass = timeForClass + tr + "��";
    return timeForClass;
}
