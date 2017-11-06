#include "teacher.h"

Teacher::Teacher(char user[10],char pw[20],string n)
{
    setId(user);
    setPassword(pw);
    setName(n);
}

Teacher::Teacher(){

}

string Teacher::getName(){
    return name;
}

void Teacher::setName(string n){
    name = n;
}
