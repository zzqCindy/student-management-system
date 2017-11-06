#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <string>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTabWidget>
#include "admin.h"
using namespace std;

class AdminWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdminWidget(Admin a,QWidget *parent = 0);

    void initApplyTable(QTableWidget *);
    void initCompulTable(QTableWidget *);
    void initElectTable(QTableWidget *);

    void delApply(string,int);
    void addCourse(string,int,Course &);

    string getTimeForClass(int,int);

    Admin admin;

signals:

public slots:
    void agreeClicked();
    void disagreeClicked();
    void fresh();
    void cMessageClicked();
    void eMessageClicked();
    void stopSelectClicked();
    void changePasswordClicked();


protected:
    void closeEvent(QCloseEvent *);

private:
    QLabel *welcomeLabel;
    string aLocate;                  // 管理员文件存放位置
    string tLocate;                  // 老师文件存放位置
    string sLocate;                  // 学生文件存放位置

    QTabWidget *tabWidget;
    QPushButton *agree[100];        // 同意设立课程
    QPushButton *disagree[100];     // 反对设立课程
    QPushButton *changePassword;    // 修改密码

    QPushButton *compulMessage[100];// 必修课所含学生
    QPushButton *electMessage[100]; // 选修课所含学生
    QPushButton *stopSelect[100];   // 停止选课

    QTableWidget *applyTable;       // 未批阅课程
    QTableWidget *compulTable;      // 已同意必修课程
    QTableWidget *electTable;       // 已同意选修课程

};

#endif // ADMINWIDGET_H
