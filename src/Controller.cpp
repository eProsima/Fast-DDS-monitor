
#include <QDebug>

#include <include/Controller.h>
#include <include/Engine.h>

void Controller::init_monitor(int domain)
{
    Engine::get_instance()->init_monitor(domain);
}

void Controller::init_monitor(QString locators)
{
    Engine::get_instance()->init_monitor(locators);
}

void Controller::host_click(QString id)
{
    Engine::get_instance()->on_entity_clicked(backend::models_id_to_backend_id(id));
}

void Controller::user_click(QString id)
{
    Engine::get_instance()->on_entity_clicked(backend::models_id_to_backend_id(id));
}

void Controller::process_click(QString id)
{
    Engine::get_instance()->on_entity_clicked(backend::models_id_to_backend_id(id));
}

void Controller::domain_click(QString id)
{
    Engine::get_instance()->on_entity_clicked(backend::models_id_to_backend_id(id));
}

void Controller::topic_click(QString id)
{
    Engine::get_instance()->on_entity_clicked(backend::models_id_to_backend_id(id));
}

void Controller::participant_click(QString id)
{
    Engine::get_instance()->on_dds_entity_clicked(backend::models_id_to_backend_id(id));
}

void Controller::endpoint_click(QString id)
{
    Engine::get_instance()->on_dds_entity_clicked(backend::models_id_to_backend_id(id));
}

void Controller::locator_click(QString id)
{
    Engine::get_instance()->on_dds_entity_clicked(backend::models_id_to_backend_id(id));
}

void Controller::updateAvailableEntityIds(
        QString entityKind,
        QString entityModelId)
{
    Engine::get_instance()->onSelectedEntityKind(backend::stringToEntityKind(entityKind), entityModelId);
}

void Controller::addStatisticsData(
        QString dataKind,
        QString sourceEntityId,
        QString targetEntityId,
        quint16 bins,
        quint64 startTime,
        bool startTimeDefault,
        quint64 endTime,
        bool endTimeDefault,
        QString statisticKind)
{

    qDebug() << "Data Kind: " << dataKind << "\n" <<
                "Source Entity Id: " << sourceEntityId << "\n" <<
                "Target Entity Id: " << targetEntityId << "\n" <<
                "Bins: " << bins << "\n" <<
                "Time Start: " << startTime << "\n" <<
                "Time Start Default: " << startTimeDefault << "\n" <<
                "End Start: " << endTime << "\n" <<
                "End Start Default: " << endTimeDefault << "\n" <<
                "Statistics Kind: " << statisticKind;


    Engine::get_instance()->onAddStatisticsDataSeries(
                backend::stringToDataKind(dataKind),
                backend::models_id_to_backend_id(sourceEntityId),
                backend::models_id_to_backend_id(targetEntityId),
                bins,
                startTime,
                startTimeDefault,
                endTime,
                endTimeDefault,
                backend::stringToStatisticKind(statisticKind));
}
