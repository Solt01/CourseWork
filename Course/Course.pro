QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addattendancesdialog.cpp \
    adddisciplinedialog.cpp \
    addgroupdialog.cpp \
    addlecturerdialog.cpp \
    addprogressdialog.cpp \
    addscorestudentdialog.cpp \
    addstudentdialog.cpp \
    addtestgroupdialog.cpp \
    addtestsdialog.cpp \
    attendancewindow.cpp \
    connectdbdialog.cpp \
    editdisciplinedialog.cpp \
    editgroupdialog.cpp \
    editlecturerdialog.cpp \
    editprogressdialog.cpp \
    editscorestudentdialog.cpp \
    editstudentdialog.cpp \
    edittestgroupdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    progressmainwindow.cpp \
    studenttestwindow.cpp \
    testgroupwindow.cpp

HEADERS += \
    addattendancesdialog.h \
    adddisciplinedialog.h \
    addgroupdialog.h \
    addlecturerdialog.h \
    addprogressdialog.h \
    addscorestudentdialog.h \
    addstudentdialog.h \
    addtestgroupdialog.h \
    addtestsdialog.h \
    attendancewindow.h \
    connectdbdialog.h \
    editdisciplinedialog.h \
    editgroupdialog.h \
    editlecturerdialog.h \
    editprogressdialog.h \
    editscorestudentdialog.h \
    editstudentdialog.h \
    edittestgroupdialog.h \
    mainwindow.h \
    progressmainwindow.h \
    studenttestwindow.h \
    testgroupwindow.h

FORMS += \
    addattendancesdialog.ui \
    adddisciplinedialog.ui \
    addgroupdialog.ui \
    addlecturerdialog.ui \
    addprogressdialog.ui \
    addscorestudentdialog.ui \
    addstudentdialog.ui \
    addtestgroupdialog.ui \
    addtestsdialog.ui \
    attendancewindow.ui \
    connectdbdialog.ui \
    editdisciplinedialog.ui \
    editgroupdialog.ui \
    editlecturerdialog.ui \
    editprogressdialog.ui \
    editscorestudentdialog.ui \
    editstudentdialog.ui \
    edittestgroupdialog.ui \
    mainwindow.ui \
    progressmainwindow.ui \
    studenttestwindow.ui \
    testgroupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
