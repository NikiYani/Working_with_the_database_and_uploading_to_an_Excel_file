QT       += core gui sql gui-private

include(QtXlsx\src\xlsx\qtxlsx.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 c++14 c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card_of_student.cpp \
    main.cpp \
    list_of_group_students.cpp \
    sql_tools.cpp \
    style_sheet_preset.cpp \
    xlsx_tools.cpp

HEADERS += \
    card_of_student.h \
    list_of_group_students.h \
    sql_tools.h \
    style_sheet_preset.h \
    xlsx_tools.h

FORMS += \
    card_of_student.ui \
    list_of_group_students.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
