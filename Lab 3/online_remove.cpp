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

    // Get the position of the row to be removed
    int position;
    cout << "Enter the position of the row to be removed: ";
    cin >> position;

    // Remove the row by shifting all the elements after the removed row up by one
    for (int i = position; i < row - 1; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            if(j==0)symbol_table[i][j]=to_string(i+1);
            else symbol_table[i][j] = symbol_table[i + 1][j];
        }
    }
    row--;


    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < MAX_COLS; j++) cout<<symbol_table[i][j]<<" ";

        cout<<endl;
    }









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
