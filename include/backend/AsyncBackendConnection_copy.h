#ifndef FASTDDS_MONITOR_BACKENDCONNECTION_H
#define FASTDDS_MONITOR_BACKENDCONNECTION_H

#include <QThread>

#include <include/backend/backend_types.h>

namespace backend {

class AsyncBackendConnection  : public QThread
{
public:
    AsyncBackendConnection(QObject *parent = 0);
    ~AsyncBackendConnection();

signals:
    void entity_update(EntityId);
    void new_data(/*TODO*/);

};

} //namespace backend

#endif // FASTDDS_MONITOR_BACKENDCONNECTION_H
