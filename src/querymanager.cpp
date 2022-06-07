#include "include/querymanager.h"

QueryManager::QueryManager() {}

/**
 * @brief QueryManager::is_diary_exist查询日记是否存在
 * @param date
 * @param m
 * @return
 */
bool QueryManager::is_diary_exist(const QDate& date, InfoManager m)
{
    return m.diary_exist(date);
}

/**
 * @brief QueryManager::query_tags按照tag查询段落
 * @param tags
 * @param m
 * @return
 */
Diary* QueryManager::query_tags(const QList<QString>& tags, InfoManager m)
{
    return m.query_tags(tags);
}

/**
 * @brief QueryManager::query_type按照段落的类型查询段落
 * @param type
 * @param m
 * @return
 */
Diary* QueryManager::query_type(const Paragraph_type& type, InfoManager m)
{
    return m.query_type(type);
}

/**
 * @brief QueryManager::query_time按照时间查询段落
 * @param begin_date
 * @param end_dat
 * @param m
 * @return
 */
QueryDiary* QueryManager::query_time(const QDate& begin_date, const QDate& end_date, InfoManager m)
{
    return m.query_time(begin_date, end_date);
}

/**
 * @brief QueryManager::query_weather按照天气查询日记
 * @param weather
 * @param m
 * @return
 */
QueryDiary* QueryManager::query_weather(const QString& weather, InfoManager m)
{
    return m.query_weather(weather);
}

/**
 * @brief QueryManager::query_location按照地点查询日记
 * @param location
 * @param m
 * @return
 */
QueryDiary* QueryManager::query_location(const QString& location, InfoManager m)
{
    return m.query_location(location);
}

/**
 * @brief QueryManager::query_mood按照心情查询日记
 * @param mood
 * @param m
 * @return
 */
QueryDiary* QueryManager::query_mood(const QString& mood, InfoManager m)
{
    return m.query_mood(mood);
}

/**
 * @brief QueryManager::query_all查询所有日记
 * @param m
 * @return
 */
QueryDiary* QueryManager::query_all(InfoManager m)
{
    return m.query_all();
}
