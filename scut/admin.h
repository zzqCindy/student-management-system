#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"
#include "course.h"
#include "teacher.h"
#include <vector>
using namespace std;

class Admin:public Person
{
public:
    Admin();
    Admin(char [],char []);

    vector<Course> compul;
    vector<Course> elect;
    vector<Course> apply;                // ��ʦ������

    vector<Teacher> teacher;

};

#endif // ADMIN_H
