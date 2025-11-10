#ifndef BOARDENTEREDPRESENTER_HPP
#define BOARDENTEREDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class BoardEnteredView;

class BoardEnteredPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    BoardEnteredPresenter(BoardEnteredView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~BoardEnteredPresenter() {}

private:
    BoardEnteredPresenter();

    BoardEnteredView& view;
};

#endif // BOARDENTEREDPRESENTER_HPP
