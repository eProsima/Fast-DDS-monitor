
#include <QDebug>

#include <include/Controller.h>
#include <include/Engine.h>

void Controller::init_monitor(int domain)
{
    qDebug() << "click init monitor int" << domain;
    Engine::get_instance()->init_monitor(domain);
}

void Controller::init_monitor(QString locators)
{
    qDebug() << "init monitor string" << locators;
    Engine::get_instance()->init_monitor(locators);
}

void Controller::host_click(QString id)
{
    qDebug() << "host click " << id;
}

void Controller::user_click(QString id)
{
    qDebug() << "user click " << id;
}

void Controller::process_click(QString id)
{
    qDebug() << "process click " << id;
}

void Controller::domain_click(QString id)
{
    qDebug() << "domain click " << id;
}

void Controller::topic_click(QString id)
{
    qDebug() << "topic click " << id;
}

void Controller::participant_click(QString id)
{
    qDebug() << "participant click " << id;
    Engine::get_instance()->fill_dds_qos(backend::models_id_to_backend_id(id));
}

void Controller::endpoint_click(QString id)
{
    qDebug() << "endpoint click " << id;
    Engine::get_instance()->fill_dds_qos(backend::models_id_to_backend_id(id));
}
