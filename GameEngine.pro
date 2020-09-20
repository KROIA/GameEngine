QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# SFML stuff
sfml_version      = "2.5.1"

sfml_basePath     = "../../SFML-$$sfml_version"
sfml_includePath  = "$$sfml_basePath/include"
sfml_binPath      = "$$sfml_basePath/bin"
sfml_libs_debug   = "$$sfml_binPath/Debug/lib/libsfml-audio-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-graphics-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-main-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-network-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-system-d.a" \
                    "$$sfml_binPath/Debug/lib/libsfml-window-d.a"

sfml_libs_release = "$$sfml_binPath/Release/lib/libsfml-audio.a" \
                    "$$sfml_binPath/Release/lib/libsfml-graphics.a" \
                    "$$sfml_binPath/Release/lib/libsfml-main.a" \
                    "$$sfml_binPath/Release/lib/libsfml-network.a" \
                    "$$sfml_binPath/Release/lib/libsfml-system.a" \
                    "$$sfml_binPath/Release/lib/libsfml-window.a"


CONFIG(release, debug|release): sfml_libs = $$sfml_libs_release
CONFIG(debug, debug|release):   sfml_libs = $$sfml_libs_debug
# End SFML stuff
srcPath = src
incPath = inc

INCLUDEPATH += $$sfml_includePath \
               $$incPath \
               $$incPath/GameObjects \
               $$incPath/base \
               $$incPath/GameObjects/base
DEPENDPATH  += $$sfml_includePath
LIBS        += $$sfml_libs



SOURCES += \
    $$srcPath/base/EngineMisc.cpp \
    $$srcPath/base/physics.cpp \
    $$srcPath/base/timer.cpp \
    $$srcPath/GameEngine.cpp \
    $$srcPath/GameObjects/base/collider.cpp \
    $$srcPath/GameObjects/base/controller.cpp \
    $$srcPath/GameObjects/base/painter.cpp \
    $$srcPath/GameObjects/GameObject.cpp \
    main.cpp \
    mainwindow.cpp



HEADERS += \
    $$incPath/base/EngineMisc.h \
    $$incPath/base/physics.h \
    $$incPath/GameEngine.h \
    $$incPath/GameObjects/base/collider.h \
    $$incPath/GameObjects/base/controller.h \
    $$incPath/GameObjects/base/painter.h \
    $$incPath/GameObjects/GameObject.h \
    $$incPath/base/timer.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
