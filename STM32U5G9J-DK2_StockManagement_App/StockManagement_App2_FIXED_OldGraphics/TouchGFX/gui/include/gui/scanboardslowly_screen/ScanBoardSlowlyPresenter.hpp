#ifndef SCANBOARDSLOWLYPRESENTER_HPP
#define SCANBOARDSLOWLYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScanBoardSlowlyView;

class ScanBoardSlowlyPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScanBoardSlowlyPresenter(ScanBoardSlowlyView& v);

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

    virtual ~ScanBoardSlowlyPresenter() {}

private:
    ScanBoardSlowlyPresenter();

    ScanBoardSlowlyView& view;
};

#endif // SCANBOARDSLOWLYPRESENTER_HPP
