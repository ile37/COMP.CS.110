/* Hitori
 *
 *Description:
 *
 *   Program mimics Hitori-game. The game has a 5 x 5 square each square
 * containing a number between 1 and 5. The purpose of the game is to eliminate
 * numbers so that in the end no number is shown twice in any row or column.
 * This has to be done without removing two adjacent numbers or disconnecting
 * a number from all four sides.
 *   In the beginning user is asked if the board will be filled with random numbers
 * or the user can input 25 numbers. the first option will be followed with the asking
 * of a seed number.
 *   Each turn the player is asked to remove one number via x and y cordinates.
 * The game ends in a victory if no number is shown twice in any row or column. And in
 * defeat if adjacent number are removed or a number is disconnected from it's
 * connecting numbers.
 *   Program checks the given cordinates, they need to be inside the game board
 * and the square can't be allready empty.
 *   At the end the program tells if the game ended with victory or defeat.
 *
 * Programmer:
 * Name: Ilari Hietala
 * Student number: H291752
 * Username: hgilhi ( Git-repositor )
 * E-Mail: ilari.hietala@tuni.fi
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
#include <random>

using namespace std;

const unsigned int BOARD_SIDE = 5;
const unsigned char EMPTY = ' ';

// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i) {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric) {
        return stoi(str);
    } else {
        return 0;
    }
}

// Prints the game board with row and column numbers.
void print(const vector< vector<int>>& gameboard)
{
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for(unsigned int i = 0; i < BOARD_SIDE; ++i) {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < BOARD_SIDE; ++j) {
            if(gameboard.at(i).at(j) == 0)
            {
                cout << EMPTY << " ";
            } else {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}


string random_board(int seed) {

    string board_input;
    int lower_limit = 1;
    int upper_limit = BOARD_SIDE;

    // random generator engine and setting
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(lower_limit, upper_limit);

    // creates random board number line
    for (unsigned int i = 1; i <= BOARD_SIDE*BOARD_SIDE; i++) {
        board_input += to_string(distr(gen));
    }

    return board_input;
}


vector< vector<int>> create_board(string board_line) {

    vector< vector<int>> board;
    vector< int> row;

    int column_counter = 0;
    string row_str;

    for (unsigned int i = 0; i < BOARD_SIDE*BOARD_SIDE; i++) {
        row_str.push_back(board_line.at(i));
        column_counter += 1;
        if (column_counter == BOARD_SIDE) {
            for (auto i : row_str) {
                // char type numbers underlying value is rectifyed with -48
                row.push_back(i - 48);
            }
            board.push_back(row);
            row.clear();
            row_str.clear();
            column_counter = 0;
        }
    }
    return board;

}


bool is_lost(const vector<vector<int>>& board) {

    vector<vector<int>> current_board = board;
    vector<vector<int>> rotated_board;
    vector<int> rotated_row;

    // checks for lost pattern by rotateing the board
    for (unsigned int d = 0; d < 4; ++d) {
        for(unsigned int i = 0; i < BOARD_SIDE; ++i){
            for(unsigned int j = 0; j < BOARD_SIDE; ++j) {
                // vertical double zeros
                if (i > 0) {
                    if (current_board.at(i-1).at(j) == 0 and current_board.at(i).at(j) == 0) {
                        return true;
                    }
                // horizontal double zeros
                } if (j < 4) {
                    if (current_board.at(i).at(j) == 0 and current_board.at(i).at(j+1) == 0) {
                        return true;
                    }
                // top row has an isolated number, not corner
                } if (i == 0 and j != 0 and j != 4) {
                    if (current_board.at(i).at(j-1) == 0 and current_board.at(i).at(j+1) == 0 and current_board.at(i+1).at(j) == 0) {
                        return true;
                    }
                // 4 sides empty
                } if (i > 0 and i < 4 and j > 0 and j < 4) {
                    if (current_board.at(i-1).at(j) == 0 and current_board.at(i).at(j-1) == 0 and current_board.at(i).at(j+1) == 0 and current_board.at(i+1).at(j) == 0) {
                        return true;
                    }
                // corner number isolated
                } if (current_board.at(0).at(1) == 0 and current_board.at(1).at(0) == 0) {
                    return true;
                }
            }
        }
        // rotates the board for easier losing pattern checking
        for (unsigned int a = BOARD_SIDE; a-- > 0;) {
            for (unsigned int b = 0; b < BOARD_SIDE; ++b) {
                rotated_row.push_back(current_board.at(b).at(a));
            }
            rotated_board.push_back(rotated_row);
            rotated_row.clear();
        }
        current_board = rotated_board;
        rotated_board.clear();
    }

    return false;
}


bool is_won(const vector<vector<int>>& board) {
    // Game is won if no row or column has the same number twice
    vector<int> win_check;

    // horizontal win check
    for (unsigned int i = 0; i < BOARD_SIDE; i++) {
        for (unsigned int j = 0; j < BOARD_SIDE; j++) {
            if (find(win_check.begin(), win_check.end(), (board.at(i).at(j))) != win_check.end()) {
                return false;
            } else {
                if (board.at(i).at(j) != 0) {
                    win_check.push_back(board.at(i).at(j));
                }
            }
        }
        win_check.clear();
    }

    // vertical win check
    for (unsigned int i = 0; i < BOARD_SIDE; i++) {
        for (unsigned int j = 0; j < BOARD_SIDE; j++) {
            if (find(win_check.begin(), win_check.end(), board.at(j).at(i)) != win_check.end()) {
                return false;
            } else {
                if (board.at(j).at(i) != 0) {
                    win_check.push_back(board.at(j).at(i));
                }
            }
        }
        win_check.clear();
    }

    return true;

}


int main()
{
    vector< vector<int>> board;
    string board_line;
    string input;
    // Selects witch type of board the game will use random/input
    // And creats a string number line for board creation
    while (true) {
        cout << "Select start (R for random, I for input): ";
        getline(cin, input);
        if (input == "r" or input == "R") {
            cout << "Enter seed value: ";
            int seed;
            cin >> seed;
            board_line = random_board(seed);
            break;
        } else if (input == "i" or input == "I") {
            cout << "Input: ";
            getline(cin, board_line);
            board_line.erase(remove(board_line.begin(), board_line.end(), ' '), board_line.end());
            break;
        }
    }

    board = create_board(board_line);
    print(board);

    string x_str;
    string y_str;

    while (true) {
        cout << "Enter removable element (x, y): ";
        cin >> x_str;
        if (x_str == "q" or x_str == "Q") {
            cout << "Quitting" << endl;
            return 0;
        }
        cin >> y_str;

        unsigned int x = stoi_with_check(x_str);
        unsigned int y = stoi_with_check(y_str);

        // if x/y is not a number returns as 0 witch is outside board
        if (x < 1 or x > BOARD_SIDE or y < 1 or y > BOARD_SIDE) {
            cout << "Out of board" << endl;
        } else if (board.at(y-1).at(x-1) == 0) {
            cout << "Already removed" << endl;
        } else {
            board.at(y-1).at(x-1) = 0;
            print(board);
        }

        // check if game has ended
        if (is_lost(board)) {
            cout << "You lost" << endl;
            return 0;
        } else if (is_won(board)) {
            cout << "You won" << endl;
            return 0;
        }
    }
    return 0;
}









