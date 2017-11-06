#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <vector>
#include "compulsory.h"
#include "elective.h"
#include <fstream>
using namespace std;

class Student:public Person
{
private:
    int time;           // 入学时间
    string majorNumber; // 专业代号
    int classNumber;    // 班号
    double GPA;         // 总GPA

public:
    Student(char [],char[],int,string,int);
    Student();
    vector<Compulsory> compul; // 必修课程
    vector<Elective> elect;    // 已选到的选修课程
    vector<Elective> choosed;  // 勾选的选修课程
    vector<Elective> select;   // 可选的选修课程

    int getTime();
    string getMajorNumber();
    int getClassNumber();
    double calGPA();
};

#endif // STUDENT_H
