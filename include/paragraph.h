#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include "include/metadata.h"
#include <QString>
#include <QList>

enum Paragraph_type {RICHTEXT, VIDEO};
enum PARAGRAPH_LENGTH_EXCEPTION {EXCEP_TAGS_LEN, EXCEP_PATH_LEN};


class Paragraph
{
public:
    Paragraph();
    Paragraph(QDate _belong_diary);
    Paragraph(QDate _belong_diary, int _para_id);
    Paragraph(QDate _date, QTime _time);
    Paragraph(QDate _belong_diary, int _para_id, QDate _date, QTime _time);
    Paragraph(const Paragraph& r);
    virtual ~Paragraph();
    void set_metadata(const QDate& _cdate, const QTime& _ctime, const QDate& _edate, const QTime& _etime, const QString& _path);
    void get_metadata(QDate& _cdate, QTime& _ctime, QDate& _edate, QTime& _etime, QString& _path) const;
    void set_create_date_time(const QDate& _cdate, const QTime& _ctime);
    void set_edit_date_time(const QDate& _edate, const QTime& _etime);
    void get_create_date_time(QDate& _cdate, QTime& _ctime) const;
    void get_edit_date_time(QDate& _edate, QTime& _etime) const;
    void set_path(const QString& _path);
    QString get_path() const;
    QDate get_diary_belong() const;
    int get_para_id() const;
    void set_para_id(const int& id);
    void set_diary_belong_id(const QDate& _belong, const int& _id = 0);
    void get_diary_belong_id(QDate& _belong, int& _id) const;
    void add_tags(const QString& new_tag);
    void remove_tags(const QString& remove_tag);
    const QList<QString>& get_tags() const;
    void set_type(Paragraph_type _type);
    Paragraph_type get_type() const;
    void set_is_comment(bool _c);
    bool get_is_comment() const;
private:
    MetaData meta_data;//段落的元数据
    QDate belong_diary;//段落属于哪篇日记
    int para_id;//标记段落位于日记的第几段
    QList<QString> tags;//存储tags的list
    Paragraph_type type;//标记段落类型
    bool is_comment;//标记是否是评论段
};

#endif // PARAGRAPH_H
