#include "sql_tools.h"

void sql_tools::Create_connection_local_db(QStringList array_config_for_db)
{
    db = QSqlDatabase::addDatabase(array_config_for_db[0]);
    db.setDatabaseName(array_config_for_db[1]);
    db.setUserName(array_config_for_db[3]);
    db.setPassword(array_config_for_db[4]);

    if(!db.open())
    {
        QMessageBox::warning(0, "Ошибка подключения к базе данных", db.lastError().text());
    }
    else
    {
        QMessageBox::information(0, "Проверка соединения с сервером!", "Соединение с локальной базой данных установлено!");
    }
}

void sql_tools::Delete_connection_work_db()
{
    db.close();
}

void sql_tools::Create_a_list()
{
    QSqlQuery query_a_link_table = QSqlQuery(db);

    if(!query_a_link_table.exec("CREATE TABLE public.\"Список студентов\""
                                "(id integer NOT NULL,"
                                "\"Фамилия\" text NOT NULL,"
                                "\"Имя\" text NOT NULL,"
                                "\"Отчество\" text NOT NULL,"
                                "\"Год рождения\" date,"
                                "\"Пол\" text,"
                                "\"Примечание\" text,"
                                "PRIMARY KEY (id))"))

    {
        QMessageBox::warning(0, "Ошибка создания списка", query_a_link_table.lastError().databaseText());
    }
    else
    {
        qDebug() << "Список студентов создан!";
    }
}

void sql_tools::Delete_a_list()
{
    QSqlQuery query_delete_a_link_table = QSqlQuery(db);

    if(!query_delete_a_link_table.exec("DROP TABLE \"Список студентов\""))
    {
        qDebug() << query_delete_a_link_table.lastError().databaseText();
        qDebug() << query_delete_a_link_table.lastError().driverText();
        return;
    }
    else
    {
        qDebug() << "Список студентов удален!";
    }
}

void sql_tools::Add_card(int id,
                         QString surname,
                         QString name,
                         QString patronymic,
                         QString year_of_birth,
                         QString sex,
                         QString other)
{
    QSqlQuery query_add = QSqlQuery(db);

    QString query_add_str = "INSERT INTO \"Список студентов\" "
                            "(id, "
                            "\"Фамилия\", "
                            "\"Имя\", "
                            "\"Отчество\", "
                            "\"Год рождения\", "
                            "\"Пол\", "
                            "\"Примечание\")";

    query_add_str += "VALUES (" + QString::number(id)
            + ", '" + surname
            + "', '" + name
            + "', '" + patronymic
            + "', '" + year_of_birth
            + "', '" + sex
            + "', '" + other
            + "')";

    qDebug() << query_add_str;

    if(!query_add.exec(query_add_str))
    {
        qDebug() << query_add.lastError().databaseText();
        qDebug() << query_add.lastError().driverText();

        QMessageBox::warning(0, "Введены некорректные данные!", query_add.lastError().databaseText());

        return;
    }
    else
    {
        qDebug() << "Новый студент успешно создан!";
    }
}

void sql_tools::Update_card(int id, QString surname, QString name, QString patronymic, QString year_of_birth, QString sex, QString other)
{
    QSqlQuery query_delete = QSqlQuery(db);

    QString query_add_str = "UPDATE \"Список студентов\" SET ";

    query_add_str += "\"Фамилия\" = '" + surname + "', ";
    query_add_str += "\"Имя\" = '" + name + "', ";
    query_add_str += "\"Отчество\" = '" + patronymic + "', ";
    query_add_str += "\"Год рождения\" = '" + year_of_birth + "', ";
    query_add_str += "\"Пол\" = '" + sex + "', ";
    query_add_str += "\"Примечание\" = '" + other + "'";

    query_add_str += "WHERE id = " + QString::number(id);

    qDebug() << query_add_str;

    if(!query_delete.exec(query_add_str))
    {
        qDebug() << query_delete.lastError().databaseText();
        qDebug() << query_delete.lastError().driverText();
        return;
    }
    else
    {
        qDebug() << "Данные студента успешно перезаписаны!";
    }
}

void sql_tools::Delete_card(int id)
{
    QSqlQuery query_delete = QSqlQuery(db);

    QString str_query = "DELETE FROM \"Список студентов\"";
    str_query += "WHERE id = " + QString::number(id);

    qDebug() << str_query;

    if(!query_delete.exec(str_query))
    {
        qDebug() << query_delete.lastError().databaseText();
        qDebug() << query_delete.lastError().driverText();
        return;
    }
    else
    {
        qDebug() << "Студент успешно удален!";
    }
}

sql_tools::sql_tools()
{

}
