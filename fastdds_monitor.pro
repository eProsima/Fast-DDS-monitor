QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/model/logical/ParticipantModelItem.cpp \
        src/model/logical/EndpointModelItem.cpp \
        src/model/logical/TopicModelItem.cpp \
        src/model/physical/HostModelItem.cpp \
        src/model/physical/UserModelItem.cpp \
        src/model/physical/ProcessModelItem.cpp \
        src/model/ListModel.cpp \
        src/model/SubListedListModel.cpp \
        src/main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/model/logical/ParticipantModelItem.h \
    include/model/logical/EndpointModelItem.h \
    include/model/logical/TopicModelItem.h \
    include/model/physical/HostModelItem.h \
    include/model/physical/UserModelItem.h \
    include/model/physical/ProcessModelItem.h \
    include/model/ListModel.h \
    include/model/ListItem.h \
    include/model/SubListedListModel.h \
    include/model/SubListedListItem.h
