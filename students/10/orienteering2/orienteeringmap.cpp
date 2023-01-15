#include "orienteeringmap.hh"
#include "point.hh"
#include <iostream>
#include <cmath>
#include <iomanip>


OrienteeringMap::OrienteeringMap()
{

}

OrienteeringMap::~OrienteeringMap()
{
    for (auto& i:points_) {
        delete i.second;
    }
}

void OrienteeringMap::set_map_size(int width, int height)
{
    width_ = width;
    height_ = height;
}

void OrienteeringMap::add_point(std::string name, int x, int y, int height, char marker)
{
    Point *point = new Point(name, x, y, height, marker);
    points_.insert({name, point});
}

bool OrienteeringMap::connect_route(std::string from, std::string to, std::string route_name)
{
    // if route exists point pushed back to the map routes at route_name
    // else created new vector and pushed back both from and to
    if (routes_.find(route_name) != routes_.end()) {
        routes_.at(route_name).push_back(points_.at(to));
    } else {
        std::vector<Point*> temp;
        temp.push_back(points_.at(from));
        routes_.insert({route_name, temp});
        routes_.at(route_name).push_back(points_.at(to));
    }
    return true;
}

void OrienteeringMap::print_map() const
{
    std::vector<char> temp(height_, '.');
    std::vector<std::vector<char>> map(width_, temp);

    // puts points in to the map
    for (auto& i:points_) {
        map.at(i.second->get_x()-1).at(i.second->get_y()-1) = i.second->get_marker();
    }

    // prints the first number line
    std::cout << "  ";
    for (int i = 0; i < width_; ++i) {
        if (i > 8) {
            std::cout << (i+1) << " ";
        }else {
            std::cout << " " << (i+1) << " ";
        }
    }

    // rest of the map
    std::cout << std::endl;
    for (int j = 0; j < height_; ++j) {
        if ((j+1) > 9) {
            std::cout << (j+1) << " ";
        }else {
            std::cout << " " << (j+1) << " ";
        }
        for (int i = 0; i < width_; ++i) {
            std::cout << " " << map.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

}

void OrienteeringMap::print_routes() const
{
    std::cout << "Routes:" << std::endl;
    for (auto& i:routes_) {
        std::cout << " - " << i.first << std::endl;
    }
}

void OrienteeringMap::print_points() const
{
    std::cout << "Points:" << std::endl;
    for(auto& i:points_) {
        std::cout << " - " << i.first << " : ";
        i.second->print_marker();
        std::cout << std::endl;
    }
}

void OrienteeringMap::print_route(const std::string &name) const
{
    if (routes_.find(name) != routes_.end()) {
        // prints the startin point with out "->"
        routes_.at(name).at(0)->print_name();
        std::cout << std::endl;
        for (unsigned int i = 1; i < routes_.at(name).size(); ++i) {
            std::cout << " -> ";
            routes_.at(name).at(i)->print_name();
            std::cout << std::endl;
        }
    } else {
            std::cout << "Error: Route named " << name << " can't be found" << std::endl;
        }
}

void OrienteeringMap::route_length(const std::string &name) const
{
    if (routes_.find(name) != routes_.end()) {
        float lenght = 0;

        for (unsigned long i = 0; i < routes_.at(name).size()-1; ++i) {
            lenght += std::sqrt(std::pow(routes_.at(name).at(i)->get_x()
                    - routes_.at(name).at(i+1)->get_x(),2) +std::pow(routes_.at(name).at(i)->get_y()
                    - routes_.at(name).at(i+1)->get_y(),2));
        }
        std::cout << std::setprecision(2) << "Route " << name << " length was " << lenght << std::endl;
    } else {
        std::cout << "Error: Route named " << name << " can't be found" << std::endl;
    }

}

void OrienteeringMap::greatest_rise(const std::string &point_name) const
{
    if (points_.find(point_name) == points_.end()) {
        std::cout << "Error: Point named " << point_name << " can't be found" << std::endl;
        return;
    }
    int current_height = points_.at(point_name)->get_height();
    std::map<std::string, int> greatest_rise;

    // goes through all the routes starting from point_name tracking the height if height declines
    // current height is put in a map along with name of route
    for (auto& i:routes_) {
        for (unsigned long j=0; j < i.second.size(); ++j) {
            if (i.second.at(j)->get_name() == point_name) {
                for (unsigned long k = j; k < i.second.size(); ++k) {
                    if (i.second.at(k)->get_height() >= current_height) {
                        current_height = i.second.at(k)->get_height();
                    } else {
                        break;
                    }
                }
                greatest_rise.insert({i.first, current_height});
                current_height = points_.at(point_name)->get_height();
            }
        }
    }
    // calculates the greatest rise
    for (auto& i:greatest_rise) {
        if (i.second >= current_height) {
            current_height = i.second;
        }
    }
    // prints route if route had the greatest rise calculated before
    if (current_height - points_.at(point_name)->get_height() == 0) {
        std::cout << "No route rises after point " << point_name << std::endl;
    } else {
        std::cout << "Greatest rise after point " << point_name << ", "
                  << current_height - points_.at(point_name)->get_height()
                  << " meters, is on route(s):" << std::endl;
        for (auto& i:greatest_rise) {
            if (i.second == current_height) {
                std::cout << " - " << i.first << std::endl;
            }
        }
    }
    greatest_rise.clear();
}


