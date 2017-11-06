#include "widget.h"
#include "ui_widget.h"
#include "changepassword.h"
#include <QTextCodec>
#include <QtGui>
#include <QLayout>
#include "course.h"
#include <sstream>
#include <QDebug>
#include <QDir>
#include <QDebug>
#include <windows.h>

Widget::Widget(Student s, QWidget *parent,int i1,int i2,int i3,int bi) :
    QWidget(parent),
    ui(new Ui::Widget),
    index1(i1),
    index2(i2),
    index3(i3),
    buttonIndex(bi)
{
    tabWidget = new QTabWidget();
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    studentName = "����";
    sex = "����";

    student = s;

    int classNumber = student.getClassNumber();
    string cNumber;
    stringstream s1;
    stringstream s2;
    s1 << classNumber;
    s1 >> cNumber;
    int sTime = student.getTime();
    string stuTime;
    s2 << sTime;
    s2 >> stuTime;

    locate = "E:\\Qt\\scutStatistic\\student\\" + student.getMajorNumber()
            + "\\" + stuTime + "\\" + cNumber + "\\";
    string stuNumber = student.getID();
    string loc = locate + "compulsory.txt";
    string passedLoc = locate + "passed.txt";
    locate += stuNumber;

    // ��ʼ���������Ա�
    QFileInfo file((locate+"\\information.txt").c_str());
    bool exist = file.isFile();
    if(exist){
        fstream inputFile((locate+"\\information.txt").c_str());
        string n,s;
        inputFile >> n >> s;
        studentName = n;
        sex = s;
        inputFile.close();
    }

    // ���û�ӭ��
    string str="��ӭ�㣬";
    if(studentName != "����")
        str += studentName;
    str += "ͬѧ";
    welcomeLabel = new QLabel(QString::fromStdString(str));
    changePassword = new QPushButton;
    changePassword->setText(" �޸����� ");
    connect(changePassword,SIGNAL(clicked()),this,SLOT(changePasswordClicked()));

    // ���༶����Ŀ¼�±��޿�ͬ������ѧ����compul�ļ���
    fstream pubCompul(loc.c_str());
    fstream stuCompul((locate + "\\compul.txt").c_str(),ios::trunc|ios::out);
    string line = "";
    while(line != "-1"){
        getline(pubCompul,line);
        stuCompul << line << endl;
    }
    pubCompul.close();
    stuCompul.close();

    fstream inputCom((locate + "\\compul.txt").c_str());
    while(!inputCom.eof()){
        int sn,cn,w,ct,r;
        double c,g;
        string cna,t,cy,cte;
        inputCom >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        inputCom >> sn >> w >> ct >> c >> cna >> t >> cy >> cte >> g >> r;
        Course temp1(sn,cn,w,ct,c,cna,t);
        Compulsory temp2(temp1,cy,cte,g,r);
        student.compul.push_back(temp2);
    }
    inputCom.close();

    fstream PassedCompul(passedLoc.c_str());
    while(!PassedCompul.eof()){
        int sn,cn,w,ct,r;
        double c,g;
        string cna,t,cy,cte;
        PassedCompul >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        PassedCompul >> sn >> w >> ct >> c >> cna >> t >> cy >> cte >> g >> r;
        Course temp1(sn,cn,w,ct,c,cna,t);
        Compulsory temp2(temp1,cy,cte,g,r);
        student.compul.push_back(temp2);
    }
    PassedCompul.close();

    fstream inputEle((locate + "\\elect.txt").c_str());
    while(!inputEle.eof()){
        int sn,cn,w,ct,r;
        double c,g;
        string cna,t,cy,cte;
        inputEle >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        inputEle >> sn >> w >> ct >> c >> cna >> t >> cy >> cte >> g >> r;
        Course temp1(sn,cn,w,ct,c,cna,t);
        Elective temp2(temp1,cy,cte,false,g,r);
        student.elect.push_back(temp2);
    }
    inputEle.close();

    fstream PassedEle((locate+"\\pass.txt").c_str());
    while(!PassedEle.eof()){
        int sn,cn,w,ct,r;
        double c,g;
        string cna,t,cy,cte;
        PassedEle >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        PassedEle >> sn >> w >> ct >> c >> cna >> t >> cy >> cte >> g >> r;
        Course temp1(sn,cn,w,ct,c,cna,t);
        Elective temp2(temp1,cy,cte,false,g,r);
        student.elect.push_back(temp2);
    }
    PassedEle.close();

    fstream inputCho((locate + "\\choosed.txt").c_str());
    while(!inputCho.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        inputCho >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        inputCho >> sn >> w >> ct >> c >> cna >> t;
        Course temp1(sn,cn,w,ct,c,cna,t);
        Elective temp2(temp1);
        student.choosed.push_back(temp2);
    }
    inputCho.close();



    // ��adminĿ¼�¿�ѡѡ��ͬ������ѧ����select�ļ���
    fstream aElect("E:\\Qt\\scutStatistic\\admin\\elective\\list.txt");
    fstream sSelect((locate + "\\select.txt").c_str(),ios::out|ios::trunc);
    while(!aElect.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        bool s;
        aElect >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        aElect >> s >> sn >> w >> ct >> c >> cna >> t;
        if(!s){
            for(unsigned int i=0;i<student.choosed.size();i++){
                if(cn == student.choosed[i].getClassNumber())
                    s = true;
                else
                    s = false;
            }
            sSelect << cn << " " << s << " " << sn << " " << w << " " << ct << " "
                    << c << " " << cna << " "  << t << '\n';
        }
    }
    sSelect << -1;
    sSelect.close();
    aElect.close();

    fstream inputSel((locate + "\\select.txt").c_str());
    while(!inputSel.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        bool s;
        inputSel >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        inputSel >> s >> sn >> w >> ct >> c >> cna >> t;
        Course temp1(sn,cn,w,ct,c,cna,t);
        Elective temp2(temp1,"2015","1",s);
        student.select.push_back(temp2);
    }
    inputSel.close();

    // ��choose��select�����Ŀγ̣��������elect
    for(unsigned int i=0;i<student.choosed.size();i++){
        int cNumber = student.choosed[i].getClassNumber();
        int flag = 0;
        for(unsigned int i=0;i<student.select.size();i++){
            if(cNumber == student.select[i].getClassNumber()){
                flag = 1;
                break;
            }
        }
        if(!flag){
            student.elect.push_back(student.choosed[i]);

            student.choosed.erase(student.choosed.begin()+i); // �˴�����������
            i--;
        }
    }

    // ͬ���ɼ�
    // ѡ�޿�
    string Locate = "E:\\Qt\\scutStatistic\\admin\\elective\\";
    string temp;
    for(unsigned int i=0;i<student.elect.size();i++){
        stringstream ss;
        ss << student.elect[i].getClassNumber();
        ss >> temp;
        temp = Locate + temp + "grade.txt";
        QFileInfo checkGrade(temp.c_str());
        bool exist = checkGrade.isFile();
        if(exist){
            fstream fileTemp(temp.c_str());
            string sNumber = "";
            int rank;
            double grade;
            while(sNumber != "-1"){
                fileTemp >> sNumber >> grade >> rank;
                if(sNumber == student.getID()){
                    student.elect[i].setGrade(grade);
                    student.elect[i].setRank(rank);
                    break;
                }
            }
            fileTemp.close();
        }
    }

    Locate = "E:\\Qt\\scutStatistic\\admin\\compulsory\\";
    for(unsigned int i=0;i<student.compul.size();i++){
        stringstream ss,s1,s2;
        string time,cNumber;
        ss << student.compul[i].getClassNumber();
        ss >> temp;
        s1 << student.getTime();
        s1 >> time;
        s2 << student.getClassNumber();
        s2 >> cNumber;
        temp = Locate + temp + "(" + time + student.getMajorNumber() + cNumber + ")grade.txt";
        QFileInfo checkGrade(temp.c_str());
        bool exist = checkGrade.isFile();
        if(exist){
            fstream fileTemp(temp.c_str());
            string sNumber = "";
            int rank;
            double grade;
            while(sNumber != "-1"){
                fileTemp >> sNumber >> grade >> rank;
                if(sNumber == student.getID()){
                    student.compul[i].setGrade(grade);
                    student.compul[i].setRank(rank);
                    break;
                }
            }
            fileTemp.close();
        }
    }


    //�½���һ��ҳ��Ĳ���
    QWidget *widget = new QWidget();
    initInfWidget(widget);

    //�½��ڶ���ҳ��Ĳ���
    QWidget *chooseWidget = new QWidget();
    choose = new QTableWidget(0,7);
    initTable2(choose);
    initChooseWidget(chooseWidget, choose);

    //�½�������ҳ��Ĳ���
    courseTable = new QTableWidget(5,7);
    initTable3(courseTable);

    //�½����ĸ�ҳ���layout
    QWidget *gradeWidget = new QWidget();
    grade = new QTableWidget(0,9);
    initTable4(grade);
    initWidget(gradeWidget, grade,0);

    //�½������ҳ���layout
    QWidget *chWidget = new QWidget();
    course = new QTableWidget(0,5);
    initTable5(course);
    initWidget(chWidget, course,1);

    //��QTabWidget�����ҳ��
    tabWidget->addTab(widget, "������Ϣ");
    tabWidget->addTab(chooseWidget, "ѧ��ѡ��");
    tabWidget->addTab(courseTable, "���˿α�");
    tabWidget->addTab(gradeWidget, "�ɼ���ѯ");
    tabWidget->addTab(chWidget, "ѡ�����");

    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(tabWidget);
    hLayout->addWidget(welcomeLabel);
    hLayout->addStretch(20);
    hLayout->addWidget(changePassword);
    vLayout->addLayout(hLayout);
    vLayout->addLayout(layout);

    this->setLayout(vLayout);
    this->resize(900, 600);
    this->move(220,80);
    this->setWindowTitle("ѧ��ѡ��ϵͳ");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initInfWidget(QWidget *widget){
    QLabel *name = new QLabel("����");
    QLabel *sex = new QLabel("�Ա�");
    QLabel *majorNumber = new QLabel("רҵ����");
    QLabel *year = new QLabel("��ѧ���");
    QLabel *classNumber = new QLabel("���");
    QLabel *stuNumber = new QLabel("ѧ��");
    QLabel *gpa = new QLabel("GPA");

    QLineEdit *nameEdit = new QLineEdit(QString::fromStdString(studentName));
    nameEdit->setEnabled(false);
    QLineEdit *sexEdit = new QLineEdit(QString::fromStdString(this->sex));
    sexEdit->setEnabled(false);
    QLineEdit *majorNumberEdit = new QLineEdit(QString::fromStdString(student.getMajorNumber()));
    majorNumberEdit->setEnabled(false);
    QLineEdit *yearEdit = new QLineEdit(QString::number(student.getTime()));
    yearEdit->setEnabled(false);
    QLineEdit *classNumberEdit = new QLineEdit(QString::number(student.getClassNumber()));
    classNumberEdit->setEnabled(false);
    QLineEdit *stuNumberEdit = new QLineEdit(QString::fromStdString(student.getID()));
    stuNumberEdit->setEnabled(false);
    QLineEdit *gpaEdit = new QLineEdit(QString::number(student.calGPA()));
    gpaEdit->setEnabled(false);

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QHBoxLayout *hLayout3 = new QHBoxLayout;

    hLayout1->addStretch(10);
    hLayout1->addWidget(name);
    hLayout1->addWidget(nameEdit);
    hLayout1->addStretch(20);
    hLayout1->addWidget(sex);
    hLayout1->addWidget(sexEdit);
    hLayout1->addStretch(20);
    hLayout1->addWidget(majorNumber);
    hLayout1->addWidget(majorNumberEdit);
    hLayout1->addStretch(20);

    hLayout2->addStretch(10);
    hLayout2->addWidget(year);
    hLayout2->addWidget(yearEdit);
    hLayout2->addStretch(20);
    hLayout2->addWidget(classNumber);
    hLayout2->addWidget(classNumberEdit);
    hLayout2->addStretch(20);
    hLayout2->addWidget(stuNumber);
    hLayout2->addWidget(stuNumberEdit);
    hLayout2->addStretch(20);

    hLayout3->stretch(10);
    hLayout3->addWidget(gpa);
    hLayout3->addWidget(gpaEdit);
    hLayout3->stretch(60);

    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    widget->setLayout(vLayout);
}

void Widget::bClicked1(){
    index1 = combo1[0]->currentIndex();
    index2 = combo2[0]->currentIndex();
    index3 = combo3[0]->currentIndex();

    switch(index1){
        case 0:
            yClass = "2015";
            break;
        case 1:
            yClass = "2014";
            break;
        case 2:
            yClass = "2013";
            break;
        case 3:
            yClass = "2012";
            break;
    }

    switch(index2){
        case 0:
            tClass = "1";
            break;
        case 1:
            tClass = "2";
            break;
    }

    int cIndex = tabWidget->currentIndex();
    switch(cIndex){
        case 1:
            initTable2(choose);
            break;
        case 2:
            initTable3(courseTable);
            break;
        case 3:
            initTable4(grade);
            break;
        case 4:
            initTable5(course);
            break;
    }
}

void Widget::bClicked2(){
    index1 = combo1[1]->currentIndex();
    index2 = combo2[1]->currentIndex();
    index3 = combo3[1]->currentIndex();

    switch(index1){
        case 0:
            yClass = "2015";
            break;
        case 1:
            yClass = "2014";
            break;
        case 2:
            yClass = "2013";
            break;
        case 3:
            yClass = "2012";
            break;
    }

    switch(index2){
        case 0:
            tClass = "1";
            break;
        case 1:
            tClass = "2";
            break;
    }

    int cIndex = tabWidget->currentIndex();
    switch(cIndex){
        case 1:
            initTable2(choose);
            break;
        case 2:
            initTable3(courseTable);
            break;
        case 3:
            initTable4(grade);
            break;
        case 4:
            initTable5(course);
            break;
    }
}

void Widget::b1Clicked(){
    buttonIndex = 0;
    initTable2(choose);
}

void Widget::b2Clicked(){
    buttonIndex = 1;
    initTable2(choose);
}

void Widget::availableClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = choose->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();
    unsigned int i;
    QTableWidgetItem *item = choose->item(row,0);
    QString number = item->text();
    bool ok;
    int cNumber = number.toInt(&ok,10);
    for(i=0;i<student.select.size();i++){
        if(student.select[i].getClassNumber()==cNumber)
            break;
    }

    string str = "";
    stringstream ss;
    ss << cNumber;
    ss >>str;

    string location = "E:\\Qt\\scutStatistic\\admin\\elective\\";

    // ���ʱ���Ƿ��ͻ
    int week,classTime;
    fstream repeat((location+"list.txt").c_str());
    while(!repeat.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        bool s;
        repeat >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn==-1)
            break;
        repeat >> s >> sn >> w >> ct >> c >> cna >> t;
        if(cn == cNumber){
            week = w;
            classTime = ct;
        }
    }
    repeat.close();
    // ���޿�
    for(unsigned int i=0;i<student.compul.size();i++){
        if(week == student.compul[i].getWeek() && classTime == student.compul[i].getClassTime()){
            QMessageBox::warning(this,"Warning","�Ͽ�ʱ���ͻ",QMessageBox::Yes);
            return;
        }
    }
    // ѡ�޿�
    for(unsigned int i=0;i<student.elect.size();i++){
        if(week == student.elect[i].getWeek() && classTime == student.elect[i].getClassTime()){
            QMessageBox::warning(this,"Warning","�Ͽ�ʱ���ͻ",QMessageBox::Yes);
            return;
        }
    }

    location += str;
    str = "";

    // ������ѡ����
    int count = 0;
    fstream add1((location+".txt").c_str());
    fstream add2((location+"temp.txt").c_str(),ios::trunc|ios::out);
    while(str != "-1"){
        getline(add1,str);
        add2 << str << endl;
        if(str != "-1")
            count++;
    }
    add1.close();
    add2.close();
    str = "";

    // ����Ƿ񳬹�����
    int flag = 0;
    fstream check("E:\\Qt\\scutStatistic\\admin\\elective\\list.txt");
    while(!check.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        bool s;
        check >> cn ;
        // ����һ�����ݣ��γ̴��룩����-1ʱ���ļ������β
        if(cn == -1)
            break;
        check >> s >> sn >> w >> ct >> c >> cna >> t;

        if(cn == cNumber) // �Ƿ�ÿγ�
            if(count == sn) // �Ƿ�����
                flag =1;
    }
    check.close();

    if(flag){
        QMessageBox::warning(this,tr("Warning"),tr("the course is full"),QMessageBox::Yes);
    }
    else{
        fstream add3((location+".txt").c_str(),ios::trunc|ios::out);
        fstream add4((location+"temp.txt").c_str());
        while(str != "-1"){
            getline(add4,str);
            if(str == "-1")
                add3 << student.getID() << '\n';
            add3 << str << endl;
        }
        add3.close();
        add4.close();

        student.select[i].setSelected(true);
        student.choosed.push_back(student.select[i]);
        initTable2(choose);
    }
    WinExec(("cmd /c del "+location+"temp.txt").c_str(), SW_HIDE);

}

