#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include <string>
using namespace std;

namespace Ui {
    class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(int index,string un,string pw,QWidget *parent = 0);
    ~ChangePassword();

private slots:
    void on_yes_clicked();

    void on_cancel_clicked();

private:
    Ui::ChangePassword *ui;
    int index;
    string userNumber;      // µÇÂ¼ÕËºÅ
    string userPassword;    // µÇÂ¼ÃÜÂë
};

#endif // CHANGEPASSWORD_H
