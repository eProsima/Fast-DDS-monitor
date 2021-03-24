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

    Q_INVOKABLE void host_click(QString id);
    Q_INVOKABLE void user_click(QString id);
    Q_INVOKABLE void process_click(QString id);

    Q_INVOKABLE void domain_click(QString id);
    Q_INVOKABLE void topic_click(QString id);

    Q_INVOKABLE void participant_click(QString id);
    Q_INVOKABLE void endpoint_click(QString id);
    Q_INVOKABLE void locator_click(QString id);

    Q_INVOKABLE void updateAvailableEntityIds(QString entityKind, QString entityModelId);

private:
};

#endif // CONTROLLER_H
