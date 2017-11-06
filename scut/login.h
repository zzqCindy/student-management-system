#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "admin.h"
#include "student.h"
#include "teacher.h"
#include <vector>
using namespace std;

namespace Ui {
    class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    vector<Admin> adLogin;
    vector<Teacher> teLogin;
    vector<Student> stLogin;
    ~Login();
    int getIndex();
    char * getUn();
    Student findStudent(char []);
    Teacher findTeacher(char []);
    Admin findAdmin(char []);

private slots:
    void on_login_clicked();

    void on_exit_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Login *ui;
    int index;
    char un[10];
    string location;
};

#endif // LOGIN_H
