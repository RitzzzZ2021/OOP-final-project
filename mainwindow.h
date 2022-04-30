#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
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

public slots:
    void on_actionopen_triggered(bool checked);
    void on_actionsave_triggered(bool checked);
    void on_actionsaveas_triggered(bool checked);
    void on_actionnew_triggered(bool checked);
    void on_actionundo_triggered(bool checked);
    void on_actionredo_triggered(bool checked);
    void on_actionpaste_triggered(bool checked);


private slots:
    void on_edited();



};
#endif // MAINWINDOW_H
