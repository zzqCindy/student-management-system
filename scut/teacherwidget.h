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
    QPushButton *changePassword;    // �޸�����
    QPushButton *setGrade[100];     // elect���óɼ�
    QPushButton *detail[100];       // �γ̰���ѧ��

    string locate;                  // �ļ����λ��
    QPushButton *add;               // ��ӿγ̰�ť

};

#endif // TEACHERWIDGET_H
