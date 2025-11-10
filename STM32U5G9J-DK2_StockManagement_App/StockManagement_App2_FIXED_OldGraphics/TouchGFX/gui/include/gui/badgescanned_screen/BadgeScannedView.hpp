#ifndef BADGESCANNEDVIEW_HPP
#define BADGESCANNEDVIEW_HPP

#include <gui_generated/badgescanned_screen/BadgeScannedViewBase.hpp>
#include <gui/badgescanned_screen/BadgeScannedPresenter.hpp>

class BadgeScannedView : public BadgeScannedViewBase
{
public:
    BadgeScannedView();
    virtual ~BadgeScannedView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BADGESCANNEDVIEW_HPP
