#include <ei_widget.h>


#include <functional>

namespace ei{

    /**
     * @brief   Configures the attributes of widgets of the class "frame".
     *
     *      Parameters obey the "default" protocol: if a parameter is "NULL" and it has never
     *      been defined before, then a default value should be used (default values are
     *      specified for each parameter). If the parameter is "NULL" but was defined on a
     *      previous call, then its value must not be changed.
     *
     * @param   requested_size  The size requested for this widget. The geometry manager may
     *                  override this size due to other constraints.
     *                  Defaults to the "natural size" of the widget, ie. big enough to
     *                  display the text or the image, or (0, 0) if the widget has no text
     *                  and no image.
     * @param   color       The color of the background of the widget. Defaults to
     *                      \ref ei_default_background_color.
     * @param   border_width    The width in pixel of the border decoration of the widget. The final
     *                          appearance depends on the "relief" parameter. Defaults to 0.
     * @param   relief      Appearance of the border of the widget. Defaults to \ref ei_relief_none.
     * @param   text        The text to display in the widget, or NULL. Only one of the
     *                      parameter "text" and "img" should be used (i.e. non-NULL). Defaults
     *                      to NULL.
     * @param   text_font   The font used to display the text. Defaults to \ref ei_default_font.
     * @param   text_color  The color used to display the text. Defaults to
     *                      \ref ei_font_default_color.
     * @param   text_anchor The anchor of the text, i.e. where it is placed whithin the widget
     *                      when the size of the widget is bigger than the size of the text.
     *                      Defaults to \ref ei_anc_center.
     * @param   img     The image to display in the widget, or NULL. Any surface can be
     *                  used, but usually a surface returned by \ref hw_image_load. Only one
     *                  of the parameter "text" and "img" should be used (i.e. non-NULL).
     *                  Defaults to NULL.
     * @param   img_rect    If not NULL, this rectangle defines a subpart of "img" to use as the
     *                      image displayed in the widget. Defaults to NULL.
     * @param   img_anchor  The anchor of the image, i.e. where it is placed whithin the widget
     *                      when the size of the widget is bigger than the size of the image.
     *                      De  de  n’utiliser  qu’une  sous-partie  de  l’image, faults to \ref ei_anc_center.
     */


Frame::Frame(Widget *parent) : Widget("Frame", parent)
{
    //this->parent = parent;
}

Frame::~Frame(){}



void Frame::configure (Size*           requested_size,
                    const color_t*  color,
                    int*            border_width,
                    relief_t*       relief,
                    char**          text,
                    font_t*         text_font,
                    color_t*        text_color,
                    anchor_t*       text_anchor,
                    surface_t*      img,
                    Rect*          img_rect,
                    anchor_t*       img_anchor){

       pick_color = (color == nullptr)? default_background_color : *color;
       _border_width = border_width == nullptr? 0 : *border_width;
        _relief = relief == nullptr? ei_relief_none : *relief ;

       if(text == nullptr){
           _text = nullptr;

       }
       else{
           _text = text;
           _text_font = text_font == nullptr? default_font : *text_font;
           _text_color = text_color == nullptr? font_default_color : *text_color;
           _anchor = text_anchor == nullptr? ei_anc_center : *text_anchor;
       }

       if(img != nullptr){
           _img = img;
           _img_rect = *img_rect ;
           _anchor = img_anchor == nullptr? ei_anc_center : *img_anchor;
       }
    }

void Frame::draw (surface_t surface,
                           surface_t pick_surface,
                           Rect*     clipper){
        Point test = Point();

        Point location = screen_location.top_left;
        Size size = screen_location.size;
        /*switch(_relief){
        case ei_relief_raised:

             _border_rect = Rect(Point(location.x()+_border_width, location.y() + _border_width), size);
             _border_rect.
    }*/


        if(_text != NULL){
            surface_t s_text = hw_text_create_surface((*_text), _text_font, &_text_color);
            Size stext_size = hw_surface_get_size(s_text);
            switch (_anchor) {
            case ei_anc_center:
                test = Point(requested_size.width() - stext_size.width()/2, requested_size.height()- stext_size.height()/2);
                break;
            case ei_anc_north:
                test = Point(requested_size.width()-stext_size.width()/2, 0);
                break;
            case ei_anc_northeast:
                test = Point(requested_size.width() - stext_size.width(), 0);
                break;
            case ei_anc_northwest:
                test = Point(0, 0);
                break;
            case ei_anc_east:
                test = Point(requested_size.width() - stext_size.width(), requested_size.height() - stext_size.height()/2);
                break;
            case ei_anc_south:
                test = Point(requested_size.width() - stext_size.width()/2, requested_size.height()-stext_size.height());
                break;
            case ei_anc_southeast:
                test = Point(requested_size.width() - stext_size.width(), requested_size.height()-stext_size.height());
                break;
            case ei_anc_southwest:
                test = Point(0, requested_size.height() - stext_size.width());
                break;
            case ei_anc_west:
                test = Point(0, requested_size.height()-stext_size.height()/2);
                break;
            }
            if(clipper==NULL)
                draw_text(surface, &test, *(_text), _text_font, &_text_color);
            else{
                ei_copy_subsurface(surface, s_text, &test , clipper->size, EI_TRUE );
            }
        }
        if(&_img != NULL){
            Size _img_size = hw_surface_get_size(_img);
            switch (_anchor) {
            case ei_anc_none:
                break;
            case ei_anc_center:
                test = Point(requested_size.width() - _img_size.width()/2, requested_size.height()- _img_size.height()/2);
                break;
            case ei_anc_north:
                test = Point(requested_size.width()-_img_size.width()/2, 0);
                break;
            case ei_anc_northeast:
                test = Point(requested_size.width() - _img_size.width(), 0);
                break;
            case ei_anc_northwest:
                test = Point(0, 0);
                break;
            case ei_anc_east:
                test = Point(requested_size.width() - _img_size.width(), requested_size.height() - _img_size.height()/2);
                break;
            case ei_anc_south:
                test = Point(requested_size.width() - _img_size.width()/2, requested_size.height()-_img_size.height());
                break;
            case ei_anc_southeast:
                test = Point(requested_size.width() - _img_size.width(), requested_size.height()-_img_size.height());
                break;
            case ei_anc_southwest:
                test = Point(0, requested_size.height() - _img_size.width());
                break;
            case ei_anc_west:
                test = Point(0, requested_size.height()-_img_size.height()/2);
                break;
            }
            if(clipper==NULL)
                ei_copy_surface(surface, _img, &test, EI_TRUE);
            else{
                ei_copy_subsurface(surface, _img, &test, clipper->size, EI_TRUE);
                }
        }

        for(Widget* w : children) {
            w->draw(surface, pick_surface, clipper);
        }

        }

void Frame::geomnotify (Rect rect){
    this->setScreenLocation(rect.top_left, rect.size);
}
}
