#ifndef ELECTIVE_H
#define ELECTIVE_H

#include "course.h"

class Elective : public Course
{
private:
    double grade;      // �ɼ�
    int rank;          // ����
    double gpa;        // ����
    string classYear;  // ѧ��
    string classTerm;  // ѧ��
    bool selected;     // ѡ��

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
