#include <QDebug>
#include "student.h"

Student::Student(char user[8],char pw[20],int t,string mNumber,int cNumber)
{
    setId(user);
    setPassword(pw);
    time = t;
    majorNumber = mNumber;
    classNumber = cNumber;
}

Student::Student(){

}

int Student::getTime(){
    return time;
}

string Student::getMajorNumber(){
    return majorNumber;
}

int Student::getClassNumber(){
    return classNumber;
}

double Student::calGPA(){
    double credit = 0, gpa = 0;
    for(unsigned int i=0;i<compul.size();i++){
        if(compul[i].getGpa() != 0){
            credit += compul[i].getCredit();
            gpa += compul[i].getCredit() * compul[i].getGpa();
        }
    }
    for(unsigned int i=0;i<elect.size();i++){
        if(elect[i].getGpa() != 0){
            credit += elect[i].getCredit();
            gpa += elect[i].getCredit() * elect[i].getGpa();
        }
    }
    double ans;
    if(credit == 0)
        return 0.0;
    else{
        ans = gpa / credit;
    }
    ans=( (double)( (int)( (ans+0.005)*100 ) ) )/100;
    return ans;
}
