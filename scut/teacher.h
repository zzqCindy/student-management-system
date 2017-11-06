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
    vector<Course> apply;                // ��ʦ������

    vector<Course> save;                 // ����Ա�������пγ�����

    string getName();
    void setName(string);

private:
    string name;
};

#endif // TEACHER_H
