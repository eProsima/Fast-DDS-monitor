#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>

class Engine;

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(
            Engine* engine,
            QObject *parent = nullptr)
        : QObject(parent)
        , engine_(engine)
    {
    }

Q_SIGNALS:

public slots:

    void init_monitor(int domain);

    void init_monitor(QString locators);

    void host_click(QString id);
    void user_click(QString id);
    void process_click(QString id);

    void domain_click(QString id);
    void topic_click(QString id);

    void participant_click(QString id);
    void endpoint_click(QString id);
    void locator_click(QString id);

    void refresh_click();

    void update_available_entity_ids(
            QString entity_kind,
            QString entity_model_id);

    void add_statistics_data(
            QString data_kind,
            QString source_entity_id,
            QString target_entity_id,
            quint16 bins,
            quint64 startTime,
            bool startTimeDefault,
            quint64 endTime,
            bool endTimeDefault,
            QString statisticKind);

protected:
    // Engine object
    Engine* engine_;
};

#endif // CONTROLLER_H
