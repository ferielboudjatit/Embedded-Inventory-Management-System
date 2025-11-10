#ifndef SCANBADGEB4VIEW_HPP
#define SCANBADGEB4VIEW_HPP

#include <gui_generated/scanbadgeb4_screen/ScanBadgeB4ViewBase.hpp>
#include <gui/scanbadgeb4_screen/ScanBadgeB4Presenter.hpp>

class ScanBadgeB4View : public ScanBadgeB4ViewBase
{
public:
    ScanBadgeB4View();
    virtual ~ScanBadgeB4View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCANBADGEB4VIEW_HPP
