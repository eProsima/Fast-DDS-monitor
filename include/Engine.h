#ifndef ENGINE_H
#define ENGINE_H

#include <QQmlApplicationEngine>

#include <include/backend/SyncBackendConnection.h>
#include <include/model/SubListedListModel.h>

#include <include/model/tree/TreeModel.h>

class Engine : public QQmlApplicationEngine
{
public:
    Engine();

    void enable();

private:
    models::ListModel* participantsModel;
    models::ListModel* physicalModel;
    models::ListModel* logicalModel;

    models::TreeModel* qosModel;

    backend::SyncBackendConnection backend_connection;
};

#endif // ENGINE_H
