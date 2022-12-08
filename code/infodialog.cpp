#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
    setWindowTitle("Diary Information");
    init_InfoDialog();
    init_connects();
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::init_InfoDialog()
{
    ui->dateEdit->setDate(QDate::currentDate());
}

void InfoDialog::init_connects()
{

}

void InfoDialog::on_pushButton_clicked()
{
    /*获取当前的选项*/
    mood = ui->comboBox_mood->currentText();
    date = ui->dateEdit->date();
    weather = ui->comboBox_weather->currentText();
    location = ui->comboBox_location->currentText();
    comment = ui->lineEdit->text();
    qDebug() << mood << date << weather << location << comment << endl;
    emit widget_closed();
    close();
}

void InfoDialog::on_comboBox_mood_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Add..."){
        QPlainTextEdit *add_tag = new QPlainTextEdit();

    }
}

void InfoDialog::on_comboBox_location_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Add..."){
        QPlainTextEdit *add_tag = new QPlainTextEdit();

    }
}
