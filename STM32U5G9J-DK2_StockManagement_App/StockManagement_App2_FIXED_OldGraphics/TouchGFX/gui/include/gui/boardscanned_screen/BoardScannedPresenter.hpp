#ifndef BOARDSCANNEDPRESENTER_HPP
#define BOARDSCANNEDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class BoardScannedView;

class BoardScannedPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    BoardScannedPresenter(BoardScannedView& v);

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

    virtual ~BoardScannedPresenter() {}

private:
    BoardScannedPresenter();

    BoardScannedView& view;
};

#endif // BOARDSCANNEDPRESENTER_HPP
