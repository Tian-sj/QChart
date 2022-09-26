QT += core gui widgets
QT += charts

CONFIG += c++17

win32-msvc*:QMAKE_CXXFLAGS += /utf-8
# QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""

HEADERS += \
    src/dialog.h \
    src/Tian.h

SOURCES += \
    src/dialog.cpp \
    src/Tian.cpp \
    src/main.cpp

FORMS += \
    src/dialog.ui \
    src/Tian.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target