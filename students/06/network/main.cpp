#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


int print_network(const std::map<std::string, std::vector<std::string>>& network, const std::string& id, int depth) {

    if (network.find(id) != network.end()) {
        for (unsigned long i = 0; i < network.at(id).size(); ++i) {
            if (network.find(id) != network.end()) {
                for (int j = 0; j < depth; ++j) {
                    std::cout << "..";
                }
                std::cout << network.at(id).at(i) << std::endl;
                depth += print_network(network, network.at(id).at(i), depth + 1);
            }
        }
    }
    return 0;
}


int count_network(const std::map<std::string, std::vector<std::string>>& network, const std::string& id, int count) {

    if (network.find(id) != network.end()) {
        for (unsigned long i = 0; i < network.at(id).size(); ++i) {
            if (network.find(network.at(id).at(i)) != network.end()) {
                count += count_network(network, network.at(id).at(i), 1);
            } else {
                count += 1;
            }
        }
    }
    return count;
}


int network_depth(const std::map<std::string, std::vector<std::string>>& network, const std::string& id, int depth) {

    int top_depth = 1;

    if (network.find(id) != network.end()) {
        for (unsigned long i = 0; i < network.at(id).size(); ++i) {
            if (network.find(network.at(id).at(i)) != network.end()) {
                depth += network_depth(network, network.at(id).at(i), 1);
            } else {
                depth += 1;
            }
            if (depth > top_depth) {
                top_depth = depth;
                depth = 0;
            } else {
                depth = 0;
            }
        }
    }
    return top_depth;
}


int main()
{
    std::map<std::string, std::vector<std::string>> network = {};


    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            if (network.find(id1) != network.end()) {
                network.at(id1).push_back(id2);
            } else {

                std::vector<std::string> temp = {};
                temp.push_back(id2);
                network.insert({id1, temp});
            }

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << id << std::endl;
            print_network(network, id, 1);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << count_network(network, id, 0) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << network_depth(network, id, 1) << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
