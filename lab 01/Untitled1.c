#include <iostream>
#include <fstream>
#include <regex>
using namespace std;


int main()
{
    fstream file;
    string kat, text, res;
    file.open("file1.txt", ios::in | ios::out | ios::trunc);
    if (!file.is_open())cout << "Eror";
    else
    {
         while (!file.eof())
        {
            getline(file, kat);
            text = text  + kat + "\n";
        }

        regex r1("(\\/\\/) (.*)");
        text = filemaker(text, r1);

        int f1 = text.find("/*");
        int f2 = text.find("*/");
        if (f1 != string::npos)if (f1 != string::npos) text.replace(f1,f2-f1+2,"");

        f1 = text.find("int");
        f2 = text.find("main");
        if (f1 != string::npos)if (f1 != string::npos) text.replace(f1,f2-f1+2," ");


        f1 = text.find("printf");
        f2 = text.find("(");
        if (f1 != string::npos)if (f1 != string::npos) text.replace(f1,f2-f1+2," ");

        int i=0;
        while(i<text.length())
        {
            if(text[i]=='\n' ) text.erase(text.begin() +i);
            i++;
        }

        cout<<text;
    }
}
