#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();
    string get_text();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SearchDialog *ui;

    /*保存输入的内容*/
    string text;
};

#endif // SEARCHDIALOG_H
