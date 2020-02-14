class Button : public Widget
{
public:

    Button(Widget* parent);

    virtual ~Button();

protected:
    Size*       _requested_size;
    const color_t*   _color;
    int*             _border_width;
    int*             _corner_radius;
    relief_t    _relief;
    char**        _text;
    font_t      _text_font;
    color_t     _text_color;
    anchor_t    _text_anchor;
    surface_t   _img;
    Rect        **_img_rect;
    anchor_t    _img_anchor;
    


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
    void configure (Size*            requested_size,
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
                             _text = text;
                            _text_font = text_font == nullptr? default_font : *text_font;
                             _text_color = text_color == nullptr? font_default_color : *text_color;
                            _text_anchor = text_anchor == nullptr? ei_anc_center : *text_anchor;
                        }

                        if(img != nullptr)
                        {
                            _img = img;
                            _img_rect = img_rect ;
                            _img_anchor = img_anchor == nullptr? ei_anc_center : *img_anchor;
                        }
                        _relief = relief == nullptr? ei_relief_raised : *relief;
                        _border_width = border_width == nullptr? k_default_button_border_width : *border_width;
                        _corner_radius = corner_radius == nullptr? k_default_button_corner_radius : *corner_radius;
                    }





};
