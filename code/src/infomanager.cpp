#include "include/infomanager.h"
#include <QStringList>
#include <QtDebug>

#define INFO_DEBUG

InfoManager::InfoManager() {}

/**
 * @brief InfoManager::create_connectin
 * 该函数创建数据库连接（在程序的最开始调用）,同时检查是否包含
 * 需要的表格，如果不存在表格则新建表格。
 * 如果建立连接失败会抛出异常。
 */
void InfoManager::create_connectin()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "sqlite");
    db.setDatabaseName(".//diaryDB.db");
    if (!db.open()) { throw EXCEP_CONN_FAILED;}
    QStringList tables = db.tables();
    if(tables.count() == 0)
    {
        create_tables();
    }
}

/**
 * @brief InfoManager::close_connection
 * 检查数据库是否被打开，如果被打开则关闭连接。
 */
void InfoManager::close_connection()
{
    if (db.isOpen()) { db.close();}
}

/**
 * @brief InfoManager::create_tables
 * 创建表格，这个函数只有create_connection需要调用。
 */
void InfoManager::create_tables()
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    QSqlQuery query(db);
    bool success;
    success = query.exec("CREATE TABLE diary(diary_date VARCHAR(15) primary key, weather VARCHAR(10), mood VARCHAR(10), "
                         "location VARCHAR(25), comment VARCHAR(50))");
    if (!success) { throw EXCEP_CTABLE_FAILED; }
    success = query.exec("CREATE TABLE paragraph(diary_date VARCHAR(15), paragraph_id int, "
                         "create_date_time VARCHAR(30), edit_date_time VARCHAR(30), paragraph_type int, "
                         "is_comment int, path VARCHAR(50), "
                         "PRIMARY KEY(diary_date, paragraph_id), "
                         "FOREIGN KEY(diary_date) REFERENCES diary(diary_date))");
    if (!success) { throw EXCEP_CTABLE_FAILED; }
    success = query.exec("CREATE TABLE para_tags(tag_content VARCHAR(20), diary_date VARCHAR(15), paragraph_id int, "
                         "PRIMARY KEY(tag_content, diary_date, paragraph_id), "
                         "FOREIGN KEY(diary_date, paragraph_id) REFERENCES paragraph(diary_date, paragraph_id))");
    if (!success) { throw EXCEP_CTABLE_FAILED; }
}

/**
 * @brief InfoManager::insert_diary将一个日记类插入到数据库中
 * @param d是一个日记类
 */
void InfoManager::insert_diary(const Diary& d)
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query_diary(db);
    QSqlQuery query_paragraphs(db);
    QSqlQuery query_para_tags(db);
    query_diary.prepare("insert into diary values(?,?,?,?,?)");
    query_paragraphs.prepare("insert into paragraph values(?,?,?,?,?,?,?)");
    query_para_tags.prepare("insert into para_tags values(?,?,?)");

    QString date, weather, location, mood, comment;
    d.get_diary_metadate(weather, location, mood, comment);
    date = d.get_diary_date().toString("yyyy-MM-dd");

    query_diary.bindValue(0, date);
    query_diary.bindValue(1, weather);
    query_diary.bindValue(2, mood);
    query_diary.bindValue(3, location);
    query_diary.bindValue(4, comment);
    success = query_diary.exec();
    if(!success) { throw EXCEP_EXE_FAILED;}

    QList<Paragraph*> ps = d.get_paragraphs();
    QList<Paragraph*>::iterator iter;
    Paragraph* pp;

    int pid, pty, isc;
    QString cdt, edt, path;
    QDate td;
    QTime tt;
    QList<QString> tgs;
    QList<QString>::iterator titer;
    for(iter = ps.begin(); iter != ps.end(); iter++)
    {
        pp = *iter;
        pid = pp->get_para_id();
        pp->get_create_date_time(td,tt);
        cdt = td.toString("yyyy-MM-dd") + " " + tt.toString("hh:mm:ss.zzz");
        pp->get_edit_date_time(td,tt);
        edt = td.toString("yyyy-MM-dd") + " " + tt.toString("hh:mm:ss.zzz");
        pty = pp->get_type();
        isc = pp->get_is_comment();
        path = pp->get_path();
        query_paragraphs.bindValue(0, date);
        query_paragraphs.bindValue(1, pid);
        query_paragraphs.bindValue(2, cdt);
        query_paragraphs.bindValue(3, edt);
        query_paragraphs.bindValue(4, pty);
        query_paragraphs.bindValue(5, isc);
        query_paragraphs.bindValue(6, path);
        success = query_paragraphs.exec();
        if(!success) { throw EXCEP_EXE_FAILED;}
        tgs = pp->get_tags();
        for(titer = tgs.begin(); titer != tgs.end(); titer++)
        {
            query_para_tags.bindValue(0, *titer);
            query_para_tags.bindValue(1, date);
            query_para_tags.bindValue(2, pid);
            success = query_para_tags.exec();
            if(!success) { throw EXCEP_EXE_FAILED;}
        }
    }
}

