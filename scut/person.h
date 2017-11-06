#ifndef PERSON_H
#define PERSON_H


class Person
{
private:
        char ID[10];			// 账号
        char password[20];              // 密码

public:
    Person();
    char * getID();
    char * getPassword();
    bool checkId(char *);               // 检测长度与是否包含非法字符
    bool checkPassword(char *);
    void setId(char *);
    void setPassword(char *);

};

#endif // PERSON_H
