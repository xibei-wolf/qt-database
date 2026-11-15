#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QStringList>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_listWidget_currentTextChanged(const QString &currentText);

private:
    Ui::Widget *ui;
    QStringList drivers =  QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    bool dbconnected;

    void loadAllTables();
    void loadTableByName(const QString & tablename);

};
#endif // WIDGET_H