/**
 * @brief InfoManager::delete_diary从数据库中删除一个日记类
 * @param date是要删除的日记的日期
 */
void InfoManager::delete_diary(const QDate& date)
{
    qDebug() << "in infomanager delete diary" << endl;
#ifdef INFO_DEBUG
    QStringList tables = db.tables();
    if(tables.count() == 0)
    {
        qDebug() << "in infomanager dbg, no table exist" << endl;
    }
#endif
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query_diary(db);
    QSqlQuery query_paragraphs(db);
    QSqlQuery query_para_tags(db);
    success = query_diary.prepare("delete from diary where diary_date = ?");
    if(!success) { qDebug() << "in infomanager delete diary prepare diary failed" << endl; throw EXCEP_P_FAILED; }
    success = query_paragraphs.prepare("delete from paragraph where diary_date = ?");
    if(!success) { qDebug() << "in infomanager delete diary prepare paragraph failed" << endl; throw EXCEP_P_FAILED; }
    success = query_para_tags.prepare("delete from para_tags where diary_date = ?");
    if(!success) { qDebug() << "in infomanager delete diary prepare para_tag failed" << endl; throw EXCEP_P_FAILED; }

    query_diary.bindValue(0, date.toString("yyyy-MM-dd"));
    query_paragraphs.bindValue(0, date.toString("yyyy-MM-dd"));
    query_para_tags.bindValue(0, date.toString("yyyy-MM-dd"));
    success = query_diary.exec();
    if(!success) { throw EXCEP_EXE_FAILED;}
    qDebug() <<  "delete diary affect " << query_diary.numRowsAffected() << "rows" << endl;
    success = query_paragraphs.exec();
    if(!success) { throw EXCEP_EXE_FAILED;}
    qDebug() <<  "delete para affect " << query_paragraphs.numRowsAffected() << "rows" << endl;
    success = query_para_tags.exec();
    if(!success) { throw EXCEP_EXE_FAILED;}
    qDebug() <<  "delete para_tag affect " << query_para_tags.numRowsAffected() << "rows" << endl;
}

/**
 * @brief InfoManager::update_diary更新某一天的日记
 * @param d是一个日记类
 */
void InfoManager::update_diary(const Diary& d)
{
    delete_diary(d.get_diary_date());
    insert_diary(d);
}

/**
 * @brief InfoManager::diary_exist查询日记是否存在
 * @param date是要查询的日记日期
 * @return 如果存在返回True,否则返回False
 */
bool InfoManager::diary_exist(const QDate& date)
{
    qDebug() << "in infomanager diary_exist" << endl;
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query(db);
    success = query.prepare("select * from diary where diary_date = ?");
    if(!success) { qDebug() << "prepare failed" << endl; throw EXCEP_P_FAILED; }
    query.bindValue(0, date.toString("yyyy-MM-dd"));
    success = query.exec();
    if(!success) { throw EXCEP_EXE_FAILED;}
#ifdef INFO_DEBUG
    bool is_ex = false;
    while(query.next()) {
        qDebug() << "finding..." << endl;
        qDebug() << query.at() << endl;
        is_ex = true;
        break;
    }
    qDebug() << "done" << endl;
#endif
    if(is_ex) {
        qDebug() << "idx = 0 exist" << endl;
        return true;
    }
    qDebug() << "idx = 0 not exist" << endl;
    return false;
}

