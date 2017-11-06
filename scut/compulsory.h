#ifndef COMPULSORY_H
#define COMPULSORY_H

#include "course.h"
#include <string>
using namespace std;

class Compulsory : public Course
{
private:
    double grade;      // 成绩
    int rank;          // 排名
    double gpa;        // 绩点
    string classYear;  // 学年
    string classTerm;  // 学期

public:
    Compulsory(Course &course, string cy = "", string ct = "", double g = -1, int r = -1);
    double getGrade();
    int getRank();
    string getClassYear();
    string getClassTerm();
    double getGpa();

    void setGrade(double);
    void setRank(int);
    void setClassYear(string);
    void setClassTerm(string);
};

#endif // COMPULSORY_H
