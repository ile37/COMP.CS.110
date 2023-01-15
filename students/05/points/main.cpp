#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {

    cout << "Input file: ";
    string file_name = "";
    cin >> file_name;

    ifstream file_object(file_name);

    if (not file_object) {
        cout << "Error! The file " << file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }else {
        cout << "Final scores:" << endl;
        string row;
        string name;
        int score;
        map<string, int> player_scores;
        while (getline(file_object, row)) {

            name = row.substr(0,row.find(":"));
            score = stoi(row.substr(row.find(":")+1,row.length()-1));

            if (player_scores.find(name) != player_scores.end()) {
                player_scores.at(name) += score;
            } else {
                player_scores.insert({name, score});
            }
        }
        for (auto data_pair : player_scores) {
            cout << data_pair.first << ": " << data_pair.second << endl;
        }
    }



    return EXIT_SUCCESS;
}
