#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    string input_file = "";
    string output_file = "";
    int row_counter = 1;

    cout << "Input file: ";
    getline(cin, input_file);
    cout << "Output file: ";
    getline(cin, output_file);

    ifstream file_object_input(input_file);


    if (not file_object_input) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        string row;
        ofstream file_object_output(output_file);
        while (getline(file_object_input, row)) {
            file_object_output << row_counter << " " << row << endl;
            row_counter += 1;
        }
        file_object_output.close();
    }
    file_object_input.close();



    return EXIT_SUCCESS;
}
