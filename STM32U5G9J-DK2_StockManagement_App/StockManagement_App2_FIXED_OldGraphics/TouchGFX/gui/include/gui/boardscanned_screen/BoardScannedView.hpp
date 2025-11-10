#ifndef BOARDSCANNEDVIEW_HPP
#define BOARDSCANNEDVIEW_HPP

#include <gui_generated/boardscanned_screen/BoardScannedViewBase.hpp>
#include <gui/boardscanned_screen/BoardScannedPresenter.hpp>

class BoardScannedView : public BoardScannedViewBase
{
public:
    BoardScannedView();
    virtual ~BoardScannedView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BOARDSCANNEDVIEW_HPP
