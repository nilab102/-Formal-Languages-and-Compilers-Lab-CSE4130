#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

string filemaker(string text,regex r,string text2)
{
    string result;
    regex_replace(back_inserter(result), text.begin(), text.end(),
                  r, text2);
    return result;
}
int main()
{
    fstream file;
    string  text,temp;
    file.open("input.txt", ios::in | ios::app);
    if (!file.is_open())cout << "No FIle ! Error";
    else
    {
        while (!file.eof())
        {
            getline(file, temp);
            text = text  + temp + "\n";
        }

        regex r1("(.*)(\\/\\/)(.*)");
        text = filemaker(text, r1,"");

        regex r2("(.*)printf(.*)\\(");
        text = filemaker(text, r2,"printf(");

        regex r3("\\\n+");
        text = filemaker(text, r3,"");



        regex r4("(\\/\\*)(.*)(\\*\\/)");
        text = filemaker(text, r4,"");


        regex r5("int( *)main");
        text = filemaker(text, r5," int main");
         cout<<text<<endl;
        file.close();
        file.open("OUTPUT.txt", ios::out | ios::trunc);
        file << text;
        file.close();

    }
}
