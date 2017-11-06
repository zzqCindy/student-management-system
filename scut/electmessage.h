#ifndef ELECTMESSAGE_H
#define ELECTMESSAGE_H

#include "adminwidget.h"

#include <QDialog>

namespace Ui {
    class ElectMessage;
}

class ElectMessage : public QDialog
{
    Q_OBJECT

public:
    explicit ElectMessage(int,AdminWidget *parent = 0);
    ~ElectMessage();

    void initialize();
    void initTable(QTableWidget *);
    void initWidget();
    void addWidget(QTableWidget *,int row,string grade,string rank);

public slots:
    void onBackClicked();

private:
    Ui::ElectMessage *ui;
    AdminWidget *aWidget;
    QTableWidget *sTable;
    QPushButton *back;
    int classNumber;
    string location;

    QLabel *curNumber;
};

#endif // ELECTMESSAGE_H
