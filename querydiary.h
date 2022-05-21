#ifndef QUERYDIARY_H
#define QUERYDIARY_H

#include <QList>
#include "paragraph.h"
#include "diary.h"

class QueryDiary
{
public:
    QueryDiary();
    ~QueryDiary();
    QList<Diary *>& get_diarys();
private:
    QList<Diary *> diarys;//返回的日记链表
};

#endif // QUERYDIARY_H
