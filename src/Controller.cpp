
#include <QDebug>

#include <include/Controller.h>

void Controller::init_monitor(int domain){
    qDebug()<<domain;
}

void Controller::init_monitor(QString locators){
    qDebug()<<locators;
}
