#include "card_of_student.h"
#include "ui_card_of_student.h"

int Card_of_student::counter = 0;

void Card_of_student::set_style_sheet()
{
    Style_sheet_preset *style_sheet = new Style_sheet_preset;

    this->setStyleSheet(style_sheet->window_gray());

    ui->groupBox->setStyleSheet(style_sheet->groupbox_white());
    ui->groupBox_2->setStyleSheet(style_sheet->groupbox_white());
    ui->groupBox_5->setStyleSheet(style_sheet->groupbox_blue());

    ui->label_4->setStyleSheet(style_sheet->label_white());

    ui->pushButton->setStyleSheet(style_sheet->buttom_gray_blue());
    ui->pushButton_2->setStyleSheet(style_sheet->buttom_gray_blue());

    delete style_sheet;
}

void Card_of_student::trans(List_of_group_students &trans_ref)
{
    this->trans_ref = &trans_ref;
}

Card_of_student::Card_of_student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Card_of_student)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Мужской");
    ui->comboBox->addItem("Женский");
    ui->comboBox->addItem("Другое");
}

Card_of_student::~Card_of_student()
{
    delete sql;
    delete ui;
}

Ui::Card_of_student &Card_of_student::getUI()
{
    return *this->ui;
}

void Card_of_student::on_pushButton_2_clicked()
{
    this->close();
}


void Card_of_student::on_pushButton_clicked()
{
    sql->Add_card(counter,
                  ui->lineEdit_2->text(),
                  ui->lineEdit_3->text(),
                  ui->lineEdit_4->text(),
                  ui->dateEdit->date().toString("yyyy-MM-dd"),
                  ui->comboBox->currentText(),
                  ui->lineEdit_5->text());
    ++counter;

    trans_ref->Gen_table();
    this->close();
}

