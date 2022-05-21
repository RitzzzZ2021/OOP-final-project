#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    saved = true;
    init_ui();
    init_connects();
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(on_edited()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_ui()
{
    ui->toolBar->addSeparator();

    fontCombo = new QFontComboBox();
    fontCombo->setMinimumWidth(20);
    ui->toolBar->addWidget(new QLabel("字体:"));
    ui->toolBar->addWidget(fontCombo);

    /*增加一个字体大小选择框*/
    ui->toolBar->addSeparator();
    fontSize = new QSpinBox();
    fontSize->setMinimumWidth(70);
    fontSize->setMinimum(5);
    fontSize->setMaximum(100);
    ui->toolBar->addWidget(new QLabel("字体大小:"));
    ui->toolBar->addWidget(fontSize);

    setWindowTitle("Notebook");

    /*设置光标*/
    setCursor(Qt::CrossCursor);
}

void MainWindow::init_connects()
{
    connect(fontSize, SIGNAL(valueChanged(int)), this, SLOT(on_fontSize_Changed(int)));
    connect(fontCombo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(on_fontCombo_Changed(const QString&)));
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
        QMessageBox::critical(NULL, "错误", "保存失败", QMessageBox::Yes, QMessageBox::Yes);
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
    QClipboard *c = QApplication::clipboard();
    /*粘贴到光标处*/
    ui->textEdit->paste();
}

void MainWindow::on_actioncopy_triggered(bool checked)
{
    qDebug() << "复制..." << endl;
    QClipboard* c = QApplication::clipboard();
    /*选定内容*/
    QString content = ui->textEdit->textCursor().selectedText();
    /*粘贴到剪切板上*/
    c->setText(content);
}

void MainWindow::on_actioncut_triggered(bool checked)
{
    qDebug() << "剪切..." << endl;
    QClipboard* c = QApplication::clipboard();
    /*选定内容*/
    QString content = ui->textEdit->textCursor().selectedText();
    /*粘贴到剪切板上*/
    c->setText(content);

    /*删除选定的内容*/
    QString text = ui->textEdit->toPlainText();
    text.remove(content);
    ui->textEdit->setText(text);
}

void MainWindow::on_fontCombo_Changed(const QString& fontcombo)
{
    QTextCharFormat f;
    /*设置字体*/
    f.setFontFamily(fontcombo);
    ui->textEdit->mergeCurrentCharFormat(f);
}

void MainWindow::on_fontSize_Changed(int fontsize)
{
    QTextCharFormat f;
    /*设置字体大小*/
    f.setFontPointSize(fontsize);
    ui->textEdit->mergeCurrentCharFormat(f);
}

void MainWindow::on_actionitalic_triggered(bool checked)
{
    QTextCharFormat f;
    /*获取目前字体*/
    f = ui->textEdit->currentCharFormat();
    if(checked){
        f.setFontItalic(true);
    }else{
        f.setFontItalic(false);
    }
    ui->textEdit->mergeCurrentCharFormat(f);
}

void MainWindow::on_actionbold_triggered(bool checked)
{
    QTextCharFormat f;
    /*获取目前字体*/
    f = ui->textEdit->currentCharFormat();
    if(checked){
        f.setFontWeight(QFont::Bold);
    }else{
        f.setFontWeight(QFont::Normal);
    }
    ui->textEdit->mergeCurrentCharFormat(f);
}

void MainWindow::on_actionunderline_triggered(bool checked)
{
    QTextCharFormat f;
    /*获取目前字体*/
    f = ui->textEdit->currentCharFormat();
    if(checked){
        f.setFontUnderline(true);
    }else{
        f.setFontUnderline(false);
    }
    ui->textEdit->mergeCurrentCharFormat(f);
}

void MainWindow::on_actionlookup_triggered()
{
    dial = new SearchDialog(this);
    dial->show();
}

void MainWindow::on_actionphoto_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("选择图片"),
                                                ".",tr("BMP (*.bmp)\n"
                                                       "JPEG (*.jpg *.jpeg)\n"
                                                       "GIF (*.gif)\n"
                                                       "PNG (*.png)\n"));

    QUrl Uri(QString("file://%1").arg(file));
    QImage image = QImageReader(file).read();
    QTextDocument* textDocument = ui->textEdit->document();
    textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth(image.width());
    imageFormat.setHeight(image.height());
    imageFormat.setName(Uri.toString());
    cursor.insertImage(imageFormat);
}
