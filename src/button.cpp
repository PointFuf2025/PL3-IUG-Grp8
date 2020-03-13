#include <ei_widget.h>
#include <cmath>
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

            int lred = std::min(255.0,std::floor(_color.red * 1.5));
            unsigned char lcolor_red = lred;
            int lgreen = std::min(255.0,std::floor(_color.green * 1.5));
            unsigned char lcolor_green = lgreen;
            int lblue = std::min(255.0,std::floor(_color.blue * 1.5));
            unsigned char lcolor_blue = lblue;

            int dred = std::floor(_color.red * 0.50);
            unsigned char dcolor_red = dred;
            int dgreen = std::floor(_color.green * 0.50);
            unsigned char dcolor_green = dgreen;
            int dblue = std::floor(_color.blue * 0.50);
            unsigned char dcolor_blue = dblue;

            color_t lcolor = { lcolor_red, lcolor_green, lcolor_blue, 255};
            color_t dcolor = { dcolor_red, dcolor_green , dcolor_blue, 255};

            color_t pick_color;
            Rect rect_draw ;


            linked_point_t rect_bottom = rounded_frame(screen_location, _corner_radius, BT_BOTTOM);
            linked_point_t rect_top = rounded_frame(screen_location, _corner_radius, BT_TOP);
            rect_draw.top_left.x() = screen_location.top_left.x() + 5;
            rect_draw.top_left.y() = screen_location.top_left.y()  + 5;
            rect_draw.size.width() =  screen_location.size.width() - 10;
            rect_draw.size.height() =  screen_location.size.height() - 10;
            linked_point_t rect_full = rounded_frame(rect_draw, _corner_radius-5, BT_FULL);

            draw_polygon(surface, rect_top, lcolor, clipper);
            draw_polygon(surface, rect_bottom, dcolor, clipper);
            draw_polygon(surface, rect_full, _color, clipper);
            draw_polygon(pick_surface,rect_full,pick_color,clipper);

            // text
            hw_text_compute_size(_text,_text_font,this->requested_size);
            Point pos = rect_draw.top_left;
            pos.x() += (rect_draw.size.width() - this->requested_size.width()) / 2.f;
            pos.y() += (rect_draw.size.height() - this->requested_size.height()) / 2.f;

            draw_text(surface, &pos, _text, _text_font, &_text_color);
            }

void Button::geomnotify(Rect rect){
    setScreenLocation(rect.top_left, rect.size);
}

}














