#ifndef EDITDIARY_H
#define EDITDIARY_H

#include "include/diary.h"

class EditDiary: public Diary
{
public:
    EditDiary();
    void set_is_dirty(const bool& dirty);
    bool get_is_dirty() const;
    bool get_is_new() const;
    friend class EditManager;
private:
    EditDiary(QDate _date);
    EditDiary(const Diary& d);
    bool is_dirty;//日记是否被修改，也就是是否和数据库信息不一致
    bool is_new;//是否是新建的日记
};

#endif // EDITDIARY_H
