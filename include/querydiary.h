#ifndef QUERYDIARY_H
#define QUERYDIARY_H

#include "include/diary.h"

class QueryDiary
{
public:
    QueryDiary();
    ~QueryDiary();
    QList<Diary *>& get_diarys();
    void add_diary(Diary* nd)
    {
        diarys.append(nd);
    }
private:
    QList<Diary *> diarys;//返回的日记链表
};

#endif // QUERYDIARY_H
