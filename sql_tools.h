#ifndef SQL_TOOLS_H
#define SQL_TOOLS_H

#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>
#include <QDebug>


class sql_tools
{
public:
    sql_tools();

    void Create_connection_local_db(QStringList array_config_for_db);
    void Delete_connection_work_db();

    // Создание таблицы
    void Create_a_list();

    // Удаление таблицы
    void Delete_a_list();

    // Добавление нового студента
    void Add_card(int id,
                  QString surname,
                  QString name,
                  QString patronymic,
                  QString year_of_birth,
                  QString sex,
                  QString other);


    // Редактирование карточки студента
    void Update_card(int id,
                     QString surname,
                     QString name,
                     QString patronymic,
                     QString year_of_birth,
                     QString sex,
                     QString other);

    // Удаление карточки студента
    void Delete_card(int id);

private:
    QSqlDatabase db;
};

#endif // SQL_TOOLS_H
