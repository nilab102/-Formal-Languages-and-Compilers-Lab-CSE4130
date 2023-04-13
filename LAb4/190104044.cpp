#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>
using namespace std;

bool isKeyword(string str)						//check if the given substring is a keyword or not
{

    string keyword[]= {"if","else","printf","while","for","do","break,","continue","int","double","float","return","char","case","long","short","typedef","switch","unsigned","void","static","struct","sizeof","long","volatile","enum","const","bool","union","extern"};
    for(int k=0; k< (sizeof keyword / sizeof keyword[0]); k++)
    {

        if(keyword[k].compare(str)==0)return true;
    }
    return false;

}
bool areBracketsBalanced(string expr)
{
    // Declare a stack to hold the previous brackets.
    stack<char> temp;
    for (int i = 0; i < expr.length(); i++)
    {
        if (temp.empty())
        {

            // If the stack is empty
            // just push the current bracket
            temp.push(expr[i]);
        }
        else if ((temp.top() == '(' && expr[i] == ')')
                 || (temp.top() == '{' && expr[i] == '}')
                 || (temp.top() == '[' && expr[i] == ']'))
        {

            // If we found any complete pair of bracket
            // then pop
            temp.pop();
        }
        else
        {
            temp.push(expr[i]);
        }
    }
    if (temp.empty())
    {
        // If stack is empty return true
        return true;
    }
    return false;
}
bool isPair(string str)						//check if the given substring is a keyword or not
{

    string Pair[]= {"(",")","{","}","[","]"};
    for(int k=0; k< (sizeof Pair / sizeof Pair[0]); k++)
    {

        if(Pair[k].compare(str)==0)return true;
    }
    return false;

}
void errorFinder(regex rgx,string text)
{

    string totalparanthesis;
    string lineno="-1";
    bool parenthesis=true;
    bool semicolon=true;
    string lastwordtochecksemicolon;
    string lastkeyword;
    bool keywordtokrn=true;
    int ifcount=0;
    bool existif=false;
    for( sregex_iterator it(text.begin(), text.end(), rgx), it_end; it != it_end; ++it )
    {
        string temp=(*it)[0].str();
        if (temp.find("Xacn420k") != string::npos)lineno = temp[0];
        if(isPair((*it)[0].str())&&parenthesis)
        {
            totalparanthesis=totalparanthesis+" "+temp;
            if(temp.compare("}")==0 )
            {
                if(!areBracketsBalanced(totalparanthesis))cout<<" Misplaced at Line  "<<lineno<<",";
                parenthesis=false;
            }

        }
        if(temp.compare(lastwordtochecksemicolon)==0 && temp.compare(";")==0 && semicolon)
        {
            cout<<" Duplicate token at line   "<<lineno<<", ";
            semicolon=false;
        }


        if(temp.compare(lastkeyword)==0  && keywordtokrn && isKeyword(temp))
        {
            cout<<" Duplicate keyword at line   "<<lineno<<", ";
            keywordtokrn=false;
        }



        if(temp.compare("if")==0)
        {
            //ifcount++;
            existif=true;
        }
        //if(temp.compare("}")==0 && existif &&ifcount>0)ifcount--;
        if(temp.compare("else")!=0 && existif )existif=false;
        else if(temp.compare("else")==0 && existif==false )
        {
            cout<<" Error at line "<<lineno<<",";
        }
        else if(temp.compare("else")==0 && existif )existif=false;




        lastkeyword=temp;
        lastwordtochecksemicolon=temp;
    }

}

int main()
{
    fstream file;
    string  text,temp;
    file.open("input.txt", ios::in | ios::app);
    int i=0;
    if (!file.is_open())cout << "No FIle ! Error";
    else
    {
        while (!file.eof())
        {
            i++;
            getline(file, temp);
            text = text + to_string(i)+"Xacn420k"+" "+temp + "\n";
        }


        cout<<text<<endl;

        regex r2("(\\S+)");
        errorFinder(r2,text);

        file.close();
        file.open("OUTPUT.txt", ios::out | ios::trunc);
        file << text;
        file.close();

    }
}










/*


void dupidentifier(regex rgx, string text)
{

    string last_kwd="";
    string scope_="global";
    string prev_id="";
    string isBalanaced="";
    for( sregex_iterator it(text.begin(), text.end(), rgx), it_end; it != it_end; ++it )
    {
       string temp=(*it)[0].str();
        if(isPair((*it)[0].str()))
        {
            if(temp.compare("}")==0 || temp.compare("{")==0)isBalanaced=isBalanaced+temp;
            if(temp.compare("(") ==0 && areBracketsBalanced(isBalanaced))scope_=prev_id;
            if(temp.compare("}")==0 && areBracketsBalanced(isBalanaced))scope_="global";

        }

        else if(isIdentifier((*it)[0].str()))
        {
            if(temp.compare("Id")==0);
            else
            {
                prev_id=temp;
            }

        }

        if(!temp.compare("]")==0 && !temp.compare("[")==0 && !temp.compare("Id")==0)last_kwd=temp;
        //res=res +" " +(*it)[0].str();
    }


}

*/