void Widget::cancelClicked(){
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
        return;
    QModelIndex index = choose->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    int row = index.row();
    unsigned int i;
    QTableWidgetItem *item = choose->item(row,0);
    QString number = item->text();
    bool ok;
    int cNumber = number.toInt(&ok,10);
    for(i=0;i<student.select.size();i++){
        if(student.select[i].getClassNumber()==cNumber)
            break;
    }
    student.select[i].setSelected(false);
    for(i=0;i<student.choosed.size();i++){
        if(student.choosed[i].getClassNumber()==cNumber)
            break;
    }
    student.choosed.erase(student.choosed.begin()+i);
    initTable2(choose);

    string str = "";
    stringstream ss;
    ss << cNumber;
    ss >>str;

    string location = "E:\\Qt\\scutStatistic\\admin\\elective\\" + str;
    str = "";
    unsigned int count = 0;
    fstream del1((location+".txt").c_str());
    fstream del2((location+"temp.txt").c_str(),ios::trunc|ios::out);
    while(str != "-1"){
        getline(del1,str);
        if(count != i)
            del2 << str << endl;
        count++;
    }
    del1.close();
    del2.close();
    str = "";
    fstream del3((location+".txt").c_str(),ios::trunc|ios::out);
    fstream del4((location+"temp.txt").c_str());
    while(str != "-1"){
        getline(del4,str);
        del3 << str << endl;
    }
    del3.close();
    del4.close();
    WinExec(("cmd /c del "+location+"temp.txt").c_str(), SW_HIDE);
}

