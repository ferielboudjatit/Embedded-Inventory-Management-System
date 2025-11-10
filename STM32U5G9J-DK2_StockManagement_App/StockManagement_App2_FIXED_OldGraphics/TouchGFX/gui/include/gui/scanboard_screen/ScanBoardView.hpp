#ifndef SCANBOARDVIEW_HPP
#define SCANBOARDVIEW_HPP

#include <gui_generated/scanboard_screen/ScanBoardViewBase.hpp>
#include <gui/scanboard_screen/ScanBoardPresenter.hpp>

class ScanBoardView : public ScanBoardViewBase
{
public:
    ScanBoardView();
    virtual ~ScanBoardView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCANBOARDVIEW_HPP
