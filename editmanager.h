#ifndef EDITMANAGER_H
#define EDITMANAGER_H

#include "editdiary.h"
#include "infomanager.h"
#include "diary.h"

class EditManager
{
public:
    EditManager();
    void delete_diary(const QDate& date);
    EditDiary* new_diary(QDate date);
    EditDiary* edit_diary(QDate date);
    EditDiary* edit_diary(Diary d);
    void update_diary(EditDiary& edit_diary);
};

#endif // EDITMANAGER_H
