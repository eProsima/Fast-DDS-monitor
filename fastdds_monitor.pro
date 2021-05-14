QT += charts qml quick

CONFIG += c++14
CONFIG += qtquickcompiler

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/backend/Listener.cpp \
        src/statistics/StatisticsData.cpp \
        src/Controller.cpp \
        src/backend/SyncBackendConnection.cpp \
        src/backend/backend_utils.cpp \
        src/model/ListItem.cpp \
        src/model/dds/ParticipantModelItem.cpp \
        src/model/dds/EndpointModelItem.cpp \
        src/model/logical/TopicModelItem.cpp \
        src/model/physical/ProcessModelItem.cpp \
        src/model/ListModel.cpp \
        src/model/SubListedListModel.cpp \
        src/main.cpp \
        src/model/tree/TreeItem.cpp \
        src/model/tree/TreeModel.cpp \
        src/utils.cpp \
        src/Engine.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += include

HEADERS += \
        include/fastdds-monitor/Controller.h \
        include/fastdds-monitor/backend/Callback.h \
        include/fastdds-monitor/backend/Listener.h \
        include/fastdds-monitor/backend/SyncBackendConnection.h \
        include/fastdds-monitor/backend/backend_types.h \
        include/fastdds-monitor/model/EntityContainerModelItem.h \
        include/fastdds-monitor/model/statistics/EntityItem.h \
        include/fastdds-monitor/model/dds/LocatorModelItem.h \
        include/fastdds-monitor/model/model_types.h \
        include/fastdds-monitor/utils.h \
        include/fastdds-monitor/backend/backend_utils.h \
        include/fastdds-monitor/model/dds/ParticipantModelItem.h \
        include/fastdds-monitor/model/dds/EndpointModelItem.h \
        include/fastdds-monitor/model/logical/DomainModelItem.h \
        include/fastdds-monitor/model/logical/TopicModelItem.h \
        include/fastdds-monitor/model/physical/HostModelItem.h \
        include/fastdds-monitor/model/physical/UserModelItem.h \
        include/fastdds-monitor/model/physical/ProcessModelItem.h \
        include/fastdds-monitor/model/ListModel.h \
        include/fastdds-monitor/model/ListItem.h \
        include/fastdds-monitor/model/SubListedListModel.h \
        include/fastdds-monitor/model/SubListedListItem.h \
        include/fastdds-monitor/Engine.h \
        include/fastdds-monitor/model/tree/TreeModel.h \
        include/fastdds-monitor/model/tree/TreeItem.h \
        include/fastdds-monitor/statistics/StatisticsData.h

DISTFILES += \
    qml/*

# Link to the Fast DDS Statistics Backend Complex Mock library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../install/fastdds-monitor/lib/release/ -lcomplex-backend-mock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../install/fastdds-monitor/lib/debug/ -lcomplex-backend-mock
else:unix: LIBS += -L$$PWD/../../install/fastdds-monitor/lib/ -lcomplex-backend-mock

INCLUDEPATH += $$PWD/../../install/fastdds-monitor
DEPENDPATH += $$PWD/../../install/fastdds-monitor

# Link to the Fast DDS Statistics Backend library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../install/fastdds-statistics-backend/lib/release/ -lfastdds-statistics-backend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../install/fastdds-statistics-backend/lib/debug/ -lfastdds-statistics-backend
else:unix: LIBS += -L$$PWD/../../install/fastdds-statistics-backend/lib/ -lfastdds-statistics-backend

INCLUDEPATH += $$PWD/../../install/fastdds-statistics-backend/include
DEPENDPATH += $$PWD/../../install/fastdds-statistics-backend/include
