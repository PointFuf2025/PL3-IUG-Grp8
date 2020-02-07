#include "application.h"

namespace ei {
Application::Application(Size* main_window_size)
{
    // Init acces to hardware.
    hw_init();
    default_font = hw_text_font_create(default_font_filename, font_default_size);

    // Create the main window.
    surface_t main_window = hw_create_window(&main_window_size, EI_FALSE);

    //new Frame()
    //ajouter dans le .h un attribut frame ?
}
}
