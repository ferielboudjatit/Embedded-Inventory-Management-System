#include <gui/common/FrontendApplication.hpp>
#include <gui/welcome_screen/WelcomeView.hpp>
#include <gui/welcome_screen/WelcomePresenter.hpp>
#include <gui/scanbadge_screen/ScanBadgeView.hpp>
#include <gui/scanbadge_screen/ScanBadgePresenter.hpp>
#include <gui/boardscanned_screen/BoardScannedPresenter.hpp>
#include <gui/boardscanned_screen/BoardScannedView.hpp>
#include <gui/badgescanned_screen/BadgeScannedPresenter.hpp>
#include <gui/badgescanned_screen/BadgeScannedView.hpp>
#include <gui/boardentered_screen/BoardEnteredView.hpp>
#include <gui/boardentered_screen/BoardEnteredPresenter.hpp>
#include <gui/boardgotout_screen/BoardGotOutView.hpp>
#include <gui/boardgotout_screen/BoardGotOutPresenter.hpp>
#include <gui/scanboardb4_screen/ScanBoardB4View.hpp>
#include <gui/scanboardb4_screen/ScanBoardB4Presenter.hpp>
#include <gui/scanbadgeb4_screen/ScanBadgeB4View.hpp>
#include <gui/scanbadgeb4_screen/ScanBadgeB4Presenter.hpp>
#include <gui/scanboardslowly_screen/ScanBoardSlowlyView.hpp>
#include <gui/scanboardslowly_screen/ScanBoardSlowlyPresenter.hpp>
#include <gui/transmissionerror_screen/TransmissionErrorView.hpp>
#include <gui/transmissionerror_screen/TransmissionErrorPresenter.hpp>

#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/hal/HAL.hpp>

#define CALLBACK_CAST(method) static_cast<void (FrontendApplicationBase::*)()>(&FrontendApplication::method)

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{

}

void FrontendApplication::handleNFCMessage(NFCtask_messages_t nfc_message)
{
    switch (nfc_message) {
         case SCAN_BADGE_MESSAGE:
            gotoScanBadgeScreenNoTransition();
            break;
        case BOARD_SCANNED_MESSAGE:
            gotoBoardScannedScreenNoTransition();
            break;
        case BADGE_SCANNED_MESSAGE:
            gotoBadgeScannedScreenNoTransition();
            break;
        case BOARD_ENTERED_MESSAGE:
            gotoBoardEnteredScreenNoTransition();
            break;
        case BOARD_GOTOUT_MESSAGE:
            gotoBoardGotOutScreenNoTransition();
            break;
        case SCAN_BOARD_BEFORE_MESSAGE:
            gotoScanBoardBeforeScreenNoTransition();
            break;
        case SCAN_BADGE_BEFORE_MESSAGE:
            gotoScanBadgeBeforeScreenNoTransition();
            break;
        case RESCAN_BOARD_SLOWLY:
        	gotoScanBoardSlowlyScreenNoTransition();
        	break;
        case TRANSMISSION_ERROR:
        	gotoTransmissionErrorScreenNoTransition();
        	break;
        default:
        	gotoScanBoardScreenNoTransition();
            break;
    }
}

// Scan Badge Screen
void FrontendApplication::gotoScanBadgeScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoScanBadgeScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoScanBadgeScreenNoTransitionImpl()
{
    touchgfx::makeTransition<ScanBadgeView, ScanBadgePresenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Board Scanned Screen
void FrontendApplication::gotoBoardScannedScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoBoardScannedScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoBoardScannedScreenNoTransitionImpl()
{
    touchgfx::makeTransition<BoardScannedView, BoardScannedPresenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}


// Badge Scanned Screen
void FrontendApplication::gotoBadgeScannedScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoBadgeScannedScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoBadgeScannedScreenNoTransitionImpl()
{
    touchgfx::makeTransition<BadgeScannedView, BadgeScannedPresenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Board Entered Screen
void FrontendApplication::gotoBoardEnteredScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoBoardEnteredScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoBoardEnteredScreenNoTransitionImpl()
{
    touchgfx::makeTransition<BoardEnteredView, BoardEnteredPresenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Board Got Out Screen
void FrontendApplication::gotoBoardGotOutScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoBoardGotOutScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoBoardGotOutScreenNoTransitionImpl()
{
    touchgfx::makeTransition<BoardGotoutView, BoardGotoutPresenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Scan Board Before Screen
void FrontendApplication::gotoScanBoardBeforeScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoScanBoardBeforeScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoScanBoardBeforeScreenNoTransitionImpl()
{
    touchgfx::makeTransition<ScanBoardB4View, ScanBoardB4Presenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Scan Badge Before Screen
void FrontendApplication::gotoScanBadgeBeforeScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoScanBadgeBeforeScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoScanBadgeBeforeScreenNoTransitionImpl()
{
    touchgfx::makeTransition<ScanBadgeB4View, ScanBadgeB4Presenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}


// Scan Board Slowly Screen
void FrontendApplication::gotoScanBoardSlowlyScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoScanBoardSlowlyScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoScanBoardSlowlyScreenNoTransitionImpl()
{
    touchgfx::makeTransition<ScanBoardSlowlyView, ScanBoardSlowlyPresenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Transmission Error Screen
void FrontendApplication::gotoTransmissionErrorScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, CALLBACK_CAST(gotoTransmissionErrorScreenNoTransitionImpl));
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoTransmissionErrorScreenNoTransitionImpl()
{
    touchgfx::makeTransition<TransmissionErrorView, TransmissionErrorPresenter, touchgfx::NoTransition, Model >
        (&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

