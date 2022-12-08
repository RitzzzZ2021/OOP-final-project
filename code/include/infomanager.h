#ifndef INFOMANAGER_H
#define INFOMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlRecord>
#include "include/querydiary.h"

enum DATABASE_EXCEPTION {EXCEP_CONN_FAILED, EXCEP_CONN_NEXIST, EXCEP_CTABLE_FAILED, EXCEP_EXE_FAILED, EXCEP_P_FAILED};

class InfoManager
{
public:
    InfoManager();
    void create_connectin();
    void close_connection();
    void create_tables();
    friend class QueryManager;
    friend class EditManager;
private:
    void insert_diary(const Diary& d);
    void delete_diary(const QDate& date);
    void update_diary(const Diary& d);
    bool diary_exist(const QDate& date);
    Diary* query_tags(const QList<QString>& tags);
    Diary* query_type(const Paragraph_type& type);
    Diary* query_date(const QString& d);
    QueryDiary* query_time(const QDate& begin_date, const QDate& end_date);
    QueryDiary* query_weather(const QString& weather);
    QueryDiary* query_location(const QString& location);
    QueryDiary* query_mood(const QString& mood);
    QueryDiary* query_all();
    QStringList get_all_tags();
    QSqlDatabase db;
};

#endif // INFOMANAGER_H
