#include "include/diary.h"

Diary::Diary() {}

/**
 * @brief Diary::Diary只初始化日期的构造函数
 * @param _date日期
 */
Diary::Diary(const QDate& _date):diary_date(_date) {}

/**
 * @brief Diary::Diary初始化所有信息的构造函数
 * @param _date日期
 * @param _weather天气
 * @param _location地点
 * @param _mood心情
 * @param _comment评论
 */
Diary::Diary(const QDate& _date, const QString& _weather, const QString& _location, const QString& _mood, const QString& _comment):
    diary_date(_date), diary_meta_data(_weather, _location, _mood, _comment) {}

/**
 * @brief Diary::Diary拷贝构造函数
 * @param r
 */
Diary::Diary(const Diary& r):
    diary_date(r.get_diary_date()), diary_meta_data()
{
    QString weather, location, mood, comment;
    r.get_diary_metadate(weather,location,mood,comment);
    diary_meta_data.set_all(weather, location, mood, comment);
    QList<Paragraph *>::const_iterator iter;
    for(iter = r.get_paragraphs().begin(); iter != r.get_paragraphs().end(); iter++)
    {
        paragraphs << *iter;
    }
}

/**
 * @brief Diary::~Diary析构函数
 */
Diary::~Diary()
{
    QList<Paragraph *>::iterator iter;
    for(iter = paragraphs.begin(); iter != paragraphs.end(); iter++)
    {
        delete *iter;
    }
}

/**
 * @brief Diary::set_diary_date设置日期
 * @param _date日期
 */
void Diary::set_diary_date(const QDate& _date)
{
    diary_date = _date;
}

/**
 * @brief Diary::get_diary_date得到日期
 * @return日期
 */
QDate Diary::get_diary_date() const
{
    return diary_date;
}

/**
 * @brief Diary::set_diary_metadata设置的metadata，所有的参数均可以为空字符串，但是有长度限制，如果超过长度会抛出异常
 * 异常的声明在头文件中。是一个枚举类型。
 * @param _weather天气，最长长度为10
 * @param _location地点，最长长度为25
 * @param _mood心情，最长长度为10
 * @param _comment评论，最场长度为50
 */
void Diary::set_diary_metadata(const QString& _weather, const QString& _location, const QString& _mood, const QString& _comment)
{
    if(_weather.length() > 10) throw EXCEP_WEATHER;
    if(_location.length() > 25) throw EXCEP_LOCATION;
    if(_mood.length() > 10) throw EXCEP_MOOD;
    if(_comment.length() > 50) throw EXCEP_COMMENT;
    diary_meta_data.set_all(_weather, _location, _mood, _comment);
}

/**
 * @brief Diary::set_weather设置天气，超过长度限制会抛出异常
 * @param _weather天气，最长长度为10
 */
void Diary::set_weather(const QString& _weather)
{
    if(_weather.length() > 10) throw EXCEP_WEATHER;
    diary_meta_data.set_weather(_weather);
}

/**
 * @brief Diary::set_location设置地点，超过长度限制会抛出异常
 * @param _location地点，最长长度为25
 */
void Diary::set_location(const QString& _location)
{
    if(_location.length() > 25) throw EXCEP_LOCATION;
    diary_meta_data.set_location(_location);
}

/**
 * @brief Diary::set_mood设置心情，超过长度限制会抛出异常
 * @param _mood心情，最长长度为10
 */
void Diary::set_mood(const QString& _mood)
{
    if(_mood.length() > 10) throw EXCEP_MOOD;
    diary_meta_data.set_mood(_mood);
}

/**
 * @brief Diary::set_comment设置评论，超过长度限制会抛出异常
 * @param _comment评论，最场长度为50
 */
void Diary::set_comment(const QString& _comment)
{
    if(_comment.length() > 50) throw EXCEP_COMMENT;
    diary_meta_data.set_comment(_comment);
}

/**
 * @brief Diary::get_weather得到天气
 * @return天气
 */
QString Diary::get_weather() const
{
    return diary_meta_data.get_weather();
}

