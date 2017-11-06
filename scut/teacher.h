#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include "student.h"

class Teacher:public Person
{
public:
    Teacher(char [],char [],string);
    Teacher();
    vector<Course> course;
    vector<Course> apply;                // 老师的申请

    vector<Course> save;                 // 管理员处的所有课程申请

    string getName();
    void setName(string);

private:
    string name;
};

#endif // TEACHER_H
