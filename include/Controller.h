#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(
            QObject *parent = nullptr)
        : QObject(parent)
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

    void updateAvailableEntityIds(QString entityKind, QString entityModelId);

private:
};

#endif // CONTROLLER_H
