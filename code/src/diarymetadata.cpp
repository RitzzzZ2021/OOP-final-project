#include "include/diarymetadata.h"


DiaryMetaData::DiaryMetaData() {}

DiaryMetaData::~DiaryMetaData() {}

/**
 * @brief DiaryMetaData::DiaryMetaData带参数构造函数，所有参数都可以为空
 * @param _weather天气信息
 * @param _location位置信息
 * @param _mood心情
 * @param _comment简单评论
 */
DiaryMetaData::DiaryMetaData(const QString& _weather, const QString& _location, const QString& _mood, const QString& _comment):
    weather(_weather), location(_location), mood(_mood), comment(_comment) {}

/**
 * @brief DiaryMetaData::DiaryMetaData拷贝构造函数
 * @param r
 */
DiaryMetaData::DiaryMetaData(const DiaryMetaData& r):
    weather(r.weather), location(r.location), mood(r.mood), comment(r.comment) {}

/**
 * @brief DiaryMetaData::set_all设置全部的metadata,所有参数均可以为空
 * @param _weather天气信息
 * @param _location位置信息
 * @param _mood心情
 * @param _comment简单评论
 */
void DiaryMetaData::set_all(const QString& _weather, const QString& _location, const QString& _mood, const QString& _comment)
{
    weather = _weather;
    location = _location;
    mood = _mood;
    comment = _comment;
}

/**
 * @brief DiaryMetaData::set_weather设置天气信息
 * @param _weather天气信息
 */
void DiaryMetaData::set_weather(const QString& _weather)
{
    weather = _weather;
}

/**
 * @brief DiaryMetaData::get_all获取全部信息
 * @param _weather
 * @param _location
 * @param _mood
 * @param _comment
 */
void DiaryMetaData::get_all(QString& _weather, QString& _location, QString& _mood, QString& _comment) const
{
    _weather = weather;
    _location = location;
    _mood = mood;
    _comment = comment;
}

/**
 * @brief DiaryMetaData::get_weather得到天气信息
 * @return 返回天气信息
 */
QString DiaryMetaData::get_weather() const
{
    return weather;
}

/**
 * @brief DiaryMetaData::set_location设置位置信息
 * @param _location位置信息
 */
void DiaryMetaData::set_location(const QString& _location)
{
    location = _location;
}

/**
 * @brief DiaryMetaData::get_location得到位置信息
 * @return位置信息
 */
QString DiaryMetaData::get_location() const
{
    return location;
}

/**
 * @brief DiaryMetaData::set_mood设置心情信息
 * @param _mood心情信息
 */
void DiaryMetaData::set_mood(const QString& _mood)
{
    mood = _mood;
}

/**
 * @brief DiaryMetaData::get_mood得到心情信息
 * @return心情信息
 */
QString DiaryMetaData::get_mood() const
{
    return mood;
}

/**
 * @brief DiaryMetaData::set_comment设置简单评论
 * @param _comment评论
 */
void DiaryMetaData::set_comment(const QString& _comment)
{
    comment = _comment;
}

/**
 * @brief DiaryMetaData::get_comment得到简单评论
 * @return评论
 */
QString DiaryMetaData::get_comment() const
{
    return comment;
}
