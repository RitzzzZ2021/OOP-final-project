#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    saved = true;
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(on_edited()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionsave_triggered(bool checked)
{
    qDebug() << "保存文件..." << endl;
    if(savepath.isEmpty()){
        QString file_path;
        if(file_path.isEmpty()){
            file_path = QFileDialog::getSaveFileName(this, "选择路径", ".", "*.txt");
        }
        qDebug() << file_path << endl;
        savepath = file_path;
    }

    /*定义QFile文件*/
    QFile txt(savepath);

    /*打开文件*/
    bool sign = txt.open(QIODevice::WriteOnly);
    if(sign){
        /*写入文件*/
        txt.write(ui->textEdit->toPlainText().toStdString().data());
    }else{
        qDebug() << "打开文件失败" << endl;
        /*提示打开文件失败*/
        QMessageBox::critical(NULL, "错误", "无法打开文件", QMessageBox::Yes, QMessageBox::Yes);
    }

    /*关闭文件*/
    txt.close();
    saved = true;
}

void MainWindow::on_actionsaveas_triggered(bool checked)
{
    qDebug() << "另存为..." << endl;
    savepath.clear();
    on_actionsave_triggered(checked);
}

void MainWindow::on_actionnew_triggered(bool checked)
{
    qDebug() << "新建文件..." << endl;
    if(saved){
        ui->textEdit->clear();
        saved = true;
        qDebug() << "清空" << endl;
    }else{
        int tag = QMessageBox::question(NULL, "注意", "是否保存文件？",
                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(tag == QMessageBox::Yes){
            on_actionsave_triggered(false);
        }
        ui->textEdit->clear();
        saved = true;
    }
}

void MainWindow::on_actionundo_triggered(bool checked)
{
    qDebug() << "撤销..." << endl;
    ui->textEdit->undo();
}

void MainWindow::on_actionredo_triggered(bool checked)
{
    qDebug() << "重做..." << endl;
    ui->textEdit->redo();
}

void MainWindow::on_edited()
{
    qDebug() << "文本被修改..." << endl;
    saved = false;
}

void MainWindow::on_actionopen_triggered(bool checked)
{
    qDebug() << "打开文件..." << endl;
    QString file_path = QFileDialog::getOpenFileName(NULL, "打开文件", ".", "*.txt");

    if(file_path.isEmpty()){
        qDebug() << "路径为空" << endl;
        /*提示打开文件失败*/
        QMessageBox::critical(NULL, "错误", "无法打开文件", QMessageBox::Yes, QMessageBox::Yes);
    }
    else{
        /*保存路径*/
        savepath = file_path;
        /*新建文件*/
        QFile txt(file_path);
        qDebug() << file_path;
        /*新建空白的文本框*/
        on_actionnew_triggered(false);
        /*读文件*/
        if(txt.open(QIODevice::ReadOnly | QIODevice::Text)){
            /*获取文本信息*/
            QTextStream read_stream(&txt);
            /*将文本信息展现在文本编辑框中*/
            while(!read_stream.atEnd()){
                ui->textEdit->append(read_stream.readLine());
            }

            /*状态设为保存*/
            saved = true;
        }else{
            QMessageBox::information(this, "信息", "打开文件失败");
        }

        /*关闭文件*/
        txt.close();
    }
}

void MainWindow::on_actionpaste_triggered(bool checked)
{
    qDebug() << "粘贴..." << endl;
    ui->textEdit->paste();
}
