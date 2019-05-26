QT += gui qml quick 3dcore 3drender 3dquick 3dinput 3dextras
QT += widgets quick quickwidgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    ai.cpp \
    ball.cpp \
    camflyingaround.cpp \
    collisions.cpp \
    racket.cpp \
    racketanimation1.cpp \
    racketanimation2.cpp \
    racketanimation2_copy.cpp \
    scene.cpp \
    game.cpp \
    table.cpp \
    time.cpp

HEADERS += \
    ai.hpp \
    ball.hpp \
    camflyingaround.hpp \
    collisions.hpp \
    racket.hpp \
    racketanimation1.hpp \
    racketanimation2.hpp \
    racketanimation2_copy.hpp \
    stdafx.hpp \
    scene.hpp \
    game.hpp \ \
    table.hpp \
    time.hpp

PRECOMPILED_HEADER = stdafx.hpp

RESOURCES += \
    game.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
