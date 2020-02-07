#include <widget.h>

class Frame : public Widget
{
public:

    Frame(Widget* parent);

    virtual ~Frame();

    virtual void draw (surface_t surface,
                       surface_t pick_surface,
                       Rect*     clipper);

protected:
    relief_t    relief;
    char**        text;
    font_t      text_font;
    color_t     text_color;
    anchor_t    text_anchor;
    surface_t   img;
    Rect        img_rect;
    anchor_t    img_anchor;
    int         border_width;

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
    void configure (Size*           requested_size,
                    const color_t*  color,
                    int*            border_width,
                    relief_t*       relief,
                    char**          text,
                    font_t*         text_font,
                    color_t*        text_color,
                    anchor_t*       text_anchor,
                    surface_t*      img,
                    Rect**          img_rect,
                    anchor_t*       img_anchor){

       pick_color = (color == nullptr)? ei_default_background_color : *color;
       this->border_width = border_width == nullptr? 0 : border_width;

       if(text == nullptr){
           this->text = nullptr;
           this->text_font = nullptr;
           this->text_anchor=nullptr;
           this->text_color = nullptr;
       }
       else{
           this->text = text;
           this->text_font = text_font == nullptr? ei_default_font : *text_font;
           this->text_color = text_color == nullptr? ei_font_default_color : *text_color;
           this->text_anchor = text_anchor == nullptr? ei_anc_center : *text_anchor;
       }

       if(img == nullptr){
           this->img_rect = nullptr;
           this->anchor = nullptr;
       }
       else{
           this->img = img;
           this->img_rect = img_rect ;
           this->img_anchor = img_anchor == nullptr? ei_anc_center : *img_anchor;
       }
    }
};
