#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("111111");
    db.setDatabaseName("qt1");

    if(db.open()){
        qDebug()<<"connect mysql ok";
        dbconnected = true;
    }else{
        qDebug()<<"connect mysql error: "<<db.lastError();
        dbconnected = false;
    }

    loadAllTables();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadAllTables(){
    QString sql = "show tables";
    if(dbconnected){
        QSqlQuery q(db);

        if(q.exec(sql)){
            while (q.next()) {
                QString tableName = q.value(0).toString();
                ui->listWidget->addItem(tableName);
            }
        }
    }
}
void Widget::loadTableByName(const QString & tablename){
    ui->tableWidget->clear();
    QString sql1 = "desc %1";
    QString sql2 = "select count(1) from %1";
    QStringList fields;
    int rows = 0;

    QSqlQuery q(db);

    if(q.exec(sql1.arg(tablename))){
        while (q.next()) {
            fields.append(q.value(0).toString());
        }
    }

    if(q.exec(sql2.arg(tablename))){
        while (q.next()) {
            rows=q.value(0).toInt();
        }
    }

    if(fields.empty()) return ;

    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(fields.size());

    ui->tableWidget->setHorizontalHeaderLabels(fields);

    QString sqlData = QString("SELECT * FROM %1").arg(tablename);
    if(!q.exec(sqlData)){
        qDebug() << "查询数据失败：" << q.lastError().text();
        return;
    }

    int rowIndex = 0;
    while(q.next()){
        ui->tableWidget->insertRow(rowIndex);
        for(int i=0;i<fields.size();i++){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(q.value(i).toString());
            ui->tableWidget->setItem(rowIndex, i, item);
        }
        rowIndex++;
    }
}

void Widget::on_listWidget_currentTextChanged(const QString &currentText)
{
    loadTableByName(currentText);

}

