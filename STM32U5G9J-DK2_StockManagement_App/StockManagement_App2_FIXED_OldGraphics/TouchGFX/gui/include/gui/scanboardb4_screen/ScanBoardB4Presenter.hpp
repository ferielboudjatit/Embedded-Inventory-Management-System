#ifndef SCANBOARDB4PRESENTER_HPP
#define SCANBOARDB4PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScanBoardB4View;

class ScanBoardB4Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScanBoardB4Presenter(ScanBoardB4View& v);

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

    virtual ~ScanBoardB4Presenter() {}

private:
    ScanBoardB4Presenter();

    ScanBoardB4View& view;
};

#endif // SCANBOARDB4PRESENTER_HPP
