#include "metadata.h"

MetaData::MetaData() {}

/**
 * @brief MetaData::MetaData初始化创建时间日期的构造函数
 * @param _date创建日期
 * @param _time创建时间
 */
MetaData::MetaData(QDate _date, QTime _time):
    create_date(_date), create_time(_time) {}

/**
 * @brief MetaData::MetaData拷贝构造函数
 * @param r
 */
MetaData::MetaData(const MetaData& r)
{
    r.get_create_date_time(create_date,create_time);
    r.get_edit_date_time(edit_date,edit_time);
    path = r.get_path();
}

MetaData::~MetaData() {}

/**
 * @brief MetaData::get_create_date_time获取创建日期和时间
 * @param _date
 * @param _time
 */
void MetaData::get_create_date_time(QDate& _date, QTime& _time) const
{
    _date = create_date;
    _time = create_time;
}

/**
 * @brief MetaData::get_edit_date_time获取编辑日期和时间
 * @param _date
 * @param _time
 */
void MetaData::get_edit_date_time(QDate& _date, QTime& _time) const
{
    _date = edit_date;
    _time = edit_time;
}

/**
 * @brief MetaData::set_create_date_time设置创建日期和时间
 * @param _date
 * @param _time
 */
void MetaData::set_create_date_time(const QDate& _date,const QTime& _time)
{
    create_date = _date;
    create_time = _time;
}

/**
 * @brief MetaData::set_edit_date_time设置编辑日期和时间
 * @param _date
 * @param _time
 */
void MetaData::set_edit_date_time(const QDate& _date,const QTime& _time)
{
    edit_date = _date;
    edit_time = _time;
}

/**
 * @brief MetaData::get_path获取文件存储路径
 * @return
 */
QString MetaData::get_path() const
{
    return path;
}

/**
 * @brief MetaData::set_path设置文件存储路径
 * @param _path
 */
void MetaData::set_path(const QString& _path)
{
    path = _path;
}
