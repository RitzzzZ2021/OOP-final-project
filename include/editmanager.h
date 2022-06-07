#ifndef EDITMANAGER_H
#define EDITMANAGER_H

#include "include/editdiary.h"
#include "include/infomanager.h"

class EditManager
{
public:
    EditManager();
    void delete_diary(const QDate& date, InfoManager m);
    EditDiary* new_diary(QDate date, InfoManager m);
    EditDiary* edit_diary(QDate date, InfoManager m);
    EditDiary* edit_diary(Diary d);
    void update_diary(EditDiary& edit_diary, InfoManager m);
};

#endif // EDITMANAGER_H
