#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
using namespace std;

class Course
{
private:
        int studentNumber; // 学生人数
        int classNumber;   // 课程代号
        int week;          // 上课时间 星期
        int classTime;	   // 上课节数
        double credit;	   // 学分
        string className;  // 课程名字
        string teacher;	   // 授课老师
        bool stop;         // 是否停止选课

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
