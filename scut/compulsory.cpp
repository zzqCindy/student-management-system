#include "compulsory.h"

Compulsory::Compulsory(Course &course, string cy, string ct, double g, int r)
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
}

double Compulsory::getGrade(){
    return grade;
}

int Compulsory::getRank(){
    return rank;
}

string Compulsory::getClassYear(){
    return classYear;
}

string Compulsory::getClassTerm(){
    return classTerm;
}

double Compulsory::getGpa(){
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

void Compulsory::setGrade(double g){
    grade = g;
}

void Compulsory::setRank(int r){
    rank = r;
}

void Compulsory::setClassYear(string cy){
    classYear = cy;
}

void Compulsory::setClassTerm(string ct){
    classTerm = ct;
}
