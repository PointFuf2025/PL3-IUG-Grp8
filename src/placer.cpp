#include "ei_geometrymanager.h"

namespace ei  {
Placer::Placer() {}

Placer::~Placer() {}
/**
 * \brief Configures the geometry of a widget using the "placer" geometry manager.
 *    If the widget was already managed by another geometry manager, then it is first
 *    removed from the previous geometry manager.
 *    If the widget was already managed by the "placer", then this calls simply updates
 *    the placer parameters: arguments that are not NULL replace previous values.
 *    When the arguments are passed as NULL, the placer uses default values (detailed in
 *    the argument descriptions below). If no size is provided (either absolute or
 *    relative), then the requested size of the widget is used, i.e., the minimal size
 *    required to display its content.
 *
 * @param widget    The widget to place.
 * @param anchor    How to anchor the widget to the position defined by the placer
 *        (defaults to ei_anc_northwest).
 * @param x   The absolute x position of the widget (defaults to 0).
 * @param y   The absolute y position of the widget (defaults to 0).
 * @param width   The absolute width for the widget (defaults to the requested width
 *        of the widget).
 * @param height    The absolute height for the widget (defaults to the requested height
 *        of the widget).
 * @param rel_x   The relative x position of the widget: 0.0 corresponds to the left
 *        side of the master, 1.0 to the right side (defaults to 0.0).
 * @param rel_y   The relative y position of the widget: 0.0 corresponds to the top
 *        side of the master, 1.0 to the bottom side (defaults to 0.0).
 * @param rel_width The relative width of the widget: 0.0 corresponds to a width of 0,
 *        1.0 to the width of the master (defaults to 0.0).
 * @param rel_height  The relative height of the widget: 0.0 corresponds to a height of 0,
 *        1.0 to the height of the master (defaults to 0.0).
 */

//ei_anc_none = 0,   ///< No anchor defined.
//ei_anc_center,     ///< Anchor in the center.
//ei_anc_north,      ///< Anchor on the top side, centered horizontally.
//ei_anc_northeast,  ///< Anchor on the top-right corner.
//ei_anc_east,       ///< Anchor on the right side, centered vertically.
//ei_anc_southeast,  ///< Anchor on the bottom-right corner.
//ei_anc_south,      ///< Anchor on the bottom side, centered horizontally.
//ei_anc_southwest,  ///< Anchor on the bottom-left corner.
//ei_anc_west,       ///< Anchor on the left side, centered vertically.
//ei_anc_northwest
void Placer::configure (Widget*    widget,
                anchor_t*  anchor,
                int*       x,
                int*       y,
                float*     width,
                float*     height,
                float*     rel_x,
                float*     rel_y,
                float*     rel_width,
                float*     rel_height){
    *rel_x = (rel_x==NULL) ? 0.0 : *rel_x ;
    *rel_y = (rel_y==NULL) ? 0.0 : *rel_y ;
    *rel_width = (rel_width==NULL) ? 0.0 : *rel_width ;
    *rel_height = (rel_height==NULL) ? 0.0 : *rel_height ;
    *x = (x==NULL) ? 0.0 : *x ;
    *y = (y==NULL) ? 0.0 : *y ;
    *width = (rel_width==NULL) ? 0.0 : *width ;
    *height = (rel_height==NULL) ? 0.0 : *height ;
    Widget *parent = widget->getParent() ;
    Point p ;
    Size s ;
    s.width() = *rel_x * parent->getScreenLocation().size.width() + *width ;
    s.height() = *rel_y * parent->getScreenLocation().size.height() + *height ;
    switch(*anchor) {

    case (ei_anc_northwest) :
         case( ei_anc_none) :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y() ;
        break ;
    case(ei_anc_center) :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x()
                - 1/2*widget->getScreenLocation().size.width() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y()
                - 1/2*widget->getScreenLocation().size.height();
        break ;
    case (ei_anc_north) :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x()
                - 1/2*widget->getScreenLocation().size.width() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y() ;

        break ;
    case (ei_anc_northeast) :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x()
                - widget->getScreenLocation().size.width() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y() ;
        break ;
    case (ei_anc_east) :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x()
                - widget->getScreenLocation().size.width() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y()
                - 1/2 * widget->getScreenLocation().size.height() ;
        break ;
    case (ei_anc_southeast) :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x()
                - widget->getScreenLocation().size.width() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y()
                - widget->getScreenLocation().size.height() ;

        break ;
    case ei_anc_south :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x()
                - 1/2* widget->getScreenLocation().size.width() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y()
                - widget->getScreenLocation().size.height() ;
        break ;
    case ei_anc_southwest :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y()
                - widget->getScreenLocation().size.height() ;
        break ;
    case ei_anc_west :
        p.x() = *rel_x * parent->getScreenLocation().size.width() +
                *x + parent->getScreenLocation().top_left.x() ;
        p.y() = *rel_y * parent->getScreenLocation().size.height() +
                *y + parent->getScreenLocation().top_left.y()
                - 1/2* widget->getScreenLocation().size.height() ;
        break ;
    }
    widget->setScreenLocation(p,s) ;
}
}

