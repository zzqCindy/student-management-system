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
    studentName = "暂无";
    sex = "暂无";

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

    // 初始化名字与性别
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

    // 设置欢迎语
    string str="欢迎你，";
    if(studentName != "暂无")
        str += studentName;
    str += "同学";
    welcomeLabel = new QLabel(QString::fromStdString(str));
    changePassword = new QPushButton;
    changePassword->setText(" 修改密码 ");
    connect(changePassword,SIGNAL(clicked()),this,SLOT(changePasswordClicked()));

    // 将班级号码目录下必修课同步到该学生的compul文件下
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
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
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
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
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
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
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
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
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
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(cn==-1)
            break;
        inputCho >> sn >> w >> ct >> c >> cna >> t;
        Course temp1(sn,cn,w,ct,c,cna,t);
        Elective temp2(temp1);
        student.choosed.push_back(temp2);
    }
    inputCho.close();



    // 将admin目录下可选选修同步到该学生的select文件下
    fstream aElect("E:\\Qt\\scutStatistic\\admin\\elective\\list.txt");
    fstream sSelect((locate + "\\select.txt").c_str(),ios::out|ios::trunc);
    while(!aElect.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        bool s;
        aElect >> cn ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
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
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(cn==-1)
            break;
        inputSel >> s >> sn >> w >> ct >> c >> cna >> t;
        Course temp1(sn,cn,w,ct,c,cna,t);
        Elective temp2(temp1,"2015","1",s);
        student.select.push_back(temp2);
    }
    inputSel.close();

    // 若choose含select不含的课程，则加入至elect
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

            student.choosed.erase(student.choosed.begin()+i); // 此处可能有问题
            i--;
        }
    }

    // 同步成绩
    // 选修课
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


    //新建第一个页面的部件
    QWidget *widget = new QWidget();
    initInfWidget(widget);

    //新建第二个页面的部件
    QWidget *chooseWidget = new QWidget();
    choose = new QTableWidget(0,7);
    initTable2(choose);
    initChooseWidget(chooseWidget, choose);

    //新建第三个页面的部件
    courseTable = new QTableWidget(5,7);
    initTable3(courseTable);

    //新建第四个页面的layout
    QWidget *gradeWidget = new QWidget();
    grade = new QTableWidget(0,9);
    initTable4(grade);
    initWidget(gradeWidget, grade,0);

    //新建第五个页面的layout
    QWidget *chWidget = new QWidget();
    course = new QTableWidget(0,5);
    initTable5(course);
    initWidget(chWidget, course,1);

    //向QTabWidget中添加页面
    tabWidget->addTab(widget, "个人信息");
    tabWidget->addTab(chooseWidget, "学生选课");
    tabWidget->addTab(courseTable, "个人课表");
    tabWidget->addTab(gradeWidget, "成绩查询");
    tabWidget->addTab(chWidget, "选课情况");

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
    this->setWindowTitle("学生选课系统");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initInfWidget(QWidget *widget){
    QLabel *name = new QLabel("姓名");
    QLabel *sex = new QLabel("性别");
    QLabel *majorNumber = new QLabel("专业代号");
    QLabel *year = new QLabel("入学年份");
    QLabel *classNumber = new QLabel("班别");
    QLabel *stuNumber = new QLabel("学号");
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

    // 检测时间是否冲突
    int week,classTime;
    fstream repeat((location+"list.txt").c_str());
    while(!repeat.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        bool s;
        repeat >> cn ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(cn==-1)
            break;
        repeat >> s >> sn >> w >> ct >> c >> cna >> t;
        if(cn == cNumber){
            week = w;
            classTime = ct;
        }
    }
    repeat.close();
    // 必修课
    for(unsigned int i=0;i<student.compul.size();i++){
        if(week == student.compul[i].getWeek() && classTime == student.compul[i].getClassTime()){
            QMessageBox::warning(this,"Warning","上课时间冲突",QMessageBox::Yes);
            return;
        }
    }
    // 选修课
    for(unsigned int i=0;i<student.elect.size();i++){
        if(week == student.elect[i].getWeek() && classTime == student.elect[i].getClassTime()){
            QMessageBox::warning(this,"Warning","上课时间冲突",QMessageBox::Yes);
            return;
        }
    }

    location += str;
    str = "";

    // 计算已选人数
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

    // 检查是否超过人数
    int flag = 0;
    fstream check("E:\\Qt\\scutStatistic\\admin\\elective\\list.txt");
    while(!check.eof()){
        int sn,cn,w,ct;
        double c;
        string cna,t;
        bool s;
        check >> cn ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(cn == -1)
            break;
        check >> s >> sn >> w >> ct >> c >> cna >> t;

        if(cn == cNumber) // 是否该课程
            if(count == sn) // 是否已满
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

    QLabel *label1 = new QLabel("学年");
    combo1[index] = new QComboBox();
    QLabel *label2 = new QLabel("学期");
    combo2[index] = new QComboBox();
    QLabel *label3 = new QLabel("课程类型");
    combo3[index] = new QComboBox();
    button[index] = new QPushButton;
    button[index]->setText("确定");
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
    combo3[index]->addItem("全部");
    combo3[index]->addItem("必修");
    combo3[index]->addItem("选修");

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
    button1->setText("  可选  ");
    button2 = new QPushButton;
    button2->setText("  已选  ");
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
    //设置表格行标题
    QStringList headerLabels;
    headerLabels << "课程代码" << "课程名称" << "教师姓名" << "上课时间" << "学分" << "容量" << "选择";
    table->setHorizontalHeaderLabels(headerLabels);

    table->verticalHeader()->setVisible(false);   //隐藏列表头

    //设置编辑方式
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
            ss<<student.choosed[i].getClassTime();
            ss>>tr;
            timeForClass = timeForClass + tr + "天";
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

            // 下标问题，容易内存泄漏
            cancel[cRow+i] = new QPushButton;
            cancel[cRow+i]->setText("取消");
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
            ss<<student.select[i].getClassTime();
            ss>>tr;
            timeForClass = timeForClass + tr + "天";
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
                QString clicked = QString::fromStdString("已选");
                item6->setText(clicked);
                table->setItem(cRow+i,6,item6);
            }
            else{
                available[cRow+i]= new QPushButton;
                available[cRow+i]->setText("选择");
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
    //设置表格行标题
    QStringList headerLabels;
    headerLabels << "星期一" << "星期二" << "星期三" << "星期四" << "星期五" << "星期六" << "星期天";
    table->setHorizontalHeaderLabels(headerLabels);

    //设置表格行标题的对齐方式
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    //设置行表题
    QStringList rowLabels;
    rowLabels << "8:50~10:25" << "10:40~12:15" << "14:00~15:35" << "15:40~17:15" << "19:00~21:30";
    table->setVerticalHeaderLabels(rowLabels);


    //设置每一行的高度
    for(int i = 0; i < 5; i++)
        table->setRowHeight(i, 80);

    //自动调整最后一列的宽度使它和表格的右边界对齐
    table->horizontalHeader()->setStretchLastSection(true);

    //设置表格的选择方式
    table->setSelectionBehavior(QAbstractItemView::SelectItems);

    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置表格的内容
    // 必修课
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
    // 选修课
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

    //设置表格行标题
    QStringList headerLabels;
    headerLabels << "学年" << "学期" << "课程代码" << "课程名称" << "课程性质"
                 << "学分" << "绩点" << "成绩" << "排名";
    table->setHorizontalHeaderLabels(headerLabels);

    table->verticalHeader()->setVisible(false);   //隐藏列表头

    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowCount(0);

    //设置表格的内容
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

            QString type = QString::fromStdString("必修课");
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

            QString type = QString::fromStdString("选修课");
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

    //设置表格行标题
    QStringList headerLabels;
    headerLabels << "课程代码" << "课程名称" << "课程性质" << "教师姓名" << "学分";
    table->setHorizontalHeaderLabels(headerLabels);

    table->verticalHeader()->setVisible(false);   //隐藏列表头

    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setRowCount(0);

    //设置表格的内容
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

            QString type = QString::fromStdString("必修课");
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

            QString type = QString::fromStdString("选修课");
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
