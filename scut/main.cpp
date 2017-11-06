#pragma SW_HIDE
#include <QtGui/QApplication>
#include "widget.h"
#include "teacherwidget.h"
#include "adminwidget.h"
#include "login.h"
#include "compulsory.h"
#include "elective.h"
#include <QTextCodec>
#include <sstream>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 此处应有测试数据的初始化
    QDir *initialize = new QDir;
    bool exist;

    string iniLocation = "E:\\Qt";
    exist = initialize->exists(iniLocation.c_str());
    if(!exist)
        initialize->mkdir(iniLocation.c_str());

    iniLocation += "\\scutStatistic";
    exist = initialize->exists(iniLocation.c_str());
    if(!exist)
        initialize->mkdir(iniLocation.c_str());

    exist = initialize->exists((iniLocation+"\\admin").c_str());
    if(!exist){
        initialize->mkdir((iniLocation+"\\admin").c_str());
        fstream adApply((iniLocation+"\\admin\\apply.txt").c_str(),ios::trunc|ios::out);
        adApply << -1;
        adApply.close();
        // 设置账号密码
        fstream adLogin((iniLocation+"\\admin\\login.txt").c_str(),ios::trunc|ios::out);
        for(int i=0;i<10;i++){
            stringstream ss;
            string number;
            ss << i;
            ss >> number;
            number = "000" + number;
            adLogin << number << " " << number << endl;
        }
        adLogin << -1;
        adLogin.close();
    }

    exist = initialize->exists((iniLocation+"\\student").c_str());
    if(!exist){
        initialize->mkdir((iniLocation+"\\student").c_str());
        fstream createMajor((iniLocation+"\\student\\list.txt").c_str(),ios::trunc|ios::out);
        createMajor << 0 << endl;
        createMajor << -1;
        createMajor.close();
        string locate = iniLocation + "\\student\\0";
        initialize->mkdir(locate.c_str());

        // 设置账号密码
        fstream stuLogin((locate+"\\login.txt").c_str(),ios::trunc|ios::out);

        int sNumber = 20120101;
        for(int k=0;k<3;k++){
            sNumber += 10000;
            int maxNumber1;
            int maxNumber2;
            int maxNumber3;
            int maxNumber4;
            switch(k){
                case 0:
                    maxNumber1 = 21;
                    maxNumber2 = 21;
                    maxNumber3 = 21;
                    maxNumber4 = 23;
                    break;
                case 1:
                    maxNumber1 = 25;
                    maxNumber2 = 24;
                    maxNumber3 = 22;
                    maxNumber4 = 20;
                    break;
                case 2:
                    maxNumber1 = 23;
                    maxNumber2 = 21;
                    maxNumber3 = 21;
                    maxNumber4 = 21;
                    break;
            }
            for(int i=1;i<5;i++){
                switch(i){
                    case 1:
                        for(int j=0;j<maxNumber1;j++)
                            stuLogin << sNumber+j << " " << sNumber+j << " " << 2013+k << " 0 1\n";
                        break;
                    case 2:
                        for(int j=0;j<maxNumber2;j++)
                            stuLogin << sNumber+j+100 << " " << sNumber+j+100 << " " << 2013+k << " 0 2\n";
                        break;
                    case 3:
                        for(int j=0;j<maxNumber3;j++)
                            stuLogin << sNumber+j+200 << " " << sNumber+j+200 << " " << 2013+k << " 0 3\n";
                        break;
                    case 4:
                        for(int j=0;j<maxNumber4;j++)
                            stuLogin << sNumber+j+300 << " " << sNumber+j+300 << " " << 2013+k << " 0 4\n";
                        break;
                }
            }
        }
        stuLogin << -1;
        stuLogin.close();
    }

    exist = initialize->exists((iniLocation+"\\teacher").c_str());
    if(!exist){
        initialize->mkdir((iniLocation+"\\teacher").c_str());

        fstream teLogin((iniLocation+"\\teacher\\login.txt").c_str(),ios::trunc|ios::out);
        teLogin << "3001 3001 张三\n";
        teLogin << "3002 3002 李四\n";
        teLogin << "3003 3003 王五\n";
        teLogin << -1;
        teLogin.close();
    }

    // 加载QSS样式
    QString qss;
    QFile qssFile("E:\\Qt\\scutStatistic\\style1.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()){
      qss = QLatin1String(qssFile.readAll());
      qApp->setStyleSheet(qss);
      qssFile.close();
    }

    Login lg;
    if(lg.exec() == QDialog::Accepted){
        switch(lg.getIndex()){
            case 0:{
                AdminWidget wa(lg.findAdmin(lg.getUn()));
                wa.show();
                return a.exec();
            }
            case 1:{
                TeacherWidget wt(lg.findTeacher(lg.getUn()));
                wt.show();
                return a.exec();
            }
            case 2:{
                Widget ws(lg.findStudent(lg.getUn()));
                ws.show();
                return a.exec();
            }
        }
    }
    return 0;
}
