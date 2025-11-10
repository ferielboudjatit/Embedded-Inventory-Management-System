#ifndef TRANSMISSIONERRORVIEW_HPP
#define TRANSMISSIONERRORVIEW_HPP

#include <gui_generated/transmissionerror_screen/TransmissionErrorViewBase.hpp>
#include <gui/transmissionerror_screen/TransmissionErrorPresenter.hpp>

class TransmissionErrorView : public TransmissionErrorViewBase
{
public:
    TransmissionErrorView();
    virtual ~TransmissionErrorView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // TRANSMISSIONERRORVIEW_HPP
