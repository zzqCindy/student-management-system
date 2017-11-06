#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>
#include <string>
#include <QDir>
#include <sstream>
#include <QTextCodec>
using namespace std;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->Password->setEchoMode(QLineEdit::Password);
    index = 0;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    location = "E:\\Qt\\scutStatistic\\";
    string locate;

    // student的文件夹创建与vector<student>的初始化
    QDir *createDir = new QDir;
    bool exist;
    string str = "";
    fstream createMajor((location+"student\\list.txt").c_str());
    while(str != "-1"){
        createMajor >> str;
        if(str == "-1")
            break;

        locate = location + "student\\" + str;
        exist = createDir->exists(locate.c_str());
        if(!exist)
            createDir->mkdir(locate.c_str());

        locate += "\\";
        //读取该专业信息
        fstream inputStu((locate+"login.txt").c_str());
        while(!inputStu.eof()){
            char id[10],pw[20];
            int t,cn;
            string mn;
            inputStu >> id ;
            // 当第一个数据（课程代码）读到-1时，文件到达结尾
            if(!strcmp(id,"-1"))
                break;

            inputStu >> pw >> t >> mn >> cn;
            Student student(id,pw,t,mn,cn);
            stLogin.push_back(student);

            locate = location + "student\\" + str + "\\";
            stringstream s1;
            stringstream s2;

            //创建入学年份文件夹
            string sTime;
            s1 << t;
            s1 >> sTime;
            locate = locate + sTime;
            exist = createDir->exists(locate.c_str());
            if(!exist)
                createDir->mkdir(locate.c_str());

            //创建班别文件夹
            string cNumber;
            s2 << cn;
            s2 >> cNumber;
            locate = locate + "\\" + cNumber;
            exist = createDir->exists(locate.c_str());
            if(!exist){
                createDir->mkdir(locate.c_str());
                // 班级必修课
                fstream pubCompul((locate+"\\compulsory.txt").c_str(),ios::trunc|ios::out);
                fstream pubPassed((locate+"\\passed.txt").c_str(),ios::trunc|ios::out);
                pubCompul << -1;
                pubPassed << -1;
                pubCompul.close();
                pubPassed.close();
            }

            //创建个人文件夹
            string user = string(id);
            locate = locate + "\\" + user;
            exist = createDir->exists(locate.c_str());
            if(!exist){
                createDir->mkdir(locate.c_str());
                fstream createCom((locate + "\\compul.txt").c_str(),ios::out|ios::trunc);
                fstream createEle((locate + "\\elect.txt").c_str(),ios::out|ios::trunc);
                fstream createSel((locate + "\\select.txt").c_str(),ios::out|ios::trunc);
                fstream createCho((locate + "\\choosed.txt").c_str(),ios::out|ios::trunc);
                fstream createPas((locate + "\\pass.txt").c_str(),ios::out|ios::trunc);
                createCom << -1;
                createEle << -1;
                createSel << -1;
                createCho << -1;
                createPas << -1;
                createCom.close();
                createEle.close();
                createSel.close();
                createCho.close();
                createPas.close();
            }
        }
        inputStu.close();
    }
    createMajor.close();

    // teacher的文件夹创建与vector<teacher>的初始化
    fstream inputTea((location+"teacher\\login.txt").c_str());
    while(!inputTea.eof()){
        char id[10],pw[20];
        string n;
        inputTea >> id ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(!strcmp(id,"-1"))
            break;
        inputTea >> pw >> n;
        Teacher teacher(id,pw,n);
        teLogin.push_back(teacher);

        string number = string(id);
        locate = location + "teacher\\" + number;

        //文件夹的创建
        exist = createDir->exists(locate.c_str());
        if(!exist){
            createDir->mkdir(locate.c_str());
            fstream tApply((locate+"\\apply.txt").c_str(),ios::out|ios::trunc);
            fstream tCourse((locate+"\\course.txt").c_str(),ios::out|ios::trunc);
            tApply << -1;
            tCourse << -1;
            tApply.close();
            tCourse.close();
        }
    }
    inputTea.close();

    // vector<admin>的初始化
    fstream inputAdm((location+"admin\\login.txt").c_str(),ios::in|ios::out);
    while(!inputAdm.eof()){
        char id[10],pw[20];
        inputAdm >> id ;
        // 当第一个数据（课程代码）读到-1时，文件到达结尾
        if(!strcmp(id,"-1"))
            break;
        inputAdm >> pw;
        Admin admin(id,pw);
        adLogin.push_back(admin);
    }
    inputAdm.close();

    // admin的文件夹创建
    locate = location + "admin\\" + "compulsory";
    exist = createDir->exists(locate.c_str());
    if(!exist){
        createDir->mkdir(locate.c_str());
        fstream aCom((locate+"\\list.txt").c_str(),ios::out|ios::trunc);
        aCom << -1;
        aCom.close();
    }
    locate = location + "admin\\" + "elective";
    exist = createDir->exists(locate.c_str());
    if(!exist){
        createDir->mkdir(locate.c_str());
        fstream aEle((locate+"\\list.txt").c_str(),ios::out|ios::trunc);
        aEle << -1;
        aEle.close();
    }

}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    char *temp1,*temp2;
    QByteArray ba1 = ui->UserName->text().trimmed().toLatin1();
    QByteArray ba2 = ui->Password->text().trimmed().toLatin1();
    temp1=ba1.data();
    temp2=ba2.data();

    // 0为admin，1为teacher，2为student
    switch(index){
        case 0:
            for(unsigned int count=0; count<adLogin.size(); count++){
                char *temp3;
                temp3 = adLogin[count].getID();
                if(!strcmp(temp1, temp3)){
                    temp3 = adLogin[count].getPassword();
                    if(!strcmp(temp2, temp3)){
                        strcpy(un,adLogin[count].getID());
                        accept();
                        return;
                    }
                    else
                        break;
                }
            }
            break;
        case 1:
        for(unsigned int count=0; count<teLogin.size(); count++){
            char *temp3;
            temp3 = teLogin[count].getID();
            if(!strcmp(temp1, temp3)){
                temp3 = teLogin[count].getPassword();
                if(!strcmp(temp2, temp3)){
                    strcpy(un,teLogin[count].getID());
                    accept();
                    return;
                }
                else
                    break;
            }
        }
            break;
        case 2:
        for(unsigned int count=0; count<stLogin.size(); count++){
            char *temp3;
            temp3 = stLogin[count].getID();
            if(!strcmp(temp1, temp3)){
                temp3 = stLogin[count].getPassword();
                if(!strcmp(temp2, temp3)){
                    strcpy(un,stLogin[count].getID());
                    accept();
                    return;
                }
                else
                    break;
            }
        }
            break;
    }

    QMessageBox::warning(this,"Warning","账户名或密码错误!",QMessageBox::Yes);

    ui->UserName->clear();
    ui->Password->clear();//清空输入框
    ui->UserName->setFocus();//将光标转到用户名输入框
}

void Login::on_exit_clicked()
{
    close();
}

void Login::on_comboBox_currentIndexChanged(int index)
{
    this->index = index;
}

int Login::getIndex(){
    return index;
}

char * Login::getUn(){
    return un;
}

Student Login::findStudent(char u[10]){
    for(unsigned int i=0;i<stLogin.size();i++){
        if(!strcmp(stLogin[i].getID(),u))
            return stLogin[i];
    }
}

Teacher Login::findTeacher(char u[10]){
    for(unsigned int i=0;i<teLogin.size();i++){
        if(!strcmp(teLogin[i].getID(),u))
            return teLogin[i];
    }
}

Admin Login::findAdmin(char u[10]){
    for(unsigned int i=0;i<adLogin.size();i++){
        if(!strcmp(adLogin[i].getID(),u))
            return adLogin[i];
    }
}
