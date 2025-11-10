#ifndef BADGESCANNEDPRESENTER_HPP
#define BADGESCANNEDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class BadgeScannedView;

class BadgeScannedPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    BadgeScannedPresenter(BadgeScannedView& v);

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

    virtual ~BadgeScannedPresenter() {}

private:
    BadgeScannedPresenter();

    BadgeScannedView& view;
};

#endif // BADGESCANNEDPRESENTER_HPP
