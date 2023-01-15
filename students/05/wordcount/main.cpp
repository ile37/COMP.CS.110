#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int main()
{

    cout << "Input file: ";
    string file_name = "";
    cin >> file_name;

    ifstream file_object(file_name);

    if (not file_object) {
        cout << "Error! The file " << file_name << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }else {
        map<string, vector<int>> word_data;
        vector<int> data_holder;
        string row;
        int row_counter = 0;
        string word;
        string mark;


        while (getline(file_object, row)) {
            row_counter += 1;
            row.append(" ");
            for (auto character : row) {


                mark = character;

                if (mark != " ") {
                    word += mark;
                }else {



                    if (word_data.find(word) == word_data.end()) {
                        data_holder.push_back(1);
                        data_holder.push_back(row_counter);
                        word_data.insert({word, data_holder});
                        data_holder.clear();
                        word = "";

                    }else if (word_data.at(word).at(word_data.at(word).size()-1) == row_counter) {
                        word = "";

                    }else {

                        data_holder = word_data.at(word);
                        data_holder.at(0) += 1;
                        data_holder.push_back(row_counter);
                        word_data.erase(word);

                        word_data.insert({word, data_holder});
                        data_holder.clear();
                        word = "";
                    }
                }
            }
        }


        for (auto word : word_data) {

            cout << word.first << " " << word.second.at(0) << ": ";
            for (unsigned long i = 1; i < word.second.size(); ++i) {
                if (i == word.second.size()-1) {
                    cout << word.second.at(i) << endl;
                } else {
                    cout << word.second.at(i) << ", ";
                }
            }

        }
    }

    return EXIT_SUCCESS;
}
