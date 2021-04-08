#ifndef CALLBACKLISTENER_H
#define CALLBACKLISTENER_H

#include <QObject>

class CallbackListener : public QObject
{
    Q_OBJECT

public:
    void new_callback();

signals:
    void new_callback_signal();

public slots:
    void new_callback_slot();
};

#endif // CALLBACKLISTENER_H
