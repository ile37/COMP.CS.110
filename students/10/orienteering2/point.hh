#ifndef POINT_H
#define POINT_H

#include <string>


class Point
{
public:
    Point(std::string name, int x, int y, int height, char marker);
    ~Point();

    void print_marker();

    void print_name();

    std::string get_name();

    int get_x();

    int get_y();

    int get_height();

    char get_marker();

private:
    std::string name_;
    int x_;
    int  y_;
    int height_;
    char marker_;
};

#endif // POINT_H
