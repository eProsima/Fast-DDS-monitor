#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlApplicationEngine>

#include <include/backend/SyncBackendConnection.h>
#include <include/model/SubListedListModel.h>

class Engine : public QQmlApplicationEngine
{
public:
    Engine();

    void enable();

private:
    models::ListModel* participantsModel;
    models::ListModel* physicalModel;
    models::ListModel* logicalModel;

    backend::SyncBackendConnection backend_connection;
};

#endif // ENGINE_H
