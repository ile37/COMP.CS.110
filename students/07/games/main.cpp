/*  COMP.CS.100 Project 2: GAME STATISTICS
 * ===============================
 *
 * Description:
 *
 *  Acts as a game statistics with n commands:
 * ALL_GAMES - Prints all known game names
 * GAME <game name> - Prints all players playing the given game
 * ALL_PLAYERS - Prints all known player names
 * PLAYER <player name> - Prints all games the given player plays
 * ADD_GAME <game name> - Adds a new game
 * ADD_PLAYER <game name> <player name> <score> - Adds a new player with the
 * given score for the given game, or updates the player's score if the player
 * already playes the game
 * REMOVE_PLAYER <player name> - Removes the player from all games
 *
 *  The data file's lines should be in format game_name;player_name;score
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * Programmer:
 * Name: Ilari Hietala
 * Student number: H291752
 * Username: hgilhi ( Git-repositor )
 * E-Mail: ilari.hietala@tuni.fi
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;
using Data = map<string, map<string, string>>;
// used to sort in aplhabetical order in functions
bool compareFunction (std::string a, std::string b) {return a<b;}

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split( const std::string& str, char delim = ';' )
{
    std::vector<std::string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str ) {
        if ( current_char == '"' ) {
            inside_quatation = not inside_quatation;
        }
        else if ( current_char == delim and not inside_quatation ) {
            result.push_back("");
        }
        else {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" ) {
        result.pop_back();
    }
    return result;
}

// prints all the games in the data structure
void all_games(const Data& game_data) {

    cout << "All games in alphabetical order:" << endl;

    for (auto& i:game_data) {
        cout << i.first << endl;
    }
}

// prints the players of given game
void game(const Data& game_data, const string game) {

    if (game_data.find(game) != game_data.end()) {
        cout << "Game " << game << " has these scores and players, listed in ascending order:" << endl;

        // finds the top score so it can be the upper limit of the next loop
        int top_score = 0;
        for (auto& i:game_data.at(game)) {
            if (stoi(i.second) > top_score) {
                top_score = stoi(i.second);
            }
        }
        vector<string> names;
        // goes through 0 to top score, if players score matches gets printed
        // if multiple same scores gets first stored in names vector and then printed
        for (int i = 0; i <= top_score; ++i) {
            names.clear();
            for (auto& j:game_data.at(game)) {
                if (stoi(j.second) == i) {
                    names.push_back(j.first);
                }
            }
            if (names.size() > 0) {
                cout << i << " : ";
                for (unsigned long k = 0; k < names.size()-1; ++k ) {
                    cout << names.at(k) << ", ";
                }
                cout << names.at(names.size()-1) << endl;
            }
        }
    } else {
        cout << "Error: Game could not be found." << endl;
    }
}

// prints all players in the data structure
void all_players(const Data& game_data) {

    cout << "All players in alphabetical order:" << endl;

    vector<string> players;
    for(auto& i:game_data) {
        for (auto& j:game_data.at(i.first)) {
            if (find(players.begin(),players.end(),j.first) == players.end()) {
                players.push_back(j.first);
            }
        }
    }
    sort(players.begin(),players.end(), compareFunction);
    for (auto& i:players) {
        cout << i << endl;
    }
}

// prints the games given player plays
void player(const Data& game_data, string player) {

    vector<string> games;
    for (auto& i:game_data) {
        if (i.second.find(player) != i.second.end()) {
            games.push_back(i.first);
        }
    }
    if (games.empty()) {
        cout << "Error: Player could not be found." << endl;
    }
    else {
        cout << "Player " << player <<  " playes the following games:" << endl;
        sort(games.begin(), games.end(), compareFunction);
        for (auto& i:games) {
            cout << i << endl;
        }
    }
}

// adds new games to the data structure
// returns the updated data structure
Data add_game(const Data& game_data, string game) {

    if (game_data.find(game) == game_data.end()) {
        Data data_holder = game_data;
        map<string, string> empty;
        data_holder.insert({game, empty});
        cout << "Game was added." << endl;
        return data_holder;
    }
    else {
        cout << "Error: Already exists." << endl;
        return game_data;
    }
}

// add new player to the data structure or updates an old one
// returns the updated data structure
Data add_player(const Data& game_data, string game, string name, string score) {

    if (game_data.find(game) != game_data.end()) {
        Data data_holder = game_data;
        if (game_data.at(game).find(name) == game_data.at(game).end()) {
            data_holder.at(game).insert({name, score});
            cout << "Player was added." << endl;
            return data_holder;
        }
        else {
            data_holder.at(game).at(name) = score;
            cout << "Player was added." << endl;
            return data_holder;
        }
    }
    else {
        cout << "Error: Game could not be found." << endl;
        return game_data;
    }
}

// removes player from the data structure
// returns the updated data structure
Data remove(const Data& game_data, string player) {

    Data data_holder = game_data;
    vector<string> games;

    for (auto& i:game_data) {
        if (i.second.find(player) != i.second.end()) {
            games.push_back(i.first);
            data_holder.at(i.first).erase(player);
        }
    }
    if (games.empty()) {
        cout << "Error: Player could not be found." << endl;
        return game_data;
    }
    else {
        cout << "Player was removed from all games." << endl;
        return data_holder;
    }
}


int main() {

    Data game_data;
    string input_file = "";

    cout << "Give a name for input file: ";
    getline(cin, input_file);

    ifstream file_object_input(input_file);


    if (file_object_input) {
        string row;
        vector<string> splitted;
        map<string,string> player_score;

        while (getline(file_object_input, row)) {

            splitted = split(row);
            if(splitted.size() != 3) {
                cout << "Error: Invalid format in file." << endl;
                return EXIT_FAILURE;
            }
            if (game_data.find(splitted.at(0)) !=game_data.end()) {
                game_data.at(splitted.at(0)).insert({splitted.at(1),splitted.at(2)});
            } else {
                player_score.insert({splitted.at(1),splitted.at(2)});
                game_data.insert({splitted.at(0), player_score});
                player_score.clear();
            }
        }
    } else {
        cout << "Error: File could not be read." << endl;
        return EXIT_FAILURE;
    }
    file_object_input.close();

    string cmd;
    vector<string> cmd_sep;
    while (true) {
        cout << "games> ";
        getline(cin, cmd);
        cmd_sep = split(cmd, ' ');
        cmd.clear();

        for (auto i:cmd_sep.at(0)) {
            cmd.push_back(toupper(i));
        }
        cmd_sep.at(0) = cmd;

        if (cmd_sep.at(0) == "QUIT") {
            return EXIT_SUCCESS;
        }
        else if (cmd_sep.at(0) == "ALL_GAMES") {
            all_games(game_data);
        }
        else if (cmd_sep.at(0) == "GAME") {
            if (cmd_sep.size() >= 2) {
                game(game_data, cmd_sep.at(1));
            } else {
                cout << "Error: Invalid input." << endl;
            }
        }
        else if (cmd_sep.at(0) == "ALL_PLAYERS") {
            all_players(game_data);
        }
        else if (cmd_sep.at(0) == "PLAYER") {
            if (cmd_sep.size() >= 2) {
                player(game_data, cmd_sep.at(1));
            } else {
                cout << "Error: Invalid input." << endl;
            }
        }
        else if (cmd_sep.at(0) == "ADD_GAME") {
            if (cmd_sep.size() >= 2) {
                game_data = add_game(game_data, cmd_sep.at(1));
            } else {
                cout << "Error: Invalid input." << endl;
            }
        }
        else if (cmd_sep.at(0) == "ADD_PLAYER") {
            if (cmd_sep.size() >= 4) {
                game_data = add_player(game_data, cmd_sep.at(1), cmd_sep.at(2), cmd_sep.at(3));
            } else {
                cout << "Error: Invalid input." << endl;
            }
        }
        else if (cmd_sep.at(0) == "REMOVE") {
            if (cmd_sep.size() >= 2) {
                game_data = remove(game_data, cmd_sep.at(1));
            } else {
                cout << "Error: Invalid input." << endl;
            }
        }
        else {
            cout << "Error: Invalid input." << endl;
        }
        cmd.clear();
        cmd_sep.clear();
    }

    return EXIT_SUCCESS;
}











