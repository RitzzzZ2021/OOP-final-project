#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QString>
#include <qplaintextedit.h>
#include <QDate>
#include <QDebug>
#include <QLineEdit>
#include <include/infomanager.h>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = nullptr);
    ~InfoDialog();

    QString get_mood(){return mood;}
    QDate get_date(){return date;}
    QString get_weather(){return weather;}
    QString get_location(){return location;}
    QString get_comment(){return comment;}
    InfoManager *get_infomanager(){return info_manager_;}

signals:
    void widget_closed();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_mood_currentTextChanged(const QString &arg1);

    void on_comboBox_location_currentTextChanged(const QString &arg1);

private:
    Ui::InfoDialog *ui;

    QString mood; //标签
    QString weather; //天气
    QDate date; //日期
    QString location; //地点
    QString comment; //评论

    InfoManager *info_manager_;

    void init_InfoDialog();
    void init_connects();
};

#endif // INFODIALOG_H
