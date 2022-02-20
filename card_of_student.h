#ifndef CARD_OF_STUDENT_H
#define CARD_OF_STUDENT_H

#include <QDialog>
#include <style_sheet_preset.h>
#include <sql_tools.h>
#include <list_of_group_students.h>

namespace Ui {
class Card_of_student;
}

class Card_of_student : public QDialog
{
    Q_OBJECT

public:
    explicit Card_of_student(QWidget *parent = nullptr);
    ~Card_of_student();

    Ui::Card_of_student &getUI();
    void set_style_sheet();
    void trans(List_of_group_students &trans_ref);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    List_of_group_students *trans_ref;
    sql_tools *sql = new sql_tools;
    Ui::Card_of_student *ui;
    static int counter;
};

#endif // CARD_OF_STUDENT_H
