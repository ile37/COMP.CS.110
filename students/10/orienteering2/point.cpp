#include "point.hh"
#include <iostream>


Point::Point(std::string name, int x, int y, int height, char marker):
    name_(name), x_(x), y_(y), height_(height), marker_(marker)
{

}

Point::~Point()
{

}

void Point::print_marker()
{

    std::cout << marker_;
}

void Point::print_name()
{
    std::cout << name_;
}

std::string Point::get_name()
{
    return name_;
}

int Point::get_x()
{
    return x_;
}

int Point::get_y()
{
    return y_;
}

int Point::get_height()
{
    return height_;
}

char Point::get_marker()
{
    return marker_;
}
