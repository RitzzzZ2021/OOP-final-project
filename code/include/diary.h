#ifndef DIARY_H
#define DIARY_H

#include "include/paragraph.h"
#include "include/diarymetadata.h"
#include <QList>

enum DIARY_METADATA_LENGTH_EXCPTION { EXCEP_WEATHER, EXCEP_LOCATION, EXCEP_MOOD, EXCEP_COMMENT};
enum DIARY_PARAGRAPH_POS_EXCEPTION { EXCEP_TAR_POS, EXCEP_DES_POS};

class Diary
{
public:
    Diary();
    Diary(const QDate& _date);
    Diary(const QDate& _date, const QString& _weather, const QString& _location, const QString& _mood, const QString& _comment);
    Diary(const Diary& r);
    virtual ~Diary();
    void set_diary_date(const QDate& _date);
    QDate get_diary_date() const;
    void set_diary_metadata(const QString& _weather, const QString& _location, const QString& _mood, const QString& _comment);
    void set_weather(const QString& _weather);
    void set_location(const QString& _location);
    void set_mood(const QString& _mood);
    void set_comment(const QString& _comment);
    QString get_weather() const;
    QString get_location() const;
    QString get_mood() const;
    QString get_comment() const;
    void get_diary_metadate(QString& _weather, QString& _location, QString& _mood, QString& _comment) const;
    void add_paragraphs(int pos, Paragraph *paragraph);
    void remove_paragraphs(int pos);
    void trans_para_pos(int target, int des);
    QList<Paragraph *>& get_paragraphs();
    const QList<Paragraph *>& get_paragraphs() const;
    void append_para(Paragraph* p);
protected:
    QDate diary_date;//一篇日记的日期，一个日期只能有一篇日记
    DiaryMetaData diary_meta_data;//日记的metadata
    QList<Paragraph*> paragraphs;//日记的段落，list的顺序就是段落的顺序，也是显示顺序
};

#endif // DIARY_H
