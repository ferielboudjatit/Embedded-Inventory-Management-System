#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <gui/model/Model.hpp>

class FrontendHeap;
using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }

    // Screen transition methods for each NFC state
    void gotoScanBadgeScreenNoTransition();
    void gotoBoardScannedScreenNoTransition();
    void gotoBadgeScannedScreenNoTransition();
    void gotoBoardEnteredScreenNoTransition();
    void gotoBoardGotOutScreenNoTransition();
    void gotoScanBoardBeforeScreenNoTransition();
    void gotoScanBadgeBeforeScreenNoTransition();
    void gotoScanBoardSlowlyScreenNoTransition();
    void gotoTransmissionErrorScreenNoTransition();
    // Method to handle NFC message and transition to appropriate screen
    void handleNFCMessage(NFCtask_messages_t nfc_message);
private:
    //touchgfx::Callback<FrontendApplicationBase> transitionCallback;
    //FrontendHeap& frontendHeap;
    //Model& model;
    // Implementation methods for screen transitions
    void gotoScanBadgeScreenNoTransitionImpl();
    void gotoBoardScannedScreenNoTransitionImpl();
    void gotoBadgeScannedScreenNoTransitionImpl();
    void gotoBoardEnteredScreenNoTransitionImpl();
    void gotoBoardGotOutScreenNoTransitionImpl();
    void gotoScanBoardBeforeScreenNoTransitionImpl();
    void gotoScanBadgeBeforeScreenNoTransitionImpl();
    void gotoScanBoardSlowlyScreenNoTransitionImpl();
    void gotoTransmissionErrorScreenNoTransitionImpl();
};

#endif // FRONTENDAPPLICATION_HPP
