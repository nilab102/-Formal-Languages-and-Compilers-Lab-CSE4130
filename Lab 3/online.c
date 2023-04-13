#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 3;

int main() {
    // Open the symbol table file
    ifstream file("symbolTable.txt");

    // Initialize the array to store the symbol table
    string symbol_table[MAX_ROWS][MAX_COLS];

    // Read the contents of the file into the array
    int row = 0;
    string line;
    while (getline(file, line)) {
        int col = 0;
        size_t pos = 0;
        string token;
        while ((pos = line.find(" ")) != string::npos) {
            token = line.substr(0, pos);
            symbol_table[row][col] = token;
            line.erase(0, pos + 1);
            col++;
        }
        symbol_table[row][col] = line;
        row++;
    }

    // Print the symbol table
    cout << "Symbol Table:" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            cout << symbol_table[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
