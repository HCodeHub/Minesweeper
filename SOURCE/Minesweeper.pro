QT       += core #gui

RC_ICONS += Image/Icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Graphics.cpp \
    MemeField.cpp \
    Mouse.cpp \
    RectI.cpp \
    SelectButton.cpp \
    Setting.cpp \
    Sprite.cpp \
    SpriteCodex.cpp \
    Vei2.cpp \
    main.cpp \
    Widget.cpp

HEADERS += \
    Graphics.h \
    MemeField.h \
    Mouse.h \
    RectI.h \
    SelectButton.h \
    Setting.h \
    SpriteCodex.h \
    Vei2.h \
    Widget.h

#FORMS += \    Widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    minesweeper.qmodel

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
