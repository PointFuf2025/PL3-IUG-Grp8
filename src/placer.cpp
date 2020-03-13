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

void Placer::configure (Widget*    widget,
                anchor_t*  anchor,
                int*       x,
                int*       y,
                float*     width,
                float*     height,
                float*     rel_x,
                float*     rel_y,
                float*     rel_width,
                float*     rel_height)
{

    if (widget->getGeom() !=NULL) {
        ;
    }
    _rel_x = (rel_x==nullptr) ? 0.0 : *rel_x ;
    _rel_y = (rel_y==nullptr) ? 0.0 : *rel_y ;
    _rel_width = (rel_width==nullptr) ? 0.0 : *rel_width ;
    _rel_height = (rel_height==nullptr) ? 0.0 : *rel_height ;
    _x = (x==nullptr) ? 0.0 : *x ;
    _y = (y==nullptr) ? 0.0 : *y ;
    _width = (width==nullptr) ? widget->getRequestedSize().width(): *width ;
    _height = (height==nullptr) ? widget->getRequestedSize().height() : *height ;
    _anchor = (anchor ==nullptr)? ei_anc_northwest : *anchor ;


//     printf("_width et _height = %d, %d", widget->getRequestedSize().width(), widget->getRequestedSize().height());


    this->run(widget) ;
}

void Placer::run(Widget *widget) {
    Widget *parent = widget->getParent() ;
    Point p ;
    Size s ;
    s.width() = _rel_width * parent->getScreenLocation().size.width() + _width ;
    s.height() = _rel_height * parent->getScreenLocation().size.height() + _height ;



    switch(_anchor) {

    case ei_anc_northwest :
        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x();
        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y() ;
        //printf("(%f,%f)\n", s.width(), s.height()) ;
        break ;
    case ei_anc_center :

        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x()
                - 0.5*s.width() ;

        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y()
                - 0.5*s.height();
       // printf("(%f,%f)\n", s.width(), s.height()) ;
        break ;
    case ei_anc_north :
        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x()
                - 0.5*s.width() ;
        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y() ;

        break ;
    case ei_anc_northeast :
        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x()
                - s.width() ;
        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y() ;
        break ;
    case ei_anc_east :
        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x()
                - s.width() ;
        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y()
                - 0.5 * s.height() ;
        break ;
    case ei_anc_southeast :
        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x()
                - s.width()/*widget->getScreenLocation().size.width()*/ ;
        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y()
                - s.height()/*widget->getScreenLocation().size.height() */;

        break ;
    case ei_anc_south :
        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x()
                - 0.5* s.width() ;
        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y()
                - s.height() ;
        break ;
    case ei_anc_southwest :
        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x() ;
        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y()
                - s.height();
        break ;
    case ei_anc_west :
        p.x() = _rel_x * parent->getScreenLocation().size.width() +
                _x + parent->getScreenLocation().top_left.x() ;
        p.y() = _rel_y * parent->getScreenLocation().size.height() +
                _y + parent->getScreenLocation().top_left.y()
                - 0.5* s.height() ;
        break ;
    }
    widget->geomnotify(Rect(p,s));

}
void Placer::release(Widget *widget) {
    _rel_width = 0.0 ;
    _rel_height = 0.0 ;
    _width = 0.0 ;
    _height = 0.0 ;
    run(widget) ;
}
}

