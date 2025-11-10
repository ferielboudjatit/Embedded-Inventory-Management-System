#ifndef SCANBOARDSLOWLYVIEW_HPP
#define SCANBOARDSLOWLYVIEW_HPP

#include <gui_generated/scanboardslowly_screen/ScanBoardSlowlyViewBase.hpp>
#include <gui/scanboardslowly_screen/ScanBoardSlowlyPresenter.hpp>

class ScanBoardSlowlyView : public ScanBoardSlowlyViewBase
{
public:
    ScanBoardSlowlyView();
    virtual ~ScanBoardSlowlyView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCANBOARDSLOWLYVIEW_HPP
