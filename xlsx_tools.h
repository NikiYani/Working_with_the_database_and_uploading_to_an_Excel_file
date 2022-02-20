#ifndef XLSX_TOOLS_H
#define XLSX_TOOLS_H

#include "xlsxdocument.h"
#include <QTableWidget>

class xlsx_tools
{
public:
    xlsx_tools();
    void Export_file(QString nameFileForSaving, QTableWidget &table);
};

#endif // XLSX_TOOLS_H
