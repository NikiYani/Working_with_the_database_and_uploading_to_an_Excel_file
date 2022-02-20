#include "xlsx_tools.h"

xlsx_tools::xlsx_tools()
{

}

void xlsx_tools::Export_file(QString nameFileForSaving, QTableWidget &table)
{
    QTableWidget *tableBuffer = &table;

    QXlsx::Document xlsx;

    xlsx.addSheet("Список студентов группы ИДМ-20-01");

    QXlsx::Format fontBold; // Заголовочный "Bold"
    fontBold.setFontSize(10);
    fontBold.setFontBold(true);
    fontBold.setFontName("Times New Roman");
    fontBold.setFontColor(QColor(Qt::black));
    fontBold.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    fontBold.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    fontBold.setBorderStyle(QXlsx::Format::BorderThin);
    fontBold.setTextWarp(true);

    QXlsx::Format fontStd; // Стандартный
    fontStd.setFontSize(10);
    fontStd.setFontName("Times New Roman");
    fontStd.setFontColor(QColor(Qt::black));
    fontStd.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    fontStd.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    fontStd.setBorderStyle(QXlsx::Format::BorderThin);
    fontStd.setTextWarp(true);

    xlsx.setColumnWidth(2, 7, 25);
    xlsx.setRowHeight(1, 35);

    xlsx.setColumnWidth(1, 1, 10);

    xlsx.write(1, 1, "id", fontBold);
    xlsx.write(1, 2, "Фамилия", fontBold);
    xlsx.write(1, 3, "Имя", fontBold);
    xlsx.write(1, 4, "Отчество", fontBold);
    xlsx.write(1, 5, "Год рождения", fontBold);
    xlsx.write(1, 6, "Пол", fontBold);
    xlsx.write(1, 7, "Примечание ответа", fontBold);

    for(int i = 2; i < tableBuffer->rowCount() + 2; i++){
        for(int j = 1; j < 8; j++){
            if(j == 1){
                xlsx.write(i, j, i - 1, fontStd);
            }else{
                xlsx.write(i, j, tableBuffer->model()->data(tableBuffer->model()->index(i - 2, j - 1), Qt::DisplayRole), fontStd);
            }
        }
        xlsx.setRowHeight(i, 40);
    }

    xlsx.saveAs(nameFileForSaving);
}
