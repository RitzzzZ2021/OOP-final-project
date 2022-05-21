#ifndef INFOMANAGER_H
#define INFOMANAGER_H

#include <QDate>
#include <QTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QList>
#include <QString>
#include "diary.h"
#include "paragraph.h"
#include "querymanager.h"
#include "querydiary.h"

class InfoManager
{
public:
    InfoManager();
    void create_connectin();
    void close_connection();
    void create_tebles();
    friend class QueryManager;
    friend class EditManager;
private:
    void insert_diary(const Diary& d);
    void delete_diary(const QDate& date, const QTime& time);
    void update_diary(const Diary& d);
    bool diary_exist(const QDate& date,const QTime& time);
    Diary* query_tags(const QList<QString>& tags);
    Diary* query_type(const Paragraph_type& type);
    QueryDiary* query_time(const QDate& begin_date, const QDate& end_date);
    QueryDiary* query_weather(const QString& weather);
    QueryDiary* query_location(const QString& location);
    QueryDiary* query_mood(const QString& mood);
    QueryDiary* query_all();
    QSqlDatabase db;
};

#endif // INFOMANAGER_H
