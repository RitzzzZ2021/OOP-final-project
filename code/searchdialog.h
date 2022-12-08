#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QDate>
#include "include/infomanager.h"
#include "include/editmanager.h"
#include "include/querymanager.h"

using namespace std;

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();
    QString get_key(){return key;}
    QString get_value(){return value;}
    Diary *get_diary(){return diary_;}
signals:
    void search_success();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_abort_clicked();

private:
    Ui::SearchDialog *ui;

    /*查询的键名*/
    QString key;
    /*保存搜索输入*/
    QString value;

    InfoManager *info_manager_;
    QueryManager *query_manager_;

    QList<Diary *> lst;
    Diary *diary_;

    void init_connects();
    void add_into_comboBox(const QList<Diary *> &lst);

};

#endif // SEARCHDIALOG_H
