#include "ei_widget.h"

namespace ei {

Widget::Widget(const widgetclass_name_t& class_name, Widget* parent)
{
   name = class_name;
   this->parent = parent;

}

Widget::~Widget(){}


}
