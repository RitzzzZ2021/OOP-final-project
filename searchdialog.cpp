#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_buttonBox_accepted()
{
    text = ui->lineEdit->text().toStdString();
}

string SearchDialog::get_text()
{
    return text;
}
