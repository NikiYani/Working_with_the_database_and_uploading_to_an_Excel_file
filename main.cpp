#include "list_of_group_students.h"
#include "sql_tools.h"
#include "QFile"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    sql_tools *sql = new sql_tools;

    QString buffer;
    QString filename = "./config/config_for_creating_connection_with_db.txt";
    QStringList array_config_for_db;
    QFile file(filename);
    QString result_connect;

    if(file.open(QIODevice::ReadOnly)){
        buffer.append(file.readAll());
    }

    array_config_for_db.append(buffer.split(','));

    if(array_config_for_db[5] == "local"){
        sql->Create_connection_local_db(array_config_for_db);
    }

    sql->Delete_a_list();
    sql->Create_a_list();

    delete sql;

    List_of_group_students w;
    w.set_style_sheet();
    w.Gen_table();
    w.show();
    return a.exec();
}
