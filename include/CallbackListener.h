#ifndef CALLBACKLISTENER_H
#define CALLBACKLISTENER_H

#include <QObject>

class Engine;

class CallbackListener : public QObject
{
    Q_OBJECT

public:

    CallbackListener(Engine* engine);

    void new_callback();

signals:
    void new_callback_signal();

public slots:
    void new_callback_slot();

protected:
    Engine* engine_;
};

#endif // CALLBACKLISTENER_H
