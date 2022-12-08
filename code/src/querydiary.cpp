#include "include/querydiary.h"

QueryDiary::QueryDiary() {}

/**
 * @brief QueryDiary::~QueryDiary析构函数，同时析构每一个diary类
 */
QueryDiary::~QueryDiary()
{
    QList<Diary *>::iterator iter;
    for(iter = diarys.begin(); iter != diarys.end(); iter++)
    {
        delete *iter;
    }
}

/**
 * @brief QueryDiary::get_diarys返回查询得到的日记链表
 * @return
 */
QList<Diary *>& QueryDiary::get_diarys()
{
    return diarys;
}
