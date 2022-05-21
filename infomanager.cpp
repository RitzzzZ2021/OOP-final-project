#include "infomanager.h"

InfoManager::InfoManager() {}


void InfoManager::create_connectin()
{

}

void InfoManager::close_connection()
{

}

void InfoManager::create_tebles()
{
    QSqlQuery query;
    bool success = query.exec("CREATE TABLE diary(");
}

void InfoManager::insert_diary(const Diary& d)
{

}

void InfoManager::delete_diary(const QDate& date, const QTime& time)
{

}

void InfoManager::update_diary(const Diary& d)
{

}

bool InfoManager::diary_exist(const QDate& date,const QTime& time)
{

}

Diary* InfoManager::query_tags(const QList<QString>& tags)
{

}

Diary* InfoManager::query_type(const Paragraph_type& type)
{

}

QueryDiary* InfoManager::query_time(const QDate& begin_date, const QDate& end_date)
{

}

QueryDiary* InfoManager::query_weather(const QString& weather)
{

}

QueryDiary* InfoManager::query_location(const QString& location)
{

}

QueryDiary* InfoManager::query_mood(const QString& mood)
{

}

QueryDiary* InfoManager::query_all()
{

}
