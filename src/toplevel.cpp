#include "ei_widget.h"




namespace ei {
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


    this->requested_size = requested_size->empty() ? Size(320,240) :
                                                       *requested_size ;
    pick_color = (color == nullptr)? default_background_color : *color;
    _border_with = border_width==NULL ? 4: *border_width ;
    _title = (title==NULL) ? "Toplevel" : *title;
    _closable = closable==NULL ? EI_TRUE : *closable ;
    if (_closable==EI_TRUE) {
        surface_t clos;
        Size s_clos ;
        clos = hw_image_load(DATA_DIR"cross.png") ;
        s_clos = hw_surface_get_size(clos) ;
        children.push_back(this) ;
        children[0]->configure(&s_clos, &default_banner_color, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL, NULL, clos, NULL, NULL);
    }
    _resizable = (resizable==NULL) ? ei_axis_both : *resizable ;
    _min_size = min_size->empty() ? Size(160,120) : *min_size ;
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
    Size surface_size ;
    linked_point_t s_pos ;
    if (clipper!=NULL) {
        surface_size = clipper->size ;
        s_pos.push_front(clipper->top_left);
    }else{
        surface_size = hw_surface_get_size(surface) ;
        s_pos.push_front(Point(0,0)) ;
    }
    s_pos.push_front(Point(s_pos.front().x() + (int)surface_size.width(), s_pos.front().y() )) ;
    s_pos.push_front(Point(s_pos.front().x(), s_pos.front().y()+ (int)surface_size.height())) ;
    s_pos.push_front(Point(s_pos.front().x() - (int)surface_size.width(), s_pos.front().y())) ;
    draw_polygon(pick_surface,s_pos,pick_color,NULL);
    color_t white = {255,255,255,255} ;
    Point p(0,0) ;
    surface_t s_text = hw_text_create_surface(_title, default_font, &white) ;
    draw_polygon(surface,s_pos,default_background_color,NULL);
    ei_copy_surface(surface, s_text, &p, EI_FALSE) ;
}

}
