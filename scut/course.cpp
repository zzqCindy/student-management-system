#include "course.h"
#include <string.h>

Course::Course(int sn,int cn,int w,
        int ct,double c,string cna,string t,bool s)
{
    setStudentNumber(sn);
    setClassNumber(cn);
    setWeek(w);
    setClassTime(ct);
    setCredit(c);
    setClassName(cna);
    setTeacher(t);
    setStop(s);
}

Course::Course(){}

int Course::getStudentNumber(){
    return studentNumber;
}

int Course::getClassNumber(){
    return classNumber;
}

int Course::getWeek(){
    return week;
}

int Course::getClassTime(){
    return classTime;
}

double Course::getCredit(){
    return credit;
}

string Course::getClassName(){
    return className;
}

string Course::getTeacher(){
    return teacher;
}

bool Course::getStop(){
    return stop;
}

void Course::setStudentNumber(int sn){
    studentNumber = sn;
}

void Course::setClassNumber(int cn){
    classNumber = cn;
}

void Course::setWeek(int w){
    week = w;
}

void Course::setClassTime(int ct){
    classTime = ct;
}

void Course::setCredit(double c){
    credit = c;
}

void Course::setClassName(string sn){
    className = sn;
}

void Course::setTeacher(string t){
    teacher = t;
}

void Course::setStop(bool s){
    stop = s;
}
