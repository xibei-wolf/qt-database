#include "widget.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlError>
#include <QSqlQuery>

bool sqlExecute(QSqlQuery & q,const QString &sql){
    if(q.exec(sql)){
        qDebug()<<"sql ok";
        return true;
    }else{
        qDebug()<<"sql err : "<<q.lastError();
        return false;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

#if 0
int main(int argc, char *argv[]){
    QCoreApplication a(argc,argv);

    QStringList drivers =  QSqlDatabase::drivers();
    qDebug()<<drivers;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.65");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("111111");
    db.setDatabaseName("qt1");

    // db.setHostName("192.168.1.12");
    // db.setPort(3306);
    // db.setUserName("disen");
    // db.setPassword("disen");
    // db.setDatabaseName("t1");

    if(db.open()){
        qDebug()<<"connect mysql ok";
    }else{
        qDebug()<<"connect mysql error: "<<db.lastError();
        return -1;
    }

    QSqlQuery query(db);

    QString sql1 =R"(
create table if not exists user(
        id int primary key auto_increment,
        name varchar(50) unique,
        pwd varchar(32),
        st int comment '0 unlock,1 lock'
))";

    QString sql2 =R"(
    insert into user(name,pwd,st) values
    ('小李','111',0),
    ('小王','111',0),
    ('小明','111',0),
    ('小强','111',0)
)";

    QString sql3 = "delete from user where id =4";

    //if(!sqlExecute(query,sql2)) return -1;

    // if(sqlExecute(query,"select * from user")){
    //     while (query.next()) {
    //         QString uid = query.value("id").toString();
    //         QString uname = query.value("name").toString();
    //         QString pwd = query.value("pwd").toString();
    //         int status = query.value("st").toInt();

    //         QString res = "%1 %2 %3 %4 ";
    //         qDebug()<<res.arg(uid).arg(uname).arg(pwd).arg(status);
    //     }

    // }else{
    //     qDebug()<<"select failed";
    // }


    if(sqlExecute(query,"show tables")){
        while (query.next()) {
            QString res = query.value(0).toString();
            qDebug()<<res;
        }
    }else{
        qDebug()<<"select failed";
    }


    //sqlExecute(query,sql3);//删除


    db.close();

    return 0;
}

#endif



