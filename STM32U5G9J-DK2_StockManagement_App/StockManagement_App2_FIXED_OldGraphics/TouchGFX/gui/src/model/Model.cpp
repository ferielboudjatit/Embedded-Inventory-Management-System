#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Application.hpp>


extern "C"
{
    QueueHandle_t nfcMessageQueue  = NULL;
}

//model class constructor, initializes the pointer modelListener to 0 (null pointer) when a Model object is created. This is important to avoid having an uninitialized pointer, which could lead to undefined behavior if accessed before being set.

Model::Model() : modelListener(0)
{
    nfcMessageQueue = xQueueCreate(5, sizeof(NFCtask_messages_t)); //xQueueCreate is defined as xQueueGenericCreate with type = 0
}

// the place where the GUI Task becomes aware of the new data to be shown in the UI, called every frame

void Model::tick() 
{
    NFCtask_messages_t NFC_message;
    FrontendApplication& app = static_cast<FrontendApplication&>(*touchgfx::Application::getInstance());

    while (xQueueReceive(nfcMessageQueue, &NFC_message, 0) == pdTRUE) 
    {
        // Get the application instance and cast to FrontendApplication (same is done in ScreenViewBase.hpp source codes)
        //FrontendApplication& application() {return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());}

        //FrontendApplication& app = static_cast<FrontendApplication&>(*touchgfx::Application::getInstance());
    	app.handleNFCMessage(NFC_message);
        
        //vTaskDelay(pdMS_TO_TICKS(200));
    }
}
