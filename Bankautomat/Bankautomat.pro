QT += core gui widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    DLLs\DLLSerialPort\DLLSerialPort\dllserialport.cpp

HEADERS += \
    mainwindow.h \
    DLLs\DLLSerialPort\DLLSerialPort\dllserialport.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/DLLs/DLLPinCode/build-DLLPinCode-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug
INCLUDEPATH += $$PWD/DLLs/DLLSerialPort/build-DLLSerialPort-Desktop_Qt_5_15_1_MinGW_32_bit-Debug
DEPENDPATH += $$PWD/DLLs/DLLPinCode/build-DLLPinCode-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug
DEPENDPATH += $$PWD/DLLs/DLLSerialPort/build-DLLSerialPort-Desktop_Qt_5_15_1_MinGW_32_bit-Debug
