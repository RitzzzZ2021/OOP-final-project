#include "include/editdiary.h"

EditDiary::EditDiary() {}

/**
 * @brief EditDiary::EditDiary创建一个新的日记时使用
 * @param _date日记的日期
 */
EditDiary::EditDiary(QDate _date):
    Diary(_date)
{
    is_dirty = false;
    is_new = true;
}

/**
 * @brief EditDiary::EditDiary已有一篇日记，进入编辑模式
 * @param d日记类，包含基本信息
 */
EditDiary::EditDiary(const Diary& d):
    Diary(d)
{
    is_dirty = false;
    is_new = false;
}

/**
 * @brief EditDiary::set_is_dirty设置该日记是否被修改
 * @param dirty
 */
void EditDiary::set_is_dirty(const bool& dirty)
{
    is_dirty = dirty;
}

/**
 * @brief EditDiary::get_is_dirty查看是否是被修改
 * @return
 */
bool EditDiary::get_is_dirty() const
{
    return is_dirty;
}

bool EditDiary::get_is_new() const
{
    return is_new;
}
