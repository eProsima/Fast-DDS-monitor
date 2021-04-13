
#include <QDebug>

#include <include/Controller.h>
#include <include/Engine.h>

void Controller::init_monitor(int domain)
{
    engine_->init_monitor(domain);
}

void Controller::init_monitor(QString locators)
{
    engine_->init_monitor(locators);
}

void Controller::host_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::HOST);
}

void Controller::user_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::USER);
}

void Controller::process_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::PROCESS);
}

void Controller::domain_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::DOMAIN);
}

void Controller::topic_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::TOPIC);
}

void Controller::participant_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::PARTICIPANT);
}

void Controller::endpoint_click(QString id)
{
    // WARNING: we do not know if it is DataWriter or DataReader
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::DATAWRITER);
}

void Controller::locator_click(QString id)
{
    engine_->entity_clicked(backend::models_id_to_backend_id(id), backend::EntityKind::LOCATOR);
}

void Controller::update_available_entity_ids(
        QString entity_kind,
        QString entity_model_id)
{
    engine_->onSelectedEntityKind(backend::stringToEntityKind(entityKind), entityModelId);
}

void Controller::refresh_click()
{
    engine_->refresh_engine();
}

void Controller::add_statistics_data(
        QString data_kind,
        QString source_entity_id,
        QString target_entity_id,
        quint16 bins,
        quint64 start_time,
        bool start_time_default,
        quint64 end_time,
        bool end_time_default,
        QString statistic_kind)
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


    engine_->onAddStatisticsDataSeries(
                backend::stringToDataKind(dataKind),
                backend::models_id_to_backend_id(sourceEntityId),
                backend::models_id_to_backend_id(targetEntityId),
                bins,
                start_time,
                start_time_default,
                end_time,
                end_time_default,
                backend::string_to_statistic_kind(statistic_kind));
}