/**
 * @brief InfoManager::query_tags按照标签查询日记，标签之间的连接方式是or
 * @param tags标签list
 * @return
 */
Diary* InfoManager::query_tags(const QList<QString>& tags)
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    bool first = true;
    QString sqlstat, at;
    sqlstat = "select distinct diary_date, paragraph_id from para_tags where ";
    QList<QString>::const_iterator iter;
    for(iter = tags.begin(); iter != tags.end(); iter++)
    {
        at = "tag_content = " + *iter;
        if(first)
        {
            sqlstat += at;
            first = false;
        }
        else
        {
            sqlstat += " or ";
            sqlstat += at;
        }
    }
    sqlstat += "order by diary_date, paragraph_id";
    QSqlQuery query(db);
    success = query.prepare(sqlstat);
    if(!success) {throw EXCEP_P_FAILED;}
    success = query.exec();
    if(!success) {throw EXCEP_EXE_FAILED;}
    if(query.size() == 0) return nullptr;
    Diary *ret = new Diary();
    // 遍历查询到的符合条件的段落
    while(query.next())
    {
        QString rdate = query.value(0).toString();
        int rpid = query.value(1).toInt();
        Paragraph *para = new Paragraph(QDate::fromString(rdate, "yyyy-MM-dd"), rpid);
        QSqlQuery q(db);
        q.prepare("select * from paragraph where diary_date = ? and paragraph_id = ?");
        q.bindValue(0, rdate);
        q.bindValue(1, rpid);
        success = q.exec();
        if(!success) {throw EXCEP_EXE_FAILED;}
        // 加载段落的基本信息,因为是对primary key的查询,所以只会有一个结果
        while(q.next())
        {
            QString cdt = q.value(2).toString();
            QString edt = q.value(3).toString();
            int pty = q.value(4).toInt();
            bool isc = q.value(5).toBool();
            QString path = q.value(6).toString();
            para->set_create_date_time(QDateTime::fromString(cdt,"yyyy-MM-dd hh:mm:ss").date(), QDateTime::fromString(cdt,"yyyy-MM-dd hh:mm:ss").time());
            para->set_edit_date_time(QDateTime::fromString(edt,"yyyy-MM-dd hh:mm:ss").date(), QDateTime::fromString(edt,"yyyy-MM-dd hh:mm:ss").time());
            para->set_type((Paragraph_type)pty);
            para->set_is_comment(isc);
            para->set_path(path);
        }
        // 查询段落的所有tag
        QSqlQuery q_tag(db);
        q_tag.prepare("select tag_content from para_tags where diary_date = ? and paragraph_id = ?");
        q_tag.bindValue(0, rdate);
        q_tag.bindValue(1, rpid);
        success = q_tag.exec();
        if(!success) {throw EXCEP_EXE_FAILED;}
        while(q_tag.next())
        {
            QString t = q_tag.value(0).toString();
            para->add_tags(t);
        }
        ret->append_para(para);
    }
    return ret;
}

/**
 * @brief InfoManager::query_type根据段落的类型进行查询
 * @param type段落的类型
 * @return
 */
