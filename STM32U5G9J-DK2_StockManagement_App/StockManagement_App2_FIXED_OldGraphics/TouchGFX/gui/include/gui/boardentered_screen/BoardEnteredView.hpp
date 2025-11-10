#ifndef BOARDENTEREDVIEW_HPP
#define BOARDENTEREDVIEW_HPP

#include <gui_generated/boardentered_screen/BoardEnteredViewBase.hpp>
#include <gui/boardentered_screen/BoardEnteredPresenter.hpp>

class BoardEnteredView : public BoardEnteredViewBase
{
public:
    BoardEnteredView();
    virtual ~BoardEnteredView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BOARDENTEREDVIEW_HPP
