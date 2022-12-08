#include "include/paragraph.h"
#include <QDebug>

Paragraph::Paragraph() {}

/**
 * @brief Paragraph::Paragraph初始化属于哪篇日记的构造函数
 * @param _belong_diary
 */
Paragraph::Paragraph(QDate _belong_diary):
    belong_diary(_belong_diary) {}

/**
 * @brief Paragraph::Paragraph初始化属于哪篇日记以及段落位置的构造函数
 * @param _belong_diary
 * @param _para_id
 */
Paragraph::Paragraph(QDate _belong_diary, int _para_id):
    belong_diary(_belong_diary), para_id(_para_id) {}

/**
 * @brief Paragraph::Paragraph初始化创建时间的构造函数
 * @param _date
 * @param _time
 */
Paragraph::Paragraph(QDate _date, QTime _time):
    meta_data(_date, _time) {}

/**
 * @brief Paragraph::Paragraph初始化属于哪篇日记、段落位置以及创建时间的构造函数
 * @param _belong_diary
 * @param _para_id
 * @param _date
 * @param _time
 */
Paragraph::Paragraph(QDate _belong_diary, int _para_id, QDate _date, QTime _time):
    meta_data(_date, _time), belong_diary(_belong_diary), para_id(_para_id) {}

/**
 * @brief Paragraph::Paragraph拷贝构造函数
 * @param r
 */
Paragraph::Paragraph(const Paragraph& r)
{
    QDate cdate, edate;
    QTime ctime, etime;
    QString path;
    r.get_create_date_time(cdate, ctime);
    r.get_edit_date_time(edate, etime);
    path = r.get_path();

    meta_data.set_create_date_time(cdate, ctime);
    meta_data.set_edit_date_time(edate, etime);
    meta_data.set_path(path);

    r.get_diary_belong_id(belong_diary, para_id);

    QList<QString>::const_iterator iter;
    for(iter = r.get_tags().begin(); iter != r.get_tags().end(); iter++)
    {
        tags << *iter;
    }

    type = r.get_type();
    is_comment = r.get_is_comment();
}

Paragraph::~Paragraph() {}

/**
 * @brief Paragraph::set_metadata设置metadata
 * @param _cdate
 * @param _ctime
 * @param _edate
 * @param _etime
 * @param _path
 */
void Paragraph::set_metadata(const QDate& _cdate, const QTime& _ctime, const QDate& _edate, const QTime& _etime, const QString& _path)
{
    if(_path.length() > 50) { throw EXCEP_PATH_LEN; }
    meta_data.set_create_date_time(_cdate, _ctime);
    meta_data.set_edit_date_time(_edate, _etime);
    meta_data.set_path(_path);
}

/**
 * @brief Paragraph::get_metadata获取metadata
 * @param _cdate
 * @param _ctime
 * @param _edate
 * @param _etime
 * @param _path
 */
void Paragraph::get_metadata(QDate& _cdate, QTime& _ctime, QDate& _edate, QTime& _etime, QString& _path) const
{
    meta_data.get_create_date_time(_cdate, _ctime);
    meta_data.get_edit_date_time(_edate, _etime);
    _path = meta_data.get_path();
}

/**
 * @brief Paragraph::set_create_date_time设置创建时间
 * @param _cdate
 * @param _ctime
 */
void Paragraph::set_create_date_time(const QDate& _cdate, const QTime& _ctime)
{
    meta_data.set_create_date_time(_cdate, _ctime);
}

/**
 * @brief Paragraph::set_edit_date_time设置编辑时间
 * @param _edate
 * @param _etime
 */
void Paragraph::set_edit_date_time(const QDate& _edate, const QTime& _etime)
{
    meta_data.set_edit_date_time(_edate, _etime);
}

/**
 * @brief Paragraph::get_create_date_time获取创建时间
 * @param _cdate
 * @param _ctime
 */
void Paragraph::get_create_date_time(QDate& _cdate, QTime& _ctime) const
{
    meta_data.get_create_date_time(_cdate, _ctime);
}

/**
 * @brief Paragraph::get_edit_date_time获取编辑时间
 * @param _edate
 * @param _etime
 */
void Paragraph::get_edit_date_time(QDate& _edate, QTime& _etime) const
{
    meta_data.get_edit_date_time(_edate, _etime);
}

/**
 * @brief Paragraph::set_path设置路径
 * @param _path
 */
void Paragraph::set_path(const QString& _path)
{
    if(_path.length() > 50) { throw EXCEP_PATH_LEN; }
    meta_data.set_path(_path);
}

/**
 * @brief Paragraph::get_path获取路径
 * @return
 */
QString Paragraph::get_path() const
{
    return meta_data.get_path();
}

/**
 * @brief Paragraph::get_diary_belong获取段落归属
 * @return
 */
QDate Paragraph::get_diary_belong() const
{
    return belong_diary;
}

/**
 * @brief Paragraph::get_para_id获取段落位置
 * @return
 */
int Paragraph::get_para_id() const
{
    return para_id;
}

/**
 * @brief Paragraph::set_para_id设置段落位置
 * @param id
 */
void Paragraph::set_para_id(const int& id)
{
    para_id = id;
}

/**
 * @brief Paragraph::set_diary_belong_id设置段落归属以及段落位置
 * @param _belong
 * @param _id
 */
void Paragraph::set_diary_belong_id(const QDate& _belong, const int& _id)
{
    qDebug() << "in paragraph's func. set diary belong id" << endl;
    belong_diary = _belong;
    para_id = _id;
}

/**
 * @brief Paragraph::get_diary_belong_id获取段落归属以及位置
 * @param _belong
 * @param _id
 */
void Paragraph::get_diary_belong_id(QDate& _belong, int& _id) const
{
    _belong = belong_diary;
    _id = para_id;
}

/**
 * @brief Paragraph::add_tags增加标签，如果标签长度大于20会抛出异常
 * @param new_tag
 */
void Paragraph::add_tags(const QString& new_tag)
{
    if(new_tag.length() > 20) { throw EXCEP_TAGS_LEN; }
    if(tags.count(new_tag) == 0) { tags << new_tag; }
}

/**
 * @brief Paragraph::remove_tags移除标签
 * @param remove_tag
 */
void Paragraph::remove_tags(const QString& remove_tag)
{
    tags.removeAll(remove_tag);
}

/**
 * @brief Paragraph::get_tags获取标签，const类型，修改通过add和remove进行
 * @return
 */
const QList<QString>& Paragraph::get_tags() const
{
    return tags;
}

/**
 * @brief Paragraph::set_type设置段落类型
 * @param _type
 */
void Paragraph::set_type(Paragraph_type _type)
{
    type = _type;
}

/**
 * @brief Paragraph::get_type获取段落类型
 * @return
 */
Paragraph_type Paragraph::get_type() const
{
    return type;
}

/**
 * @brief Paragraph::set_is_comment设置是否为评论段
 * @param _c
 */
void Paragraph::set_is_comment(bool _c)
{
    is_comment = _c;
}

/**
 * @brief Paragraph::get_is_comment获取是否为评论段
 * @return
 */
bool Paragraph::get_is_comment() const
{
    return is_comment;
}
