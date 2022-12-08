#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QSpinBox>
#include <QFontComboBox>
#include <QTextImageFormat>
#include <QUrl>
#include <QTextDocument>
#include <QImage>
#include <QImageReader>
#include <iostream>
#include "searchdialog.h"
#include "infodialog.h"
#include <include/editmanager.h>
#include <include/infomanager.h>
#include <include/querymanager.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    /*界面指针*/
    Ui::MainWindow *ui;
    /*保存路径*/
    QString savepath;
    /*记录是否保存*/
    bool saved;

    InfoManager *info_manager_;
    EditManager *edit_manager_;
    QueryManager *query_manager_;

    /*字体大小*/
    QSpinBox* fontSize;
    /*字体选择框*/
    QFontComboBox* fontCombo;

    /*日记信息输入*/
    InfoDialog* infoDial;

    /*搜索日记*/
    SearchDialog* dial;

    /*当前打开的日记*/
    EditDiary *diary_;

    void init_ui();
    void init_connects();
    void init_manager();
    void open_old_diary(Diary *old_diary);


signals:
    void search_finish(QList<Diary *> &lst);

public slots:
    void on_actionopen_triggered(bool checked);
    void on_actionsave_triggered(bool checked);
    void on_actionnew_triggered(bool checked);
    void on_actionundo_triggered(bool checked);
    void on_actionredo_triggered(bool checked);
    void on_actionpaste_triggered(bool checked);
    void on_actioncopy_triggered(bool checked);
    void on_actioncut_triggered(bool checked);
    void on_actionitalic_triggered(bool checked);
    void on_actionbold_triggered(bool checked);
    void on_actionunderline_triggered(bool checked);
    void on_actionlookup_triggered();
    void on_actionphoto_triggered();

    /*自定义槽*/
    void on_fontCombo_Changed(const QString&);
    void on_fontSize_Changed(int);
    void on_infoDial_closed();
    void open_search_dial();

private slots:
    void on_edited();

};
#endif // MAINWINDOW_H
