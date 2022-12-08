#include "include/editmanager.h"
#include <QDebug>

EditManager::EditManager() {}

/**
 * @brief EditManager::delete_diary从数据库中删除一篇日记
 * @param date
 * @param m
 */
void EditManager::delete_diary(const QDate& date, InfoManager m)
{
    m.delete_diary(date);
    if(!m.diary_exist(date)) {
        qDebug() << "in editmanager delete succeess!" << endl;
    } else {
        qDebug() << "in editmanager delete failed!" << endl;
    }
}

/**
 * @brief EditManager::new_diary新建一篇日记,如果日期已经有一篇日记会返回nullptr
 * @param date
 * @param m
 * @return
 */
EditDiary* EditManager::new_diary(QDate date, InfoManager m)
{
    if(!m.diary_exist(date))
    {
        qDebug() <<"new diary"<<endl;
        EditDiary *ret = new EditDiary(date);
        return ret;
    }
    return nullptr;
}

/**
 * @brief EditManager::edit_diary开始编辑某一个日期的日记,如果日期不存在返回nullptr
 * @param date
 * @return
 */
EditDiary* EditManager::edit_diary(QDate date, InfoManager m)
{
    if(!m.diary_exist(date)) {return nullptr;}
    EditDiary *ret;
    QueryDiary*  ans = m.query_time(date, date);
    QList<Diary *> lst = ans->get_diarys();
    qDebug() << "get_diarys()" << endl;
    ret = new EditDiary(*lst[0]);
    qDebug() << "get ret" << endl;
    return ret;
}

/**
 * @brief EditManager::edit_diary从一个已有的日记结构进入编辑模式
 * @param d
 * @return
 */
EditDiary* EditManager::edit_diary(Diary d)
{
    EditDiary *ret = new EditDiary(d);
    return ret;
}

/**
 * @brief EditManager::update_diary使得数据库信息和当前日记信息保持一致,该函数内部会处理new和dirty不同的情形
 * @param edit_diary
 * @param m
 */
void EditManager::update_diary(EditDiary& edit_diary, InfoManager m)
{
    if(edit_diary.get_is_new())
    {
        m.insert_diary(edit_diary);
        edit_diary.is_new = false;
        edit_diary.is_dirty = false;
    }
    else if(edit_diary.get_is_dirty())
    {
        m.update_diary(edit_diary);
        edit_diary.is_dirty = false;
    }
}
