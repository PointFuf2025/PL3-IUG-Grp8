#include <ei_widget.h>

namespace ei {


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
                    if(text == nullptr)
                    {
                        _text = nullptr;
                    }
                    else
                    {
                        _text = *text;
                        _text_font = text_font == nullptr? default_font : *text_font;
                        _text_color = text_color == nullptr? font_default_color : *text_color;
                        _text_anchor = text_anchor == nullptr? ei_anc_center : *text_anchor;
                    }
                     if(img != nullptr)
                    {
                        _img = img;
                        _img_rect = **img_rect ;
                        _img_anchor = img_anchor == nullptr? ei_anc_center : *img_anchor;
                    }
                    _relief = relief == nullptr? ei_relief_raised : *relief;
                    _border_width = border_width == nullptr? default_button_border_width : *border_width;
                    _corner_radius = corner_radius == nullptr? default_button_corner_radius : *corner_radius;
                }


void Button::draw(ei_surface_t surface,
             Rect* clipper,
             float _corner_radius,
             const char* text)
            {
            ei_color_t lgrey = { 0xcf, 0xcf, 0xcf, 0xff };
            ei_color_t dgrey = { 0x6f, 0x6f, 0x6f, 0xff };

            ei_linked_point_t* rect_top = rounded_frame(&clipper, _corner_radius, BT_TOP);
            ei_linked_point_t* rect_bottom = rounded_frame(&clipper, _corner_radius, BT_BOTTOM);
            clipper->top_left.x() +=5;
            clipper->top_left.y() +=5;
            clipper->size.width() -= 10;
            clipper->size.height() -=10;
            //clipper.top_left.x += 5;
            //clipper.top_left.y += 5;
            //clipper.size.width  -= 10;
            //clipper.size.height -= 10;
            ei_linked_point_t* rect_full = rounded_frame(&clipper, _corner_radius-5, BT_FULL);

            ei_draw_polygon(surface, rect_top, lgrey);
            ei_draw_polygon(surface, rect_bottom, dgrey);
            ei_draw_polygon(surface, rect_full, _color);

            // text
            ei_font_t font = hw_text_font_create(ei_default_font_filename, ei_font_default_size);
            int width, height;
            hw_text_compute_size(_text,font,&width,&height);
            ei_point_t pos = clipper->top_left;
            pos.x += (clipper->size.width() - width) / 2.f;
            pos.y += (clipper->size.height() - height) / 2.f;
            ei_draw_text(surface, &pos, _text, _text_font, _text_color);
            }
}
