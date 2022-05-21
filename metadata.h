#ifndef METADATA_H
#define METADATA_H

#include <QString>
#include <QDate>
#include <QTime>

class MetaData
{
public:
    MetaData();
    MetaData(QDate _date, QTime _time);
    MetaData(const MetaData& r);
    virtual ~MetaData();
    void get_create_date_time(QDate& _date, QTime& _time) const;
    void get_edit_date_time(QDate& _date, QTime& _time) const;
    void set_create_date_time(const QDate& _date,const QTime& _time);
    void set_edit_date_time(const QDate& _date,const QTime& _time);
    QString get_path() const;
    void set_path(const QString& _path);
private:
    QDate create_date;//创建日期
    QTime create_time;//创建时间
    QDate edit_date;//编辑日期
    QTime edit_time;//编辑时间
    QString path;//文件存储路径
};

#endif // METADATA_H
