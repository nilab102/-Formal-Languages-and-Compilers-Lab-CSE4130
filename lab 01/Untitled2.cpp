#include <iostream>
#include <fstream>
#include <regex>
using namespace std;
string filemaker(string text,regex r,string res)
{
    string result;
    regex_replace(back_inserter(result), text.begin(), text.end(),
                  r, res);
    return result;
}
int main()
{
    fstream file;
    string kat, text, res;
    file.open("input.txt", ios::in | ios::app);
    if (!file.is_open())cout << "Eror";
    else
    {
        while (!file.eof())
        {
            getline(file, kat);
            text = text  + kat + "\n";
        }
        regex r1("(.*)(\\/\\/)(.*)");
        text = filemaker(text, r1,"");

        int  f1 = text.find("int");
        int  f2 = text.find("main");
        if (f1>=0)if (f2 >=0) text.replace(f1+3,f2-(f1+3)," ");

        f1=-1;
        f2=-1;

        f1 = text.find("/*");
        f2 = text.find("*/");
        if (f1>=0)if (f2 >=0) text.replace(f1,f2-f1+2,"");

        regex r2("(.*)printf(.*)\\(");
        text = filemaker(text, r2,"printf(");

        regex r3("\\\n+");
        text = filemaker(text, r3,"");
        cout<<text;
        file.close();
        file.open("OUTPUT.txt", ios::out| ios::trunc);
        file << text;
        file.close();

    }
}
