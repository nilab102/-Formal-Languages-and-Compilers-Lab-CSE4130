
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 3;

int main()
{
    // Open the symbol table file
    ifstream file("symbolTable.txt");

    // Initialize the array to store the symbol table
    string symbol_table[MAX_ROWS][MAX_COLS];

    // Read the contents of the file into the array
    int row = 0;
    string line;
    while (getline(file, line))
    {
        int col = 0;
        size_t pos = 0;
        string token;
        while ((pos = line.find(" ")) != string::npos)
        {
            token = line.substr(0, pos);
            symbol_table[row][col] = token;
            line.erase(0, pos + 1);
            col++;
        }
        symbol_table[row][col] = line;
        row++;
    }

    // Get the position of the row to be inserted
    int position;
    cout << "Enter the position of the row to be inserted: ";
    cin >> position;

    // Get the values of the new row
    string new_row[MAX_COLS];
    cout << "Enter the values of the new row (separated by spaces): ";
    for (int i = 0; i < MAX_COLS; i++)
    {
        cin >> new_row[i];
    }

    // Shift all the elements after the inserted row down by one
    for (int i = row; i >position; i--)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            symbol_table[i][j] = symbol_table[i - 1][j];
        }
    }// Insert the new row
    for (int i = 0; i < MAX_COLS; i++)
    {
        symbol_table[position][i] = new_row[i];
    }
    row++;

// Open the updated symbol table file
    ofstream output_file("updatedSymbolTable.txt");

// Write the array to the updated symbol table file
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            output_file << symbol_table[i][j] << " ";
        }
        output_file << endl;
    }
    output_file.close();

// Print the symbol table
    cout << "Symbol Table has been saved to updatedSymbolTable.txt" << endl;

    return 0;
}
