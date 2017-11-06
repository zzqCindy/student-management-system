#ifndef ELECTIVE_H
#define ELECTIVE_H

#include "course.h"

class Elective : public Course
{
private:
    double grade;      // 成绩
    int rank;          // 排名
    double gpa;        // 绩点
    string classYear;  // 学年
    string classTerm;  // 学期
    bool selected;     // 选定

public:
    Elective(Course &course, string cy = "2015", string ct = "1",
             bool s = false, double g = -1, int r = -1);

    double getGrade();
    int getRank();
    string getClassYear();
    string getClassTerm();
    double getGpa();
    bool getSelected();

    void setGrade(double);
    void setRank(int);
    void setClassYear(string);
    void setClassTerm(string);
    void setSelected(bool);
};

#endif // ELECTIVE_H
