#ifndef SCANBOARDB4VIEW_HPP
#define SCANBOARDB4VIEW_HPP

#include <gui_generated/scanboardb4_screen/ScanBoardB4ViewBase.hpp>
#include <gui/scanboardb4_screen/ScanBoardB4Presenter.hpp>

class ScanBoardB4View : public ScanBoardB4ViewBase
{
public:
    ScanBoardB4View();
    virtual ~ScanBoardB4View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCANBOARDB4VIEW_HPP
