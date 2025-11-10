#ifndef TRANSMISSIONERRORPRESENTER_HPP
#define TRANSMISSIONERRORPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class TransmissionErrorView;

class TransmissionErrorPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    TransmissionErrorPresenter(TransmissionErrorView& v);

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

    virtual ~TransmissionErrorPresenter() {}

private:
    TransmissionErrorPresenter();

    TransmissionErrorView& view;
};

#endif // TRANSMISSIONERRORPRESENTER_HPP
