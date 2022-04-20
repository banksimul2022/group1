QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DLLs/DLLSerialPort/DLLSerialPort/dllserialport.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DLLs/DLLSerialPort/DLLSerialPort/DLLSerialPort_global.h \
    DLLs/DLLSerialPort/DLLSerialPort/dllserialport.h \
    mainwindow.h /
    DLLs/DLLSerialPort/DLLSerialPort/dllserialport.h
    DLLs/DLLPinCode/DLLPinCode/kirjautuminen.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/DLLs/DLLSerialPort/build-DLLSerialPort-Desktop_Qt_5_15_1_MinGW_32_bit-Debug/ -llibDLLSerialPort.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/DLLs/DLLSerialPort/build-DLLSerialPort-Desktop_Qt_5_15_1_MinGW_32_bit-Debug/ -llibDLLSerialPort.dlld
else:unix: LIBS += -L$$PWD/DLLs/DLLSerialPort/build-DLLSerialPort-Desktop_Qt_5_15_1_MinGW_32_bit-Debug/ -llibDLLSerialPort.dll
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/DLLs/DLLPinCode/build-DLLPinCode-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/release/ -lDLLPinCode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/DLLs/DLLPinCode/build-DLLPinCode-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug/ -lDLLPinCode
else:unix: LIBS += -L$$PWD/DLLs/DLLPinCode/build-DLLPinCode-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/ -lDLLPinCode

INCLUDEPATH += $$PWD/DLLs/DLLPinCode/build-DLLPinCode-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug
INCLUDEPATH += $$PWD/DLLs/DLLSerialPort/build-DLLSerialPort-Desktop_Qt_5_15_1_MinGW_32_bit-Debug
DEPENDPATH += $$PWD/DLLs/DLLPinCode/build-DLLPinCode-Desktop_Qt_5_15_2_MinGW_32_bit-Debug/debug
DEPENDPATH += $$PWD/DLLs/DLLSerialPort/build-DLLSerialPort-Desktop_Qt_5_15_1_MinGW_32_bit-Debug

DISTFILES += \
    DLLs/DLLSerialPort/DLLSerialPort/CMakeLists.txt
