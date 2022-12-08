#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    setWindowTitle("Search");
    init_connects();
    info_manager_ = new InfoManager();
    query_manager_ = new QueryManager();
}

SearchDialog::~SearchDialog()
{
    info_manager_->close_connection();
    delete ui;
}

void SearchDialog::init_connects()
{

}

void SearchDialog::add_into_comboBox(const QList<Diary *> &lst)
{
    if(lst.size() == 0){
        QMessageBox::information(this, "信息", "符合条件的日记不存在");
    }else{
        QString item;
        for(auto i : lst){
            item = i->get_diary_date().toString("Date: yyyy-MM-dd  Comment:") + i->get_comment();
            ui->comboBox->addItem(item);
        }
    }
}

void SearchDialog::on_pushButton_search_clicked()
{
    key = ui->comboBox_keys->currentText();
    value = ui->lineEdit->text();
    qDebug() << "key: " << key << ", value: " << value << endl;
    QueryDiary *ans;
    info_manager_->close_connection();
    info_manager_->create_connectin();

    ui->comboBox->clear();

    /*Qt不支持switch后面用QString类型的变量*/
    QStringList strlist;
    strlist<<"Mood"<<"Location"<<"Weather"<<"Date";
    /*查询得到符合条件的diary列表*/
    switch (strlist.indexOf(key))
    {

        case 0:{
            ans = query_manager_->query_mood(value, *info_manager_);
            lst = ans->get_diarys();
            break;
            }
        case 1:{
            ans = query_manager_->query_location(value, *info_manager_);
            lst = ans->get_diarys();
            break;
            }
        case 2:{
            ans = query_manager_->query_weather(value, *info_manager_);
            lst = ans->get_diarys();
            break;
            }
        case 3:{
            QDate d = QDate::fromString(value, "yyyy-MM-dd");
            ans = query_manager_->query_time(d, d, *info_manager_);
            lst = ans->get_diarys();
            qDebug() << "lst.size()" << lst.size() << endl;
            break;
            }
        default:
            qDebug() << "in default" << endl;
            break;
    }
    // emit search_finish(lst);
    add_into_comboBox(lst);
    info_manager_->close_connection();
}

void SearchDialog::on_pushButton_open_clicked()
{
    int index = ui->comboBox->currentIndex();
    diary_ = lst[index];
    emit search_success();
    close();
}

void SearchDialog::on_pushButton_abort_clicked()
{
    close();
}
