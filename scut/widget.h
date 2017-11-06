#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QtGui>
#include "student.h"
#include <fstream>

namespace Ui {
    class Widget;
}
class QTabWidget;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(Student s, QWidget *parent = 0,
                    int i1 = 0,int i2 = 0,int i3 = 0,int bi = 0);
    void initTable2(QTableWidget *);
    void initTable3(QTableWidget *);
    void initTable4(QTableWidget *);
    void initTable5(QTableWidget *);
    void initInfWidget(QWidget *);
    void initWidget(QWidget *, QTableWidget *,int);
    void initChooseWidget(QWidget *, QTableWidget *);

    int findNumber(int classNumber,int studentNumber);
    ~Widget();

    Student student;

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void bClicked1();
    void bClicked2();
    void b1Clicked();
    void b2Clicked();
    void availableClicked();
    void cancelClicked();
    void changePasswordClicked();

private:
    Ui::Widget *ui;
    QTabWidget *tabWidget;
    int index1;                     // 学年combobox1
    int index2;                     // 学期combobox2
    int index3;                     // 课程性质combobox3
    int buttonIndex;                // 是否选择

    QPushButton *button[2];
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *available[100];
    QPushButton *cancel[100];
    QPushButton *changePassword;    // 修改密码
    QLabel *welcomeLabel;

    QComboBox *combo1[2];              // 学年
    QComboBox *combo2[2];              // 学期
    QComboBox *combo3[2];              // 课程性质

    QTableWidget *choose;
    QTableWidget *courseTable;
    QTableWidget *grade;
    QTableWidget *course;

    // 用于combobox的切换方便与数据进行比较
    string yClass;                  // 学年
    string tClass;                  // 学期

    string locate;                  // 文件存放位置
    string adLocate;                // 管理员处选课位置

    string studentName;             // 学生姓名
    string sex;                     // 学生性别
};

#endif // WIDGET_H
