#ifndef BOARDGOTOUTVIEW_HPP
#define BOARDGOTOUTVIEW_HPP

#include <gui_generated/boardgotout_screen/BoardGotoutViewBase.hpp>
#include <gui/boardgotout_screen/BoardGotoutPresenter.hpp>

class BoardGotoutView : public BoardGotoutViewBase
{
public:
    BoardGotoutView();
    virtual ~BoardGotoutView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BOARDGOTOUTVIEW_HPP
