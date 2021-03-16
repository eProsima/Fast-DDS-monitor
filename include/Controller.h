#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr):QObject(parent)
    {}

    Q_INVOKABLE void init_monitor(int domain);

    Q_INVOKABLE void init_monitor(QString locators);

private:
};

#endif // CONTROLLER_H
