#include "ei_widget.h"




namespace ei {


Toplevel::Toplevel(Widget *parent) : Widget("top level", parent) {}

Toplevel::~Toplevel() {}
/**
 * @brief   Configures the attributes of widgets of the class "toplevel".
 *
 * @param   widget      The widget to configure.
 * @param   requested_size  The content size requested for this widget, this does not include
 *              the decorations (border, title bar). The geometry manager may
 *              override this size due to other constraints.
 *              Defaults to (320x240).
 * @param   color       The color of the background of the content of the widget. Defaults
 *                      to \ref ei_default_background_color.
 * @param   border_width    The width in pixel of the border of the widget. Defaults to 4.
 * @param   title       The string title diplayed in the title bar. Defaults to "Toplevel".
 * @param   closable    If true, the toplevel is closable by the user, the toplevel must
 *                      show a close button in its title bar. Defaults to \ref EI_TRUE.
 * @param   resizable   Defines if the widget can be resized horizontally and/or vertically
 *                      by the user. Defaults to \ref ei_axis_both.
 * @param   min_size    For resizable widgets, defines the minimum size. Defaults to (160, 120).
 */
void Toplevel::configure(Size *requested_size,
                    color_t *color,
                    int *border_width,
                    const char **title,
                    bool_t *closable,
                    axis_set_t *resizable,
                    Size *min_size) {


    this->requested_size = requested_size->empty() ? Size(320,240) : *requested_size ;
    if (parent ==NULL) {
        screen_location.size = *requested_size;
        screen_location.top_left = Point(0,0);
    }else{
        screen_location.size = parent->getRequestedSize() ;
//        screen_location.top_left =
    }
    _color = (color == nullptr)? default_background_color : *color;
    _border_with = border_width==NULL ? 4: *border_width ;
    _title = (title==NULL) ? "Toplevel" : *title;
    _closable = closable==NULL ? EI_TRUE : *closable ;
//    if (_closable==EI_TRUE) {
//        surface_t clos;
//        Size s_clos ;
//        clos = hw_image_load(DATA_DIR"cross.png") ;
//        s_clos = hw_surface_get_size(clos) ;
//        children.push_back(this) ;
//        children[0]->configure(&s_clos, &default_banner_color, NULL, NULL, NULL,
//                                  NULL, NULL, NULL, NULL, NULL, NULL, clos, NULL, NULL);
//    }
    _resizable = (resizable==NULL) ? ei_axis_both : *resizable ;
    _min_size = min_size==NULL ? Size(160,120) : *min_size ;
}

/**
 * \brief   Method that draws the widget.
 *
 * @param   surface     Where to draw the widget. The actual location of the widget in the
 *                      surface is stored in its "screen_location" field.
 * @param   pick_surface  Offscreen buffer to draw the widget \ref pick_id
 * @param   clipper     If not NULL, the drawing is restricted within this rectangle
 *                      (expressed in the surface reference frame).
 */

void Toplevel::draw(surface_t surface,
                    surface_t pick_surface,
                    Rect *clipper){
    Size s_topl_ps = hw_surface_get_size(pick_surface),
            s_topl_s = hw_surface_get_size(surface) ;
    surface_t s_bis = hw_surface_create(surface, &s_topl_s) ;
    surface_t ps_bis = hw_surface_create(surface, &s_topl_ps) ;
    surface_t clos = hw_image_load(DATA_DIR"cross.png") ;;
    Size s_clos ;
    linked_point_t frame_topl_up ;
    if (clipper==NULL) {
        clipper = new Rect(screen_location.top_left,
                            screen_location.size)  ;
    }

    frame_topl_up = rounded_frame(Rect (clipper->top_left, Size(clipper->size.width(), clipper->size.height()*2)), 15.0, BT_FULL);

    Point p = clipper->top_left ;
    color_t white = {255,255,255,255} ;
    color_t color_offscreen = {0,0,255,255} ;

    //draw
    hw_surface_lock(s_bis);
    hw_surface_lock(ps_bis);

    draw_polygon(s_bis, frame_topl_up, default_banner_color, clipper);
    draw_polygon(ps_bis, frame_topl_up, color_offscreen, clipper);


    ei_copy_surface(pick_surface, s_bis, &p, EI_TRUE) ;
    p.x()+=5 ;
    p.y()+=5 ;
    if (_closable==EI_TRUE) {
        hw_surface_lock(clos);
        s_clos = hw_surface_get_size(clos) ;
        ei_copy_surface(s_bis, clos, &p, EI_TRUE) ;
        p.x() += s_clos.width() +5 ;
        hw_surface_unlock(clos);
    }


    draw_text(s_bis, &p, _title, default_font, &_color) ;
    ei_copy_surface(surface, s_bis, &(p=Point(0,0)), EI_TRUE) ;
    hw_surface_unlock(s_bis) ;
    hw_surface_unlock(ps_bis) ;


    content_rect->size.width() = clipper->size.width() - 2*_border_with ;
    content_rect->size.height() = clipper->size.height() - 7  - s_clos.height() - _border_with ;

    content_rect->top_left.x() = clipper->top_left.x() + _border_with ;
    content_rect->top_left.y() = clipper->top_left.y() + 7  + s_clos.height()  ;

    linked_point_t rect_content = rounded_frame(*content_rect, 0.0, BT_FULL) ;
    draw_polygon(surface, rect_content, white, NULL);


    for(Widget* w : children) {
        w->draw(surface, pick_surface, content_rect);
    }

}

void Toplevel::geomnotify(Rect rect){
    this->setScreenLocation(rect.top_left, rect.size);
}

}
