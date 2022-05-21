#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include <QDate>
#include <QTime>
#include <QString>
#include <QList>
#include "infomanager.h"
#include "diary.h"
#include "querydiary.h"
#include "paragraph.h"

class QueryManager
{
public:
    QueryManager();
    bool is_diary_exist(const QDate& date, InfoManager m);
    Diary* query_tags(const QList<QString>& tags, InfoManager m);
    Diary* query_type(const Paragraph_type& type, InfoManager m);
    QueryDiary* query_time(const QDate& begin_date, const QDate& end_dat, InfoManager m);
    QueryDiary* query_weather(const QString& weather, InfoManager m);
    QueryDiary* query_location(const QString& location, InfoManager m);
    QueryDiary* query_mood(const QString& mood, InfoManager m);
    QueryDiary* query_all(InfoManager m);
};

#endif // QUERYMANAGER_H