Diary* InfoManager::query_type(const Paragraph_type& type)
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query(db);
    success = query.prepare("select diary_date, paragraph_id from paragraph where paragraph_type = ? order by diary_date, paragraph_id");
    if(!success) {throw EXCEP_P_FAILED;}
    query.bindValue(0, type);
    success = query.exec();
    if(!success) {throw EXCEP_EXE_FAILED;}
    if(query.size() == 0) return nullptr;
    Diary *ret = new Diary();
    // 遍历查询到的符合条件的段落
    while(query.next())
    {
        QString rdate = query.value(0).toString();
        int rpid = query.value(1).toInt();
        Paragraph *para = new Paragraph(QDate::fromString(rdate, "yyyy-MM-dd"), rpid);
        QSqlQuery q(db);
        q.prepare("select * from paragraph where diary_date = ? and paragraph_id = ?");
        q.bindValue(0, rdate);
        q.bindValue(1, rpid);
        success = q.exec();
        if(!success) {throw EXCEP_EXE_FAILED;}
        // 加载段落的基本信息,因为是对primary key的查询,所以只会有一个结果
        while(q.next())
        {
            QString cdt = q.value(2).toString();
            QString edt = q.value(3).toString();
            int pty = q.value(4).toInt();
            bool isc = q.value(5).toBool();
            QString path = q.value(6).toString();
            para->set_create_date_time(QDateTime::fromString(cdt,"yyyy-MM-dd hh:mm:ss").date(), QDateTime::fromString(cdt,"yyyy-MM-dd hh:mm:ss").time());
            para->set_edit_date_time(QDateTime::fromString(edt,"yyyy-MM-dd hh:mm:ss").date(), QDateTime::fromString(edt,"yyyy-MM-dd hh:mm:ss").time());
            para->set_type((Paragraph_type)pty);
            para->set_is_comment(isc);
            para->set_path(path);
        }
        // 查询段落的所有tag
        QSqlQuery q_tag(db);
        q_tag.prepare("select tag_content from para_tags where diary_date = ? and paragraph_id = ?");
        q_tag.bindValue(0, rdate);
        q_tag.bindValue(1, rpid);
        success = q_tag.exec();
        if(!success) {throw EXCEP_EXE_FAILED;}
        while(q_tag.next())
        {
            QString t = q_tag.value(0).toString();
            para->add_tags(t);
        }
        ret->append_para(para);
    }
    return ret;
}

/**
 * @brief InfoManager::query_date查询特定日期的日记
 * @param d日期,类型为QString
 * @return
 */
Diary* InfoManager::query_date(const QString& d)
{
    qDebug() << "in infomanager query_date" << endl;
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query_diary(db);
    success = query_diary.prepare("select * from diary where diary_date = ?");
    if(!success) { qDebug() << "prepare failed" << endl; throw EXCEP_P_FAILED; }
    query_diary.bindValue(0, d);
    success = query_diary.exec();
    if(!success) { qDebug() << "exe failed" << endl; throw EXCEP_EXE_FAILED; }
    Diary *ret;
    while(query_diary.next())
    {
        QString weather = query_diary.value(1).toString();
        QString mood = query_diary.value(2).toString();
        QString location = query_diary.value(3).toString();
        QString comment = query_diary.value(4).toString();
        qDebug() << "new a diary, with data " << QDate::fromString(d, "yyyy-MM-dd") << " " << weather << " " << location << " " << mood;
        qDebug() << " " << comment << endl;
        ret = new Diary(QDate::fromString(d, "yyyy-MM-dd"), weather, location, mood, comment);
    }
    QSqlQuery query_para(db);
    success = query_para.prepare("select * from paragraph where diary_date = ? order by paragraph_id");
    if(!success) { qDebug() << "prepare paragraph failed" << endl; throw EXCEP_P_FAILED;}
    query_para.bindValue(0, d);
    success = query_para.exec();
    if(!success) { throw EXCEP_EXE_FAILED; }
    Paragraph *np;
    while(query_para.next())
    {
        int pid = query_para.value(1).toInt();
        QString cdt = query_para.value(2).toString();
        QString edt = query_para.value(3).toString();
        int pty = query_para.value(4).toInt();
        bool isc = query_para.value(5).toBool();
        QString path = query_para.value(6).toString();
        np = new Paragraph(QDate::fromString(d, "yyyy-MM-dd"), pid);
        np->set_create_date_time(QDateTime::fromString(cdt,"yyyy-MM-dd hh:mm:ss").date(), QDateTime::fromString(cdt,"yyyy-MM-dd hh:mm:ss").time());
        np->set_edit_date_time(QDateTime::fromString(edt,"yyyy-MM-dd hh:mm:ss").date(), QDateTime::fromString(edt,"yyyy-MM-dd hh:mm:ss").time());
        np->set_type((Paragraph_type)pty);
        np->set_is_comment(isc);
        np->set_path(path);
        //查询tags并且插入
        QSqlQuery q_tag(db);
        q_tag.prepare("select tag_content from para_tags where diary_date = ? and paragraph_id = ?");
        q_tag.bindValue(0, d);
        q_tag.bindValue(1, pid);
        success = q_tag.exec();
        if(!success) { throw EXCEP_EXE_FAILED; }
        while(q_tag.next())
        {
            np->add_tags(q_tag.value(0).toString());
        }
        ret->append_para(np);
    }
    return ret;
}

