TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    screen.cpp \
    particle.cpp \
    swarm.cpp

# Setting access up to the SDL (Simple Directmedia Layer) library. -jmor
# Adding libraries path: -L[Directory path of "lib" folder] -lSDL2
LIBS += -L C:/Users/otero/Documents/SDL2-2.0.5/x86_64-w64-mingw32/lib -lSDL2
#LIBS += -L C:/Users/otero/Documents/SDL2-2.0.5/x86_64-w64-mingw32/lib -lSDL2main -lSDL2
# Adding include path: [Directory of "include"]
INCLUDEPATH += C:/Users/otero/Documents/SDL2-2.0.5/x86_64-w64-mingw32/include/SDL2

HEADERS += \
    screen.h \
    particle.h \
    swarm.h
