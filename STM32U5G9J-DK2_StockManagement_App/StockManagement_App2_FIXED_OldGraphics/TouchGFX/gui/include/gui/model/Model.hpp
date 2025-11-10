#ifndef MODEL_HPP
#define MODEL_HPP


extern "C"
{
	#include "../../../../../X-CUBE-NFC6/Target/nfc_messages.h"
	#include "FreeRTOS.h"
	#include "queue.h"
	#include "task.h"
}

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
