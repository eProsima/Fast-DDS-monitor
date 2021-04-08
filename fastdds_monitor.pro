QT += charts qml quick

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/backend/Listener.cpp \
        src/statistics/StatisticsData.cpp \
        src/model/EntityItem.cpp \
        src/Controller.cpp \
        src/backend/AsyncBackendConnection.cpp \
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

HEADERS += \
        include/Controller.h \
        include/backend/AsyncBackendConnection_copy.h \
        include/backend/Callback.h \
        include/backend/Listener.h \
        include/backend/SyncBackendConnection.h \
        include/backend/backend_types.h \
        include/model/EntityContainerModelItem.h \
        include/model/EntityItem.h \
        include/model/dds/LocatorModelItem.h \
        include/model/model_types.h \
        include/utils.h \
        include/backend/backend_utils.h \
        include/model/dds/ParticipantModelItem.h \
        include/model/dds/EndpointModelItem.h \
        include/model/logical/DomainModelItem.h \
        include/model/logical/TopicModelItem.h \
        include/model/physical/HostModelItem.h \
        include/model/physical/UserModelItem.h \
        include/model/physical/ProcessModelItem.h \
        include/model/ListModel.h \
        include/model/ListItem.h \
        include/model/SubListedListModel.h \
        include/model/SubListedListItem.h \
        include/Engine.h \
        include/model/tree/TreeModel.h \
        include/model/tree/TreeItem.h \
        include/statistics/StatisticsData.h \
        json.hpp

DISTFILES += \
    qml/*

# This path remains when the project is build with colcon by downloadinf fastdds-monitor.repos
INCLUDEPATH += $$PWD/../../install/fastdds-statistics-backend/include
DEPENDPATH += $$PWD/../../install/fastdds-statistics-backend/include

# Static Mock
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/fastdds-monitor/mock/static_mock/ -lStaticMock
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/fastdds-monitor/mock/static_mock/ -lStaticMockd
#else:unix: LIBS += -L$$PWD/../../build/fastdds-monitor/mock/static_mock/ -lStaticMock

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/static_mock/libStaticMock.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/static_mock/libStaticMockd.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/static_mock/StaticMock.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/static_mock/StaticMockd.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/static_mock/libStaticMock.a

# Complex Mock
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/fastdds-monitor/mock/complex_mock/ -lComplexMock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/fastdds-monitor/mock/complex_mock/ -lComplexMockd
else:unix: LIBS += -L$$PWD/../../build/fastdds-monitor/mock/complex_mock/ -lComplexMock

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/complex_mock/libComplexMock.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/complex_mock/libComplexMockd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/complex_mock/ComplexMock.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/complex_mock/ComplexMockd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../build/fastdds-monitor/mock/complex_mock/libComplexMock.a
