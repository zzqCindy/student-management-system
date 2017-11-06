#ifndef COMPULDETAIL_H
#define COMPULDETAIL_H

#include "compulmessage.h"
#include <QDialog>

namespace Ui {
    class CompulDetail;
}

class CompulDetail : public QDialog
{
    Q_OBJECT

public:
    explicit CompulDetail(int number,int row,CompulMessage *parent = 0);
    ~CompulDetail();

    void initialize();
    void initTable(QTableWidget *);
    void initWidget();
    void addWidget(QTableWidget *,int row,string grade,string rank);

public slots:
    void onBackClicked();

private:
    Ui::CompulDetail *ui;
    CompulMessage *cWidget;
    QTableWidget *sTable;
    QPushButton *back;
    int classNumber;
    string location;
    int row;                // 班级所在compulmessage的行号
};

#endif // COMPULDETAIL_H
