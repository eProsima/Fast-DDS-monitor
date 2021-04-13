
#include <include/CallbackListener.h>
#include <include/Engine.h>

CallbackListener::CallbackListener(Engine* engine)
    : engine_(engine)
{
}

void CallbackListener::new_callback()
{
    emit new_callback_signal();
}

void CallbackListener::new_callback_slot()
{
    engine_->process_callback_queue();
}
