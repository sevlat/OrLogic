#-------------------------------------------------
#
# Project created by QtCreator 2012-09-03T23:09:37
#
#-------------------------------------------------

QT       -= core gui

TARGET = SiLib
TEMPLATE = lib

CONFIG += staticlib

OBJECTS_DIR =../../../../_Output/Qt/SiLib

INCLUDEPATH += ../../../

DESTDIR =../../../../Bin/Qt

DEFINES += SILIB_LIBRARY

SOURCES += \
    ../../Z.cpp \
    ../../Stream.cpp \
    ../../stdafx.cpp \
    ../../StationWrite.cpp \
    ../../StationTypes.cpp \
    ../../StationRead.cpp \
    ../../Station.cpp \
    ../../SiTypes.cpp \
    ../../PortEmulator.cpp \
    ../../MsgDescribe.cpp \
    ../../Errors.cpp \
    ../../Crc.cpp \
    ../../ComPort.cpp \
    ../../Commands.cpp \
    ../../CommandCode.cpp \
    ../../CmdVisitor.cpp \
    ../../CmdSerialize.cpp \
    ../../CmdItemSerialize.cpp \
    ../../CmdDataDescribe.cpp \
    ../../ByteBufStream.cpp \
    ../../BufferedStream.cpp

HEADERS += \
    ../../Utils.h \
    ../../Types.h \
    ../../Stream.h \
    ../../stdafx.h \
    ../../StationWrite.h \
    ../../StationTypes.h \
    ../../StationTime.h \
    ../../StationRead.h \
    ../../Station.h \
    ../../SiTypes.h \
    ../../SerialTypes.h \
    ../../PortEmulator.h \
    ../../Log.h \
    ../../I_ComPort.h \
    ../../Fwd.h \
    ../../External.h \
    ../../Errors.h \
    ../../Crc.h \
    ../../crc529.h \
    ../../ComPort.h \
    ../../Commands.h \
    ../../CommandCode.h \
    ../../CmdVisitor.h \
    ../../CmdSerializeImpl.h \
    ../../CmdSerialize.h \
    ../../CmdItemSerialize.h \
    ../../CmdDataSerializeSpec.h \
    ../../CmdDataSerializeImpl.h \
    ../../CmdDataSerialize.h \
    ../../CmdDataDescribe.h \
    ../../CmdData.h \
    ../../ByteBufStream.h \
    ../../ByteBuffer.h \
    ../../BufferedStream.h \
    ../../Utils.h












