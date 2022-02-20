#include "list_of_group_students.h"
#include "ui_list_of_group_students.h"
#include "card_of_student.h"
#include "ui_card_of_student.h"

void List_of_group_students::Gen_table()
{
    ui->tableWidget->clear();

    int row_iteration = 0;

    sql_query->exec("SELECT COUNT(*) FROM \"Список студентов\"");

    if(sql_query->next()){
        ui->tableWidget->setRowCount(sql_query->value(0).toInt());
    }

    ui->tableWidget->setColumnCount(7);

    sql_query->exec("SELECT * FROM \"Список студентов\"");

    while(sql_query->next()){
        for(int i = 0; i < 7; i++){
            QTableWidgetItem* text_field = new QTableWidgetItem(sql_query->value(i).toString());
            ui->tableWidget->setItem(row_iteration, i, text_field);
        }
        row_iteration++;
    }

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("id"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Фамилия"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Имя"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Отчество"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Год рождения"));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Пол"));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Примечание"));

    ui->tableWidget->setWordWrap(true);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);

    for(int i = 0; i < 4; i++){
        if(i != 6){
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
        }
    }

    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);
}

List_of_group_students::List_of_group_students(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::List_of_group_students)
{
    ui->setupUi(this);
}

List_of_group_students::~List_of_group_students()
{
    delete xlsx;
    delete sql;
    delete sql_query;
    delete ui;
}

void List_of_group_students::set_style_sheet()
{
    Style_sheet_preset *style_sheet = new Style_sheet_preset;

    this->setStyleSheet(style_sheet->window_gray());

    ui->groupBox->setStyleSheet(style_sheet->groupbox_white());
    ui->groupBox_2->setStyleSheet(style_sheet->groupbox_white());
    ui->groupBox_3->setStyleSheet(style_sheet->groupbox_white());
    ui->groupBox_4->setStyleSheet(style_sheet->groupbox_blue());
    ui->groupBox_5->setStyleSheet(style_sheet->groupbox_white());
    ui->groupBox_6->setStyleSheet(style_sheet->groupbox_white());

    ui->label->setStyleSheet(style_sheet->label_white());
    ui->label_2->setStyleSheet(style_sheet->label_white());

    ui->pushButton->setStyleSheet(style_sheet->buttom_gray_blue());
    ui->pushButton_3->setStyleSheet(style_sheet->buttom_gray_blue());
    ui->pushButton_4->setStyleSheet(style_sheet->buttom_gray_blue());
    ui->pushButton_5->setStyleSheet(style_sheet->buttom_gray_blue());
    ui->pushButton_7->setStyleSheet(style_sheet->buttom_gray_blue());

    ui->pushButton->setToolTip("Добавить нового студента");
    ui->pushButton_3->setToolTip("Удалить студента");
    ui->pushButton_4->setToolTip("Обновить список студентов");
    ui->pushButton_5->setToolTip("Выход из программы");
    ui->pushButton_7->setToolTip("Выгрузка списка студентов в Excel-файл");

    delete style_sheet;
}

Ui::List_of_group_students &List_of_group_students::getUI()
{
    return *this->ui;
}

void List_of_group_students::on_pushButton_clicked()
{
    Card_of_student *COS = new Card_of_student();
    COS->setWindowTitle("Карточка студента");
    COS->getUI().label_4->setText("Добавление нового студента в список");
    COS->set_style_sheet();
    COS->trans(*this);
    COS->show();
}

void List_of_group_students::on_pushButton_3_clicked()
{
    if(ui->tableWidget->model() != NULL){
        if(!ui->tableWidget->selectionModel()->selectedRows().isEmpty()){
            QMessageBox msgBox;
            msgBox.setText("Вы действительно хотите удалить данного студента из списка?");
            msgBox.setWindowTitle("Удаление");
            msgBox.setWindowIcon(QIcon("./logo/Logo_ARM_SURID.png"));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setDefaultButton(QMessageBox::No);
            int res = msgBox.exec();
            if(res == QMessageBox::Yes){
                int row_current_index = ui->tableWidget->currentIndex().row();

                sql->Delete_card(row_current_index);

                Gen_table();
            }
        }
    }
}


void List_of_group_students::on_pushButton_4_clicked()
{
    Gen_table();
}

void List_of_group_students::on_pushButton_7_clicked()
{
    QString nameFileForSaving = QFileDialog::getSaveFileName(this,
                                                             tr("Сохранить список студентов"),
                                                             "Список студентов ИДМ-20-01.xlsx",
                                                             tr("xlsx(*xlsx)"));

    if(nameFileForSaving.isEmpty()){
        qDebug() << "Не был выбран путь.\nФайл не сохранен!";
        return;
    }else{
        xlsx->Export_file(nameFileForSaving, *ui->tableWidget);
    }
}

void List_of_group_students::on_pushButton_5_clicked()
{
    QMessageBox msg_box;
    msg_box.setText("Вы действительно хотите выйти?");
    msg_box.setWindowTitle("Выход");
    msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg_box.setIcon(QMessageBox::Warning);
    msg_box.setDefaultButton(QMessageBox::No);
    if(msg_box.exec() == QMessageBox::No)
    {
        return;
    }
    else
    {
        QThread::sleep(1);
        this->close();
        exit(0);
    }
}

void List_of_group_students::on_tableWidget_clicked(const QModelIndex &index)
{
    ui->tableWidget->selectRow(index.row());
}