void Widget::initWidget(QWidget *gradeWidget, QTableWidget *grade,int index){

    QLabel *label1 = new QLabel("ѧ��");
    combo1[index] = new QComboBox();
    QLabel *label2 = new QLabel("ѧ��");
    combo2[index] = new QComboBox();
    QLabel *label3 = new QLabel("�γ�����");
    combo3[index] = new QComboBox();
    button[index] = new QPushButton;
    button[index]->setText("ȷ��");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QVBoxLayout *vLayout1 = new QVBoxLayout;
    if(index == 0)
        connect(button[index],SIGNAL(clicked()),this,SLOT(bClicked1()));
    else
        connect(button[index],SIGNAL(clicked()),this,SLOT(bClicked2()));

    combo1[index]->addItem("2015-2016");
    combo1[index]->addItem("2014-2015");
    combo1[index]->addItem("2013-2014");
    combo1[index]->addItem("2012-2013");
    combo2[index]->addItem("1");
    combo2[index]->addItem("2");
    combo3[index]->addItem("ȫ��");
    combo3[index]->addItem("����");
    combo3[index]->addItem("ѡ��");

    hLayout1->addWidget(label1);
    hLayout1->addWidget(combo1[index]);
    hLayout1->addStretch();
    hLayout1->addWidget(label2);
    hLayout1->addWidget(combo2[index]);
    hLayout1->addStretch();
    hLayout1->addWidget(label3);
    hLayout1->addWidget(combo3[index]);
    hLayout1->addStretch();
    hLayout1->addWidget(button[index]);

    vLayout1->addLayout(hLayout1);
    vLayout1->addWidget(grade);
    gradeWidget->setLayout(vLayout1);
}

