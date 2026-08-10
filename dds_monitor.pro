QT += charts qml quick

CONFIG += c++14
CONFIG += qtquickcompiler

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/backend/backend_utils.cpp \
        src/backend/Listener.cpp \
        src/backend/SyncBackendConnection.cpp \
        src/Controller.cpp \
        src/Engine.cpp \
        src/io/csv.cpp \
        src/main.cpp \
        src/model/alerts/AlertListModel.cpp \
        src/model/alerts/AlertListItem.cpp \
        src/model/dds/EndpointModelItem.cpp \
        src/model/dds/ParticipantModelItem.cpp \
        src/model/info/InfoModel.cpp \
        src/model/ListItem.cpp \
        src/model/ListModel.cpp \
        src/model/logical/TopicModelItem.cpp \
        src/model/physical/ProcessModelItem.cpp \
        src/model/statistics/EntityItem.cpp \
        src/model/SubListedListModel.cpp \
        src/model/tree/StatusTreeItem.cpp \
        src/model/tree/StatusTreeModel.cpp \
        src/model/tree/TreeItem.cpp \
        src/model/tree/TreeModel.cpp \
        src/statistics/DataChartBox.cpp \
        src/statistics/DataModel.cpp \
        src/statistics/dynamic/DynamicDataChartBox.cpp \
        src/statistics/dynamic/DynamicStatisticsData.cpp \
        src/statistics/historic/HistoricDataChartBox.cpp \
        src/statistics/historic/HistoricStatisticsData.cpp \
        src/statistics/StatisticsData.cpp \
        src/utils.cpp

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
    include/dds_monitor/backend/backend_types.h \
    include/dds_monitor/backend/backend_utils.h \
    include/dds_monitor/backend/Callback.h \
    include/dds_monitor/backend/Listener.h \
    include/dds_monitor/backend/SyncBackendConnection.h \
    include/dds_monitor/Controller.h \
    include/dds_monitor/Engine.h \
    include/dds_monitor/io/csv.h \
    include/dds_monitor/model/dds/EndpointModelItem.h \
    include/dds_monitor/model/dds/LocatorModelItem.h \
    include/dds_monitor/model/dds/ParticipantModelItem.h \
    include/dds_monitor/model/EntityContainerModelItem.h \
    include/dds_monitor/model/info/InfoModel.h \
    include/dds_monitor/model/ListItem.h \
    include/dds_monitor/model/ListModel.h \
    include/dds_monitor/model/logical/DomainModelItem.h \
    include/dds_monitor/model/logical/TopicModelItem.h \
    include/dds_monitor/model/model_types.h \
    include/dds_monitor/model/physical/HostModelItem.h \
    include/dds_monitor/model/physical/ProcessModelItem.h \
    include/dds_monitor/model/physical/UserModelItem.h \
    include/dds_monitor/model/statistics/EntityItem.h \
    include/dds_monitor/model/SubListedListItem.h \
    include/dds_monitor/model/SubListedListModel.h \
    include/dds_monitor/model/tree/StatusTreeModel.h \
    include/dds_monitor/model/tree/StatusTreeItem.h \
    include/dds_monitor/model/tree/TreeItem.h \
    include/dds_monitor/model/tree/TreeModel.h \
    include/dds_monitor/statistics/DataChartBox.h \
    include/dds_monitor/statistics/DataModel.h \
    include/dds_monitor/statistics/dynamic/DynamicDataChartBox.h \
    include/dds_monitor/statistics/dynamic/DynamicStatisticsData.h \
    include/dds_monitor/statistics/historic/HistoricDataChartBox.h \
    include/dds_monitor/statistics/historic/HistoricStatisticsData.h \
    include/dds_monitor/statistics/StatisticsData.h \
    include/dds_monitor/utils.h

DISTFILES += \
    qml/*

# Link to the Complex Backend Mock (uncomment to link against the mock)
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../install/dds_monitor/lib/release/ -lcomplex-backend-mock
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../install/dds_monitor/lib/debug/ -lcomplex-backend-mock
#else:unix: LIBS += -L$$PWD/../../install/dds_monitor/lib/ -lcomplex-backend-mock

#INCLUDEPATH += $$PWD/../../install/dds_monitor/include
#DEPENDPATH += $$PWD/../../install/dds_monitor/include

# Link to the Fast DDS Statistics Backend library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../install/fastdds_statistics_backend/lib/release/ -lfastdds_statistics_backend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../install/fastdds_statistics_backend/lib/debug/ -lfastdds_statistics_backend
else:unix: LIBS += -L$$PWD/../../install/fastdds_statistics_backend/lib/ -lfastdds_statistics_backend

INCLUDEPATH += $$PWD/../../install/fastdds_statistics_backend/include
DEPENDPATH += $$PWD/../../install/fastdds_statistics_backend/include

# Link to the Fast DDS library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../install/fastdds/lib/release/ -lfastdds
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../install/fastdds/lib/debug/ -lfastdds
else:unix: LIBS += -L$$PWD/../../install/fastdds/lib/ -lfastdds

INCLUDEPATH += $$PWD/../../install/fastdds/include
DEPENDPATH += $$PWD/../../install/fastdds/include

# Link to the Fast CDR library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../install/fastcdr/lib/release/ -lfastcdr
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../install/fastcdr/lib/debug/ -lfastcdr
else:unix: LIBS += -L$$PWD/../../install/fastcdr/lib/ -lfastcdr

INCLUDEPATH += $$PWD/../../install/fastcdr/include
DEPENDPATH += $$PWD/../../install/fastcdr/include

# Link to the DDS Monitor includes
INCLUDEPATH += $$PWD/../../install/dds_monitor/include
DEPENDPATH += $$PWD/../../install/dds_monitor/include


