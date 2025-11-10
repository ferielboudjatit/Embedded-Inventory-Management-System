#ifndef SCANBADGEPRESENTER_HPP
#define SCANBADGEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScanBadgeView;

class ScanBadgePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScanBadgePresenter(ScanBadgeView& v);

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

    virtual ~ScanBadgePresenter() {}

private:
    ScanBadgePresenter();

    ScanBadgeView& view;
};

#endif // SCANBADGEPRESENTER_HPP
