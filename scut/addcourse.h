#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QDialog>
#include <string>
#include "teacherwidget.h"
using namespace std;

namespace Ui {
    class AddCourse;
}

class AddCourse : public QDialog
{
    Q_OBJECT

public:
    explicit AddCourse(TeacherWidget *parent);
    ~AddCourse();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddCourse *ui;
    TeacherWidget *tWidget;
};

#endif // ADDCOURSE_H