/**
 * @brief InfoManager::query_time按照日期查询日记,如果要求等值查询,令begin_date==end_date即可
 * @param begin_date查询的开始日期
 * @param end_date查询的结束日期
 * @return
 */
QueryDiary* InfoManager::query_time(const QDate& begin_date, const QDate& end_date)
{
    qDebug() << "in infomanager query_time" << endl;
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query(db);
    success = query.prepare("select diary_date from diary where diary_date >= ? and diary_date <= ? order by diary_date");
    if(!success) { qDebug() << "prepare failed" << endl; throw EXCEP_P_FAILED;}
    query.bindValue(0, begin_date.toString("yyyy-MM-dd"));
    query.bindValue(1, end_date.toString("yyyy-MM-dd"));
    success = query.exec();
    if(!success) { throw EXCEP_EXE_FAILED; }
    QueryDiary *ret = new QueryDiary;
    while(query.next())
    {
        qDebug() << "add a diary, date is " << query.value(0).toString() << endl;
        ret->add_diary(query_date(query.value(0).toString()));
    }
    return ret;
}

/**
 * @brief InfoManager::query_weather按照天气查询日记
 * @param weather天气
 * @return
 */
QueryDiary* InfoManager::query_weather(const QString& weather)
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query(db);
    query.prepare("select diary_date from diary where weather = ? order by diary_date");
    query.bindValue(0, weather);
    success = query.exec();
    if(!success) { throw EXCEP_EXE_FAILED; }
    if(query.size() == 0) { return nullptr; }
    QueryDiary *ret = new QueryDiary;
    while(query.next())
    {
        ret->add_diary(query_date(query.value(0).toString()));
    }
    return ret;
}

/**
 * @brief InfoManager::query_location按照地点查询日记
 * @param location地点
 * @return
 */
QueryDiary* InfoManager::query_location(const QString& location)
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query(db);
    query.prepare("select diary_date from diary where location = ? order by diary_date");
    query.bindValue(0, location);
    success = query.exec();
    if(!success) { throw EXCEP_EXE_FAILED; }
    if(query.size() == 0) { return nullptr; }
    QueryDiary *ret = new QueryDiary;
    while(query.next())
    {
        ret->add_diary(query_date(query.value(0).toString()));
    }
    return ret;
}

/**
 * @brief InfoManager::query_mood按照心情查询日记
 * @param mood心情
 * @return
 */
QueryDiary* InfoManager::query_mood(const QString& mood)
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query(db);
    query.prepare("select diary_date from diary where mood = ? order by diary_date");
    query.bindValue(0, mood);
    success = query.exec();
    if(!success) { throw EXCEP_EXE_FAILED; }
    if(query.size() == 0) { return nullptr; }
    QueryDiary *ret = new QueryDiary;
    while(query.next())
    {
        ret->add_diary(query_date(query.value(0).toString()));
    }
    return ret;
}

/**
 * @brief InfoManager::query_all查询全部日记
 * @return
 */
QueryDiary* InfoManager::query_all()
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query(db);
    query.prepare("select diary_date from diary order by diary_date");
    success = query.exec();
    if(!success) { throw EXCEP_EXE_FAILED; }
    if(query.size() == 0) { return nullptr; }
    QueryDiary *ret = new QueryDiary;
    while(query.next())
    {
        ret->add_diary(query_date(query.value(0).toString()));
    }
    return ret;
}

QStringList InfoManager::get_all_tags()
{
    if(!db.isOpen()) {throw EXCEP_CONN_NEXIST;}
    bool success;
    QSqlQuery query(db);
    query.prepare("select distinct tag_content from para_tags");
    success = query.exec();
    if(!success) { throw EXCEP_EXE_FAILED; }
    QStringList ret;
    while(query.next())
    {
        ret << query.value(0).toString();
    }
    return ret;
}
