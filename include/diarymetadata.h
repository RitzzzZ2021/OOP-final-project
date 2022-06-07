#ifndef DIARYMETADATA_H
#define DIARYMETADATA_H

#include <QString>

/**
 * @brief The DiaryMetaData class存储diary类的metadata,包括天气、位置、心情和评论。
 */
class DiaryMetaData
{
public:
    DiaryMetaData();
    DiaryMetaData(const QString& _weather, const QString& _location, const QString& _mood, const QString& _comment);
    DiaryMetaData(const DiaryMetaData& r);
    virtual ~DiaryMetaData();
    void set_all(const QString& _weather, const QString& _location, const QString& _mood, const QString& _comment);
    void get_all(QString& _weather, QString& _location, QString& _mood, QString& _comment) const;
    void set_weather(const QString& _weather);
    QString get_weather() const;
    void set_location(const QString& _location);
    QString get_location() const;
    void set_mood(const QString& _mood);
    QString get_mood() const;
    void set_comment(const QString& _comment);
    QString get_comment() const;
private:
    QString weather;//天气
    QString location;//位置
    QString mood;//心情
    QString comment;//评论
};

#endif // DIARYMETADATA_H
