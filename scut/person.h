#ifndef PERSON_H
#define PERSON_H


class Person
{
private:
        char ID[10];			// �˺�
        char password[20];              // ����

public:
    Person();
    char * getID();
    char * getPassword();
    bool checkId(char *);               // ��ⳤ�����Ƿ�����Ƿ��ַ�
    bool checkPassword(char *);
    void setId(char *);
    void setPassword(char *);

};

#endif // PERSON_H
