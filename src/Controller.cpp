
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

void Controller::updateAvailableEntityIds(QString entityKind, QString entityModelId)
{
    Engine::get_instance()->onSelectedEntityKind(backend::stringToEntityKind(entityKind), entityModelId);
}