void Widget::initChooseWidget(QWidget *widget, QTableWidget *table){
    button1 = new QPushButton;
    button1->setText("  ��ѡ  ");
    button2 = new QPushButton;
    button2->setText("  ��ѡ  ");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QVBoxLayout *vLayout1 = new QVBoxLayout;
    connect(button1,SIGNAL(clicked()),this,SLOT(b1Clicked()));
    connect(button2,SIGNAL(clicked()),this,SLOT(b2Clicked()));

    hLayout1->addStretch(1);
    hLayout1->addWidget(button1);
    hLayout1->addStretch(1);
    hLayout1->addWidget(button2);
    hLayout1->addStretch(1);
    vLayout1->addLayout(hLayout1);
    vLayout1->addWidget(table);
    widget->setLayout(vLayout1);
}

void Widget::initTable2(QTableWidget *table){
    //���ñ���б���
    QStringList headerLabels;
    headerLabels << "�γ̴���" << "�γ�����" << "��ʦ����" << "�Ͽ�ʱ��" << "ѧ��" << "����" << "ѡ��";
    table->setHorizontalHeaderLabels(headerLabels);

    table->verticalHeader()->setVisible(false);   //�����б�ͷ

    //���ñ༭��ʽ
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowCount(0);

    if(buttonIndex == 1){
        int cRow = table->rowCount();
        table->setRowCount(cRow+student.choosed.size());
        for(unsigned int i=0; i<student.choosed.size(); i++){
            QTableWidgetItem *item0 = new QTableWidgetItem;
            QTableWidgetItem *item1 = new QTableWidgetItem;
            QTableWidgetItem *item2 = new QTableWidgetItem;
            QTableWidgetItem *item3 = new QTableWidgetItem;
            QTableWidgetItem *item4 = new QTableWidgetItem;
            QTableWidgetItem *item5 = new QTableWidgetItem;

            int cNumber = student.choosed[i].getClassNumber();
            QString clNumber = QString::number(cNumber,10);
            item0->setText(clNumber);
            table->setItem(cRow+i,0,item0);

            string c = student.choosed[i].getClassName();
            QString cName = QString::fromStdString(c);
            item1->setText(cName);
            table->setItem(cRow+i,1,item1);

            string t = student.choosed[i].getTeacher();
            QString tName = QString::fromStdString(t);
            item2->setText(tName);
            table->setItem(cRow+i,2,item2);

            string timeForClass = "";
            switch(student.choosed[i].getWeek()){
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
            ss<<student.choosed[i].getClassTime();
            ss>>tr;
            timeForClass = timeForClass + tr + "��";
            QString timeFC = QString::fromStdString(timeForClass);
            item3->setText(timeFC);
            table->setItem(cRow+i,3,item3);

            int cre = student.choosed[i].getCredit();
            QString cred = QString::number(cre,10);
            item4->setText(cred);
            table->setItem(cRow+i,4,item4);

            int rest = findNumber(student.choosed[i].getClassNumber(),
                                  student.choosed[i].getStudentNumber());
            QString qRest = QString::number(rest,10);
            item5->setText(qRest);
            table->setItem(cRow+i,5,item5);

            // �±����⣬�����ڴ�й©
            cancel[cRow+i] = new QPushButton;
            cancel[cRow+i]->setText("ȡ��");
            connect(cancel[cRow+i],SIGNAL(clicked()),this,SLOT(cancelClicked()));
            choose->setCellWidget(cRow+i,6,cancel[cRow+i]);
        }
    }
    else{
        int cRow = table->rowCount();
        table->setRowCount(cRow+student.select.size());
        for(unsigned int i=0; i<student.select.size(); i++){
            QTableWidgetItem *item0 = new QTableWidgetItem;
            QTableWidgetItem *item1 = new QTableWidgetItem;
            QTableWidgetItem *item2 = new QTableWidgetItem;
            QTableWidgetItem *item3 = new QTableWidgetItem;
            QTableWidgetItem *item4 = new QTableWidgetItem;
            QTableWidgetItem *item5 = new QTableWidgetItem;
            QTableWidgetItem *item6 = new QTableWidgetItem;

            int cNumber = student.select[i].getClassNumber();
            QString clNumber = QString::number(cNumber,10);
            item0->setText(clNumber);
            table->setItem(cRow+i,0,item0);

            string c = student.select[i].getClassName();
            QString cName = QString::fromStdString(c);
            item1->setText(cName);
            table->setItem(cRow+i,1,item1);

            string t = student.select[i].getTeacher();
            QString tName = QString::fromStdString(t);
            item2->setText(tName);
            table->setItem(cRow+i,2,item2);

            string timeForClass = "";
            switch(student.select[i].getWeek()){
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
            ss<<student.select[i].getClassTime();
            ss>>tr;
            timeForClass = timeForClass + tr + "��";
            QString timeFC = QString::fromStdString(timeForClass);
            item3->setText(timeFC);
            table->setItem(cRow+i,3,item3);

            int cre = student.select[i].getCredit();
            QString cred = QString::number(cre,10);
            item4->setText(cred);
            table->setItem(cRow+i,4,item4);

            int rest = findNumber(student.select[i].getClassNumber(),
                                  student.select[i].getStudentNumber());
            QString qRest = QString::number(rest,10);
            item5->setText(qRest);
            table->setItem(cRow+i,5,item5);

            if(student.select[i].getSelected()){
                QString clicked = QString::fromStdString("��ѡ");
                item6->setText(clicked);
                table->setItem(cRow+i,6,item6);
            }
            else{
                available[cRow+i]= new QPushButton;
                available[cRow+i]->setText("ѡ��");
                connect(available[cRow+i],SIGNAL(clicked()),this,SLOT(availableClicked()));
                table->setCellWidget(cRow+i,6,available[cRow+i]);
            }
        }
    }

}

int Widget::findNumber(int classNumber,int studentNumber){
    string location = "E:\\Qt\\scutStatistic\\admin\\elective\\";

    stringstream ss;
    string cNumber;
    ss << classNumber;
    ss >> cNumber;
    location += cNumber + ".txt";

    fstream calNumber(location.c_str());
    string cal = "";
    int count = 0;
    while(cal != "-1"){
        calNumber >> cal;
        count++;
    }
    calNumber.close();

    return studentNumber + 1 - count;
}

void Widget::initTable3(QTableWidget *table){
    //���ñ���б���
    QStringList headerLabels;
    headerLabels << "����һ" << "���ڶ�" << "������" << "������" << "������" << "������" << "������";
    table->setHorizontalHeaderLabels(headerLabels);

    //���ñ���б���Ķ��뷽ʽ
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    //�����б���
    QStringList rowLabels;
    rowLabels << "8:50~10:25" << "10:40~12:15" << "14:00~15:35" << "15:40~17:15" << "19:00~21:30";
    table->setVerticalHeaderLabels(rowLabels);


    //����ÿһ�еĸ߶�
    for(int i = 0; i < 5; i++)
        table->setRowHeight(i, 80);

    //�Զ��������һ�еĿ��ʹ���ͱ����ұ߽����
    table->horizontalHeader()->setStretchLastSection(true);

    //���ñ���ѡ��ʽ
    table->setSelectionBehavior(QAbstractItemView::SelectItems);

    //���ñ༭��ʽ
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //���ñ�������
    // ���޿�
    for(unsigned int i=0; i<student.compul.size(); i++){

        if(student.compul[i].getClassYear() != "2015" || student.compul[i].getClassTerm() != "1")
            continue;

        QTableWidgetItem *item;
        item = new QTableWidgetItem;

        string c = student.compul[i].getClassName();
        QString cName = QString::fromStdString(c);
        cName = cName + '\n';

        string t = student.compul[i].getTeacher();
        QString tName = QString::fromStdString(t);

        QString txt = QString("%1 %2").arg(cName).arg(tName);
        item->setText(txt);
        table->setItem(student.compul[i].getClassTime()-1, student.compul[i].getWeek()-1, item);
    }
    // ѡ�޿�
    for(unsigned int i=0; i<student.elect.size(); i++){

        if(student.elect[i].getClassYear() != "2015" || student.elect[i].getClassTerm() != "1")
            continue;

        QTableWidgetItem *item;
        item = new QTableWidgetItem;

        string c = student.elect[i].getClassName();
        QString cName = QString::fromStdString(c);
        cName = cName + '\n';

        string t = student.elect[i].getTeacher();
        QString tName = QString::fromStdString(t);

        QString txt = QString("%1 %2").arg(cName).arg(tName);
        item->setText(txt);
        table->setItem(student.elect[i].getClassTime()-1, student.elect[i].getWeek()-1, item);
    }
}

void Widget::initTable4(QTableWidget *table){

    //���ñ���б���
    QStringList headerLabels;
    headerLabels << "ѧ��" << "ѧ��" << "�γ̴���" << "�γ�����" << "�γ�����"
                 << "ѧ��" << "����" << "�ɼ�" << "����";
    table->setHorizontalHeaderLabels(headerLabels);

    table->verticalHeader()->setVisible(false);   //�����б�ͷ

    //���ñ༭��ʽ
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowCount(0);

    //���ñ�������
    if(index3!=2){
        int cRow = table->rowCount();
        table->setRowCount(cRow+student.compul.size());
        for(unsigned int i=0; i<student.compul.size(); i++){
            QTableWidgetItem *item0 = new QTableWidgetItem;
            QTableWidgetItem *item1 = new QTableWidgetItem;
            QTableWidgetItem *item2 = new QTableWidgetItem;
            QTableWidgetItem *item3 = new QTableWidgetItem;
            QTableWidgetItem *item4 = new QTableWidgetItem;
            QTableWidgetItem *item5 = new QTableWidgetItem;
            QTableWidgetItem *item6 = new QTableWidgetItem;
            QTableWidgetItem *item7 = new QTableWidgetItem;
            QTableWidgetItem *item8 = new QTableWidgetItem;

            string year = student.compul[i].getClassYear();
            string term = student.compul[i].getClassTerm();
            double gra = student.compul[i].getGrade();
            int ran = student.compul[i].getRank();
            if(year!=yClass || term!=tClass ||
              gra<0 || ran<0){
                cRow--;
                table->setRowCount(table->rowCount()-1);
                continue;
            }

            QString cYear = QString::fromStdString(year);
            item0->setText(cYear);
            table->setItem(cRow+i,0,item0);

            QString cTerm = QString::fromStdString(term);
            item1->setText(cTerm);
            table->setItem(cRow+i,1,item1);

            int cNumber = student.compul[i].getClassNumber();
            QString clNumber = QString::number(cNumber,10);
            item2->setText(clNumber);
            table->setItem(cRow+i,2,item2);

            string c = student.compul[i].getClassName();
            QString cName = QString::fromStdString(c);
            item3->setText(cName);
            table->setItem(cRow+i,3,item3);

            QString type = QString::fromStdString("���޿�");
            item4->setText(type);
            table->setItem(cRow+i,4,item4);

            int cre = student.compul[i].getCredit();
            QString cred = QString::number(cre,10);
            item5->setText(cred);
            table->setItem(cRow+i,5,item5);

            double GPA = student.compul[i].getGpa();
            QString gpa = QString::number(GPA,'g',10);
            item6->setText(gpa);
            table->setItem(cRow+i,6,item6);

            QString grad = QString::number(gra,'g',10);
            item7->setText(grad);
            table->setItem(cRow+i,7,item7);

            QString ra = QString::number(ran,'g',10);
            item8->setText(ra);
            table->setItem(cRow+i,8,item8);

        }
    }

    if(index3!=1){
        int cRow = table->rowCount();
        table->setRowCount(cRow+student.elect.size());
        for(unsigned int i=0; i<student.elect.size(); i++){
            QTableWidgetItem *item0 = new QTableWidgetItem;
            QTableWidgetItem *item1 = new QTableWidgetItem;
            QTableWidgetItem *item2 = new QTableWidgetItem;
            QTableWidgetItem *item3 = new QTableWidgetItem;
            QTableWidgetItem *item4 = new QTableWidgetItem;
            QTableWidgetItem *item5 = new QTableWidgetItem;
            QTableWidgetItem *item6 = new QTableWidgetItem;
            QTableWidgetItem *item7 = new QTableWidgetItem;
            QTableWidgetItem *item8 = new QTableWidgetItem;

            string year = student.elect[i].getClassYear();
            string term = student.elect[i].getClassTerm();
            double gra = student.elect[i].getGrade();
            int ran = student.elect[i].getRank();
            if(year!=yClass || term!=tClass ||
              gra<0 || ran<0){
                cRow--;
                table->setRowCount(table->rowCount()-1);
                continue;
            }

            QString cYear = QString::fromStdString(year);
            item0->setText(cYear);
            table->setItem(cRow+i,0,item0);

            QString cTerm = QString::fromStdString(term);
            item1->setText(cTerm);
            table->setItem(cRow+i,1,item1);

            int cNumber = student.elect[i].getClassNumber();
            QString clNumber = QString::number(cNumber,10);
            item2->setText(clNumber);
            table->setItem(cRow+i,2,item2);

            string c = student.elect[i].getClassName();
            QString cName = QString::fromStdString(c);
            item3->setText(cName);
            table->setItem(cRow+i,3,item3);

            QString type = QString::fromStdString("ѡ�޿�");
            item4->setText(type);
            table->setItem(cRow+i,4,item4);

            int cre = student.elect[i].getCredit();
            QString cred = QString::number(cre,10);
            item5->setText(cred);
            table->setItem(cRow+i,5,item5);

            double GPA = student.elect[i].getGpa();
            QString gpa = QString::number(GPA,'g',10);
            item6->setText(gpa);
            table->setItem(cRow+i,6,item6);

            QString grad = QString::number(gra,'g',10);
            item7->setText(grad);
            table->setItem(cRow+i,7,item7);

            QString ra = QString::number(ran,'g',10);
            item8->setText(ra);
            table->setItem(cRow+i,8,item8);
        }
    }
}

void Widget::initTable5(QTableWidget *table){

    //���ñ���б���
    QStringList headerLabels;
    headerLabels << "�γ̴���" << "�γ�����" << "�γ�����" << "��ʦ����" << "ѧ��";
    table->setHorizontalHeaderLabels(headerLabels);

    table->verticalHeader()->setVisible(false);   //�����б�ͷ

    //���ñ༭��ʽ
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowCount(0);

    //���ñ�������
    if(index3!=2){
        int cRow = table->rowCount();
        table->setRowCount(cRow+student.compul.size());
        for(unsigned int i=0; i<student.compul.size(); i++){
            QTableWidgetItem *item0 = new QTableWidgetItem;
            QTableWidgetItem *item1 = new QTableWidgetItem;
            QTableWidgetItem *item2 = new QTableWidgetItem;
            QTableWidgetItem *item3 = new QTableWidgetItem;
            QTableWidgetItem *item4 = new QTableWidgetItem;

            string year = student.compul[i].getClassYear();
            string term = student.compul[i].getClassTerm();
            if(year!=yClass || term!=tClass){
                cRow--;
                table->setRowCount(table->rowCount()-1);
                continue;
            }

            int cNumber = student.compul[i].getClassNumber();
            QString clNumber = QString::number(cNumber,10);
            item0->setText(clNumber);
            table->setItem(cRow+i,0,item0);

            string c = student.compul[i].getClassName();
            QString cName = QString::fromStdString(c);
            item1->setText(cName);
            table->setItem(cRow+i,1,item1);

            QString type = QString::fromStdString("���޿�");
            item2->setText(type);
            table->setItem(cRow+i,2,item2);

            string t = student.compul[i].getTeacher();
            QString tName = QString::fromStdString(t);
            item3->setText(tName);
            table->setItem(cRow+i,3,item3);

            int cre = student.compul[i].getCredit();
            QString cred = QString::number(cre,10);
            item4->setText(cred);
            table->setItem(cRow+i,4,item4);
        }
    }

    if(index3!=1){
        int cRow = table->rowCount();
        table->setRowCount(cRow+student.elect.size());
        for(unsigned int i=0; i<student.elect.size(); i++){
            QTableWidgetItem *item0 = new QTableWidgetItem;
            QTableWidgetItem *item1 = new QTableWidgetItem;
            QTableWidgetItem *item2 = new QTableWidgetItem;
            QTableWidgetItem *item3 = new QTableWidgetItem;
            QTableWidgetItem *item4 = new QTableWidgetItem;

            string year = student.elect[i].getClassYear();
            string term = student.elect[i].getClassTerm();
            if(year!=yClass || term!=tClass){
                cRow--;
                table->setRowCount(table->rowCount()-1);
                continue;
            }

            int cNumber = student.elect[i].getClassNumber();
            QString clNumber = QString::number(cNumber,10);
            item0->setText(clNumber);
            table->setItem(cRow+i,0,item0);

            string c = student.elect[i].getClassName();
            QString cName = QString::fromStdString(c);
            item1->setText(cName);
            table->setItem(cRow+i,1,item1);

            QString type = QString::fromStdString("ѡ�޿�");
            item2->setText(type);
            table->setItem(cRow+i,2,item2);

            string t = student.elect[i].getTeacher();
            QString tName = QString::fromStdString(t);
            item3->setText(tName);
            table->setItem(cRow+i,3,item3);

            int cre = student.elect[i].getCredit();
            QString cred = QString::number(cre,10);
            item4->setText(cred);
            table->setItem(cRow+i,4,item4);
        }
    }
}

void Widget::closeEvent(QCloseEvent *event){
    fstream inputSel((locate + "\\select.txt").c_str(),ios::out|ios::trunc);
    for(unsigned int i=0; i<student.select.size(); i++){
        inputSel << student.select[i].getClassNumber() << " "
                  << student.select[i].getSelected() << " "
                 << student.select[i].getStudentNumber() << " "
            << student.select[i].getWeek() << " " << student.select[i].getClassTime() << " "
            << student.select[i].getCredit() << " " << student.select[i].getClassName() << " "
            << student.select[i].getTeacher() << '\n';
    }
    inputSel << -1;
    inputSel.close();

    fstream inputCho((locate + "\\choosed.txt").c_str(),ios::out|ios::trunc);
    for(unsigned int i=0; i<student.choosed.size(); i++){
        inputCho << student.choosed[i].getClassNumber() << " "
                 << student.choosed[i].getStudentNumber() << " "
            << student.choosed[i].getWeek() << " " << student.choosed[i].getClassTime() << " "
            << student.choosed[i].getCredit() << " " << student.choosed[i].getClassName() << " "
            << student.choosed[i].getTeacher() << '\n';
    }
    inputCho << -1;
    inputCho.close();

    fstream inputEle((locate + "\\elect.txt").c_str(),ios::out|ios::trunc);
    for(unsigned int i=0;i<student.elect.size();i++){
        if(student.elect[i].getClassYear() != "2015" || student.elect[i].getClassTerm() != "1")
            continue;
        inputEle << student.elect[i].getClassNumber() << " "
                 << student.elect[i].getStudentNumber() << " "
                 << student.elect[i].getWeek() << " "
                 << student.elect[i].getClassTime() << " "
                 << student.elect[i].getCredit() << " "
                 << student.elect[i].getClassName() << " "
                 << student.elect[i].getTeacher() << " "
                 << student.elect[i].getClassYear() << " "
                 << student.elect[i].getClassTerm() << " "
                 << student.elect[i].getGrade() << " "
                 << student.elect[i].getRank() <<'\n';
    }
    inputEle << -1;
    inputEle.close();

    fstream inputCom((locate + "\\compul.txt").c_str(),ios::out|ios::trunc);
    for(unsigned int i=0;i<student.compul.size();i++){
        if(student.compul[i].getClassYear() != "2015" || student.compul[i].getClassTerm() != "1")
            continue;
        inputCom << student.compul[i].getClassNumber() << " "
                 << student.compul[i].getStudentNumber() << " "
                 << student.compul[i].getWeek() << " "
                 << student.compul[i].getClassTime() << " "
                 << student.compul[i].getCredit() << " "
                 << student.compul[i].getClassName() << " "
                 << student.compul[i].getTeacher() << " "
                 << student.compul[i].getClassYear() << " "
                 << student.compul[i].getClassTerm() << " "
                 << student.compul[i].getGrade() << " "
                 << student.compul[i].getRank() <<'\n';
    }
    inputCom << -1;
    inputCom.close();

    event->accept();
}

void Widget::changePasswordClicked(){
    ChangePassword cp(2,student.getID(),student.getPassword());
    cp.exec();
}
