#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
using namespace std;

class Course
{
private:
        int studentNumber; // ѧ������
        int classNumber;   // �γ̴���
        int week;          // �Ͽ�ʱ�� ����
        int classTime;	   // �Ͽν���
        double credit;	   // ѧ��
        string className;  // �γ�����
        string teacher;	   // �ڿ���ʦ
        bool stop;         // �Ƿ�ֹͣѡ��

public:
    Course(int studentNumber,int classNumber,int week,
           int classTime,double credit,string className,string teacher,bool stop=false);
    Course();

    //vector<Student> stu;

    int getStudentNumber();
    int getClassNumber();
    int getWeek();
    int getClassTime();
    double getCredit();
    string getClassName();
    string getTeacher();
    bool getStop();

    void setStudentNumber(int);
    void setClassNumber(int);
    void setWeek(int);
    void setClassTime(int);
    void setCredit(double);
    void setClassName(string);
    void setTeacher(string);
    void setStop(bool);
};

#endif // COURSE_H
