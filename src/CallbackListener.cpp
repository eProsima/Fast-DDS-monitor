
#include <include/CallbackListener.h>
#include <include/Engine.h>

void CallbackListener::new_callback()
{
    emit new_callback_signal();
}

void CallbackListener::new_callback_slot()
{
    Engine::get_instance()->process_callback_queue();
}
