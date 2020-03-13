#include "ei_application.h"


namespace ei {
font_t  default_font ;
Application* Application::instance=nullptr;
Application::Application(Size* main_window_size)
{

    // Init acces to hardware.
    hw_init();
    default_font = hw_text_font_create(default_font_filename, font_default_size);

    // Create the main window.
    surface_t main_window = hw_create_window(main_window_size, EI_FALSE);
    _surface = main_window ;
    _surface_offScreen = hw_surface_create(_surface, main_window_size) ;
    _root_widget = new Frame(NULL);
    linked_rect_t list;
    rect_to_update = list;



}

Frame* Application::root_widget()
{
    return _root_widget;
}

void Application::run()
{
    running=EI_TRUE;
    _root_widget->draw(_surface, _surface_offScreen, NULL);

    //faire une boucle pour actualiser les widget et les redessiner.
    // Wait for a key pre(0.000000, 0.000000)

    while (running == EI_TRUE) {
        if(!rect_to_update.empty())
        {
            std::list<Rect>::iterator it;
            for(it=rect_to_update.begin();it!=rect_to_update.end();it++)
            {
                _root_widget->draw(_surface, _surface_offScreen,*it); //faire une boucle pour draw tout les rect de la liste?

            }


            }
            hw_surface_update_rects(rect_to_update); //e used for dynamic arrays
            rect_to_update.clear();
        }


        Event* event = hw_event_wait_next();
        if(event->type == ei_ev_keydown)
            quit_request();
    }


    //dans run il faut parcourir tout les widget et les dessiner une fois, ensuite redessiner que ceux qui sont update en parcourant les enfants
    // c'est aux enfant de le faire, run n'appelle qu'une fois draw sur la racine.

}
void Application::quit_request()
{
    running = EI_FALSE;
}

void Application::invalidate_rect(const Rect &rect)
{
    rect_to_update.push_back(rect);
}

Application::~Application()
{
    delete _root_widget  ;
    // Free hardware resources.
    hw_quit();
}

}
