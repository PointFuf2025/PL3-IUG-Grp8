#include "ei_application.h"

namespace ei {
Application::Application(Size* main_window_size)
{
    Application* Application::instance=nullptr;
    // Init acces to hardware.
    hw_init();
    default_font = hw_text_font_create(default_font_filename, font_default_size);

    // Create the main window.
    surface_t main_window = hw_create_window(&main_window_size, EI_FALSE);

    *root_widget=new Frame(main_window);
    linked_rect_t list;
    rect_to_update = list;



}

Application::root_widget()
{
    return root_widget;
}

Application::run()
{
    running=EI_TRUE;
    draw(root_widget());

    //faire une boucle pour actualiser les widget et les redessiner.
    // Wait for a key press.
    while (running == EI_TRUE) {
        Event* event = hw_event_wait_next();
        if(event->type == ei_ev_keydown)
            quit_request();
    }

    // Free hardware resources.
    hw_quit();


    //dans run il faut parcourir tout les widget et les dessiner une fois, ensuite redessiner que ceux qui sont update en parcourant les enfants
    // c'est aux enfant de le faire, run n'appelle qu'une fois draw sur la racine.

}
Application::quit_request()
{
    running = EI_FALSE;
}

}
