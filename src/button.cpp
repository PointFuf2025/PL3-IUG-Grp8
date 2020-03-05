#include <ei_widget.h>

namespace ei {
Button::Button(Widget* parent) : Widget("button", parent){
}

Button::~Button(){}
/**
 * @brief   Configures the attributes of widgets of the class "button".
 *
 * @param   widget, requested_size, color, border_width, relief, text, text_font,
 *          text_color, text_anchor, img, img_rect, img_anchor
 *              See the parameter definition of \ref Frame::configure. The only
 *              difference is that relief defaults to \ref ei_relief_raised
 *              and border_width defaults to \ref k_default_button_border_width.
 * @param   corner_radius   The radius (in pixels) of the rounded corners of the button.
 *                          0 means straight corners. Defaults to k_default_button_corner_radius.
 */

void Button::configure (Size*            requested_size,
                        const color_t*   color,
                        int*             border_width,
                        int*             corner_radius,
                        relief_t*        relief,
                        const char **    text,
                        font_t*          text_font,
                        color_t*         text_color,
                        anchor_t*        text_anchor,
                        surface_t*       img,
                        Rect**           img_rect,
                        anchor_t*        img_anchor)
                {
                    this->requested_size =  *requested_size ;
                    screen_location.size = *requested_size ;
                    this->_color = (color!=NULL) ? *color : default_background_color ;
                    if(text == nullptr)
                    {
                        _text = nullptr;
                    }
                    else
                    {
                        _text = *text;
                        _text_font = text_font == nullptr? hw_text_font_create(default_font_filename,font_default_size) : *text_font;
                        _text_color = text_color == nullptr? font_default_color : *text_color;
                        _text_anchor = text_anchor == nullptr? ei_anc_center : *text_anchor;
                    }
                     if(img != nullptr)
                    {
                        _img = img;
                        _img_rect = *img_rect ;
                        _img_anchor = img_anchor == nullptr? ei_anc_center : *img_anchor;
                    }
                    _relief = relief == nullptr? ei_relief_raised : *relief;
                    _border_width = border_width == nullptr? default_button_border_width : *border_width;
                    _corner_radius = corner_radius == nullptr? default_button_corner_radius : *corner_radius;
                }


void Button::draw(surface_t surface,
             surface_t pick_surface,
             Rect* clipper)
            {
            color_t lgrey = { 0xcf, 0xcf, 0xcf, 0xff };
            color_t dgrey = { 0x6f, 0x6f, 0x6f, 0xff };

//            if (clipper==NULL) {
//                clipper = &screen_location ;
//            }
//            linked_point_t rect_bottom = rounded_frame(*clipper, _corner_radius, BT_BOTTOM);
//            linked_point_t rect_top = rounded_frame(*clipper, _corner_radius, BT_TOP);
//            clipper->top_left.x() = clipper->top_left.x() + 5;
//            clipper->top_left.y() = clipper->top_left.y()  + 5;
//            clipper->size.width() =  clipper->size.width() - 10;
//            clipper->size.height() =  clipper->size.height() - 10;
//            linked_point_t rect_full = rounded_frame(*clipper, _corner_radius-5, BT_FULL);

            if (clipper==NULL) {
                clipper = new Rect(hw_surface_get_rect(surface)) ;
            }
            linked_point_t rect_bottom = rounded_frame(screen_location, _corner_radius, BT_BOTTOM);
            linked_point_t rect_top = rounded_frame(screen_location, _corner_radius, BT_TOP);
            screen_location.top_left.x() = screen_location.top_left.x() + 5;
            screen_location.top_left.y() = screen_location.top_left.y()  + 5;
            screen_location.size.width() =  screen_location.size.width() - 10;
            screen_location.size.height() =  screen_location.size.height() - 10;
            linked_point_t rect_full = rounded_frame(screen_location, _corner_radius-5, BT_FULL);

            draw_polygon(surface, rect_top, lgrey, clipper);
            draw_polygon(surface, rect_bottom, dgrey, clipper);
            draw_polygon(surface, rect_full, _color, clipper);

            // text
            hw_text_compute_size(_text,_text_font,this->requested_size);
//            Point pos = clipper->top_left;
//            pos.x() += (clipper->size.width() - this->requested_size.width()) / 2.f;
//            pos.y() += (clipper->size.height() - this->requested_size.height()) / 2.f;
            Point pos = screen_location.top_left;
            pos.x() += (screen_location.size.width() - this->requested_size.width()) / 2.f;
            pos.y() += (screen_location.size.height() - this->requested_size.height()) / 2.f;

//            draw_text(surface, &pos, _text, _text_font, &_text_color);
            }

void Button::geomnotify(Rect rect){
    setScreenLocation(rect.top_left, rect.size);
}

//Button Button::operator =(Button button) {
//    name = button.name ;
//    pick_id = button.pick_id ;
//    pick_color = button.pick_color ;
//    parent = button.parent ;
//    children = button.children ;
//    geom_manager = button.geom_manager ;
////    requested_size = button.requested_size ;
//    screen_location = button.screen_location ;
//    content_rect = button.content_rect ;
////    _requested_size = button._requested_size;
//    _color = button._color;
//    _border_width;
//    _corner_radius;
//    _relief;
//     _text;
//    _text_font;
//    _text_color;
//    _text_anchor;
//    _img;
//    _img_rect;
//    _img_anchor;

//}
}














