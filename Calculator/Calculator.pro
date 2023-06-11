QT += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Calculator

TEMPLATE = app

RC_ICONS = calculator.ico

RESOURCES += \
    calculator.qrc

FORMS += \
    calculator.ui

HEADERS += \
    calculator.h

SOURCES += \
    calculator.cpp \
    main.cpp
