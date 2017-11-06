#include "elective.h"

Elective::Elective(Course &course, string cy, string ct, bool s, double g, int r)
{
    setStudentNumber(course.getStudentNumber());
    setClassNumber(course.getClassNumber());
    setWeek(course.getWeek());
    setClassTime(course.getClassTime());
    setCredit(course.getCredit());
    setClassName(course.getClassName());
    setTeacher(course.getTeacher());
    setClassYear(cy);
    setClassTerm(ct);
    setGrade(g);
    setRank(r);
    setSelected(s);
}

double Elective::getGrade(){
    return grade;
}

int Elective::getRank(){
    return rank;
}

string Elective::getClassYear(){
    return classYear;
}

string Elective::getClassTerm(){
    return classTerm;
}

double Elective::getGpa(){
    // ËÄ·ÖÖÆgpa
    double temp = grade;
    if(temp>=90)
        return 4.0;
    else if(temp>=86)
        return 3.7;
    else if(temp>=83)
        return 3.3;
    else if(temp>=80)
        return 3.0;
    else if(temp>=76)
        return 2.7;
    else if(temp>=73)
        return 2.3;
    else if(temp>=70)
        return 2.0;
    else if(temp>=66)
        return 1.7;
    else if(temp>=63)
        return 1.3;
    else if(temp>=60)
        return 1.0;
    else
        return 0.0;
}

bool Elective::getSelected(){
    return selected;
}

void Elective::setGrade(double g){
    grade = g;
}

void Elective::setRank(int r){
    rank = r;
}

void Elective::setClassYear(string cy){
    classYear = cy;
}

void Elective::setClassTerm(string ct){
    classTerm = ct;
}

void Elective::setSelected(bool s){
    selected = s;
}
