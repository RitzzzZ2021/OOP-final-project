QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += qt

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    infodialog.cpp \
    searchdialog.cpp \
    src/diary.cpp \
    src/diarymetadata.cpp \
    src/editdiary.cpp \
    src/editmanager.cpp \
    src/infomanager.cpp \
    src/metadata.cpp \
    src/paragraph.cpp \
    src/querydiary.cpp \
    src/querymanager.cpp

HEADERS += \
    include/diary.h \
    include/diarymetadata.h \
    include/editdiary.h \
    include/editmanager.h \
    include/infomanager.h \
    include/metadata.h \
    include/paragraph.h \
    include/querydiary.h \
    include/querymanager.h \
    mainwindow.h \
    infodialog.h \
    searchdialog.h

FORMS += \
    mainwindow.ui \
    infodialog.ui \
    searchdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    myResources.qrc \
    qss.qrc