/**
 * @brief Diary::get_location得到地点
 * @return地点
 */
QString Diary::get_location() const
{
    return diary_meta_data.get_location();
}

/**
 * @brief Diary::get_mood得到心情
 * @return心情
 */
QString Diary::get_mood() const
{
    return diary_meta_data.get_mood();
}

/**
 * @brief Diary::get_comment得到评论
 * @return评论
 */
QString Diary::get_comment() const
{
    return diary_meta_data.get_comment();
}

/**
 * @brief Diary::get_diary_metadate得到metadata,通过引用进行返回值的传递
 */
void Diary::get_diary_metadate(QString& _weather, QString& _location, QString& _mood, QString& _comment) const
{
    diary_meta_data.get_all(_weather, _location, _mood, _comment);
}

/**
 * @brief Diary::add_paragraphs将一个新的段落加到下标为pos的位置之前（下标为0,1,...,n-1），如果pos不合法将抛出异常
 * 例如a.add_paragraph(0,p)就是将段落p加到第一个位置，a.add_paragraph(a.size(),p)就是将段落p加到最后一个位置
 * 也可以理解为插入到pos位置，将原pos位置及之后的元素后移
 * 调用无序考虑其他段落的id问题，本函数会进行调整
 * @param pos插入位置下标，范围为[0,size()]
 * @param paragraph要插入的段落指针
 */
void Diary::add_paragraphs(int pos, Paragraph* paragraph)
{
    if(pos < 0 || pos > paragraphs.size()) { throw(EXCEP_DES_POS); }
    paragraph->set_diary_belong_id(diary_date);
    paragraphs.insert(pos, paragraph);
    QList<Paragraph *>::iterator iter;
    int cnt = 0;
    for(iter = paragraphs.begin(); iter != paragraphs.end(); iter++)
    {
        Paragraph *t = *iter;
        t->set_para_id(cnt);
        cnt++;
    }
}

/**
 * @brief Diary::remove_paragraphs移除下标为pos的段落，如果pos不合法将抛出异常
 * 调用无需考虑其他段落id问题，本函数会进行调整
 * @param pos删除位置下标，范围为[0,size()-1]
 */
void Diary::remove_paragraphs(int pos)
{
    if(pos < 0 || pos >= paragraphs.size()) { throw(EXCEP_TAR_POS); }
    Paragraph *d = paragraphs[pos];
    delete  d;
    paragraphs.removeAt(pos);
    QList<Paragraph *>::iterator iter;
    int cnt = 0;
    for(iter = paragraphs.begin(); iter != paragraphs.end(); iter++)
    {
        Paragraph *t = *iter;
        t->set_para_id(cnt);
        cnt++;
    }
}

/**
 * @brief Diary::trans_para_pos将下标为target位置的段落移到下标为des的位置，如果下标不合法会抛出异常
 * @param target要移动的段落下标
 * @param des目标下标
 */
void Diary::trans_para_pos(int target, int des)
{
    if(target < 0 || target >= paragraphs.size()) { throw(EXCEP_TAR_POS); }
    if(des < 0 || des >= paragraphs.size() ) { throw(EXCEP_DES_POS); }
    paragraphs.move(target, des);
    QList<Paragraph *>::iterator iter;
    int cnt = 0;
    for(iter = paragraphs.begin(); iter != paragraphs.end(); iter++)
    {
        Paragraph *t = *iter;
        t->set_para_id(cnt);
        cnt++;
    }
}

/**
 * @brief Diary::get_paragraphs得到段落list，所有对段落的修改操作要通过上面的函数进行
 * @return const的段落list
 */
QList<Paragraph *>& Diary::get_paragraphs()
{
    return paragraphs;
}

const QList<Paragraph *>& Diary::get_paragraphs() const
{
    return paragraphs;
}

/**
 * @brief append_para不要调用此函数！该函数不会更改段落的para_id
 * @param p段落
 */
void Diary::append_para(Paragraph* p)
{
    paragraphs.append(p);
}
