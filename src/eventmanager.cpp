#include "ei_eventmanager.h"
#include "ei_application.h"


namespace ei {
 EventManager::EventManager(){}

    /**
     * \brief	Binds a callback to an event type and a widget or a tag.
     *
     * @param	eventtype	The type of the event.
     * @param	widget		The callback is only called if the event is related to this widget.
     *                      This parameter must be NULL if the "tag" parameter is not NULL.
     * @param	tag		The callback is only called if the event is related to a widget that
     *                  has this tag. A tag can be a widget class name, or the tag "all".
     *      			This parameter must be NULL if the "widget" parameter is not NULL.
     * @param	callback	The callback (i.e. the function to call).
     * @param	user_param	A user parameter that will be passed to the callback when it is called.
     */
     void EventManager::bind(ei_eventtype_t eventtype,
               Widget*        widget,
               tag_t          tag,
               ei_callback_t  callback,
               void*          user_param)
    {
         if (widget!=NULL && widget->getName()=="Button") {

        switch (eventtype) {
            case ei_ev_mouse_buttondown:
//               button.setRelief(ei_relief_sunken);
                break;
            case ei_ev_mouse_buttonup:
//                button.setRelief(ei_relief_raised);
                break;
            case ei_ev_keydown:
                hw_event_wait_next() ;
                break;
            case ei_ev_display:

                break;
            default:
                break;
            }
//        const Rect rect_to_update = button.getScreenLocation();
//        Application::getInstance()->invalidate_rect(rect_to_update);
        }
    }


    /**
     * \brief	Unbinds a callback from an event type and widget or tag.
     *
     * @param	eventtype, widget, tag, callback, user_param
     *			All parameters must have the same value as when
     *          \ref ei::EventManager::bind was called to create the binding.
     */
    void EventManager::unbind (ei_eventtype_t eventtype,
                 Widget*        widget,
                 tag_t          tag,
                 ei_callback_t  callback,
                 void*          user_param)
    {

    }


}
