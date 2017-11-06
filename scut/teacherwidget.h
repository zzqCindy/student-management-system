#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include "teacher.h"

class TeacherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TeacherWidget(Teacher t,QWidget *parent = 0);

    Teacher teacher;

    string getLocate();
    void initCourseTable(QTableWidget *);
    void initApplyTable(QTableWidget *);

    void createGradeTxt(string fileLoc,string gradeLoc);
    string getTimeForClass(int w,int t);

    QTableWidget *courseTable;
    QTableWidget *applyTable;

signals:

protected:
    void closeEvent(QCloseEvent *);

public slots:
    void addClicked();
    void fresh();
    void changePasswordClicked();
    void detailClicked();
    void gradeClicked();

private:
    QLabel *welcomeLabel;
    QTabWidget *tabWidget;
    QPushButton *changePassword;    // 修改密码
    QPushButton *setGrade[100];     // elect设置成绩
    QPushButton *detail[100];       // 课程包含学生

    string locate;                  // 文件存放位置
    QPushButton *add;               // 添加课程按钮

};

#endif // TEACHERWIDGET_H
