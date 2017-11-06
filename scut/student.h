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
    int time;           // ��ѧʱ��
    string majorNumber; // רҵ����
    int classNumber;    // ���
    double GPA;         // ��GPA

public:
    Student(char [],char[],int,string,int);
    Student();
    vector<Compulsory> compul; // ���޿γ�
    vector<Elective> elect;    // ��ѡ����ѡ�޿γ�
    vector<Elective> choosed;  // ��ѡ��ѡ�޿γ�
    vector<Elective> select;   // ��ѡ��ѡ�޿γ�

    int getTime();
    string getMajorNumber();
    int getClassNumber();
    double calGPA();
};

#endif // STUDENT_H
