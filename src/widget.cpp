#include "ei_widget.h"

namespace ei {

Widget::Widget(const widgetclass_name_t& class_name, Widget* parent)
{
   name = class_name;
   this->parent = parent;

}

Widget::~Widget(){}

void Widget::geomnotify(Rect rect) {}
void Widget::draw(surface_t surface, surface_t pick_surface, Rect *clipper) {}


}
