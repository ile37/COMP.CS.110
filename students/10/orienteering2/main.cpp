/* Orienteering
 *
 * Desc:
 *
 * Program that collects orienteeringmap data about points and routes
 * to display them in an orderly fashion.
 *  MAP - prints a map of the points in a square of given diameter.
 *  ROUTES - prinst a list of all the routes.
 *  ROUTE - prints the route of the given prarameter.
 *  POINTS - prints all the points in alphabetical order
 *  LENGTH - calculates and prints the length of the route given as a parameter
 *  RISE - calculates and prints the greatest continuous rise starting from point
 *  given as a parameter, checking all the routes the point is in.
 *
 * Programmer:
 * Name: Ilari Hietala
 * Student number: H291752
 * Username: hgilhi ( Git-repositor )
 * E-Mail: ilari.hietala@tuni.fi
 *
 * Notes about the program and it's implementation:
 *  Class point perhaps would have been more practical to
 *  have been greate a struct. Point data only stored in class point (excluding
 *  the names of the points)
 *
 * */

#include "orienteeringmap.hh"
#include "parser.hh"
#include "cli.hh"
#include <iostream>

int main()
{
    std::shared_ptr<OrienteeringMap> routes(new OrienteeringMap);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if( not read_input_from_file(input, routes) )
    {
        return EXIT_FAILURE;
    }


    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


