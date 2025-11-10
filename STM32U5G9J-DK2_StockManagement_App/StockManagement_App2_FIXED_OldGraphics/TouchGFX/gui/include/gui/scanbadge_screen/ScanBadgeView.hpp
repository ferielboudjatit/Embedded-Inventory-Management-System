#ifndef SCANBADGEVIEW_HPP
#define SCANBADGEVIEW_HPP

#include <gui_generated/scanbadge_screen/ScanBadgeViewBase.hpp>
#include <gui/scanbadge_screen/ScanBadgePresenter.hpp>

class ScanBadgeView : public ScanBadgeViewBase
{
public:
    ScanBadgeView();
    virtual ~ScanBadgeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCANBADGEVIEW_HPP
