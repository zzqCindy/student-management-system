#include "person.h"
#include <iostream>
#include <QDebug>
using namespace std;

Person::Person()
{
    ID[0]='\0';
    password[0]='\0';
}

char * Person::getID(){
    return ID;
}

char * Person::getPassword(){
    return password;
}

bool Person::checkId(char *id){
    int iLength = strlen(id);
    if(iLength > 8){
        qDebug() << "the length of user name should be less than 8";
        return false;
    }

    for(int i=0; i < iLength; i++){
        if(id[i] < 48 || id[i] > 57){
            qDebug() << "the id contains illegal character";
            return false;
        }
    }
    return true;
}

bool Person::checkPassword(char *pw){
    int pLength = strlen(pw);

    if(pLength > 20){
        qDebug() << "the length of password should be less than 20";
        return false;
    }

    for(int i=0; i < pLength; i++){
        if(pw[i] < 48 || (pw[i]>57 && pw[i] < 65) || pw[i]>90){
            qDebug() << "the password contains illegal character";
            return false;
        }
    }
    return true;
}

void Person::setId(char *id){
    strcpy(ID, id);
}

void Person::setPassword(char *pw){
    strcpy(password, pw);
}

