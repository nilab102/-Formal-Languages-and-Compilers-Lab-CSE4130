/*Md Nabil Rahman Khan
190104044*/
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>
using namespace std;
string nilab="";
void filemaker2(string text1,string text2)
{
    nilab =nilab+" ["+text2+" "+text1+"] ";

}
string filemaker(string text,regex r,string text2)
{
    string result;
    regex_replace(back_inserter(result), text.begin(), text.end(),
                  r, text2);
    return result;
}
bool isKeyword(string str)						//check if the given substring is a keyword or not
{

    string keyword[]= {"if","else","printf","while","for","do","break,","continue","int","double","float","return","char","case","long","short","typedef","switch","unsigned","void","static","struct","sizeof","long","volatile","enum","const","bool","union","extern"};
    for(int k=0; k< (sizeof keyword / sizeof keyword[0]); k++)
    {

        if(keyword[k].compare(str)==0)return true;
    }
    return false;

}
bool isIdentifier(string str)
{
    regex e("([a-zA-Z_])[a-zA-Z0-9_]{0,31}");
    if (regex_match (str,e))
        return true;
    else return false;
}
bool isNum(string str)
{
    regex e("(\-)?(\\d+(?:\.\\d+)?)");
    if (regex_match (str,e))
        return true;
    else return false;
}
bool isOperand(string str)						//check if the given substring is a keyword or not
{

    string Operand[]= {"+","-", "*","/","++","--",">","<","=","<=",">=","!","!=","%","&&","|","||","==","+=","/=","%=","&=","|=","^=",">>=","<<=",">=","<=","!="};
    for(int k=0; k< (sizeof Operand / sizeof Operand[0]); k++)
    {

        if(Operand[k].compare(str)==0)return true;
    }
    return false;

}
bool isSeparator(string str)						//check if the given substring is a keyword or not
{

    string Separator[]= {",",";","\"","'"};
    for(int k=0; k< (sizeof Separator / sizeof Separator[0]); k++)
    {

        if(Separator[k].compare(str)==0)return true;
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
void regexprint(regex rgx,string text)
{
    string res="";
    for( sregex_iterator it(text.begin(), text.end(), rgx), it_end; it != it_end; ++it )
    {
        if(isKeyword((*it)[0].str()))filemaker2((*it)[0].str(),"Kw");
        else if(isIdentifier((*it)[0].str()))filemaker2((*it)[0].str(),"Id");
        else if(isNum((*it)[0].str()))filemaker2((*it)[0].str(),"Num");
        else if(isOperand((*it)[0].str()))filemaker2((*it)[0].str(),"Op");
        else if(isSeparator((*it)[0].str()))filemaker2((*it)[0].str(),"Sep");
        else if(isPair((*it)[0].str()))filemaker2((*it)[0].str(),"Par");
        else filemaker2((*it)[0].str(),"Unkown");

        //res=res +" " +(*it)[0].str();
    }
    //cout<< res;
}
int main()
{
    fstream file;
    string  text,temp;
    file.open("190104044_input.txt", ios::in | ios::app);
    if (!file.is_open())cout << "No FIle ! Error";
    else
    {
        while (!file.eof())
        {
            getline(file, temp);
            text = text  + temp + "\n";
        }
        regex r0("printf(.*)\\((.*)\\);");
        text = filemaker(text, r0,"printf ( \" \" );");
        cout<<text;

        string operator1[]= { "\\;", "\\+", "\\-","\\'", "\\*","\\/","\\%","\\,","\\=","\\>","\\<","\\&&","\\|","\\!","\\(","\\)","\\&" };
        for(int k=0; k< (sizeof operator1 / sizeof operator1[0]); k++)
        {
            string l=" "+operator1[k].substr(1,operator1[k].size())+" ";
            regex r1(operator1[k]);
            text = filemaker(text, r1,l);
        }
        string operator2[] = {"(\\+)( )*(\\+)","(\\=)( )*(\\=)","(\\+)( )*(\\=)","(\\-)( )*(\\=)","(\\*)( )*(\\=)","(\\/)( )*(\\=)","(\\%)( )*(\\=)","(\\&)( )*(\\=)","(\\|)( )*(\\=)","(\\^)( )*(\\=)","(\\>)( )*(\\>)( )*(\\=)","(\\<)( )*(\\<)( )*(\\=)","(\\>)( )*(\\=)","(\\<)( )*(\\=)","(\\!)( )*(\\=)"};
        string f[]= {"++","==","+=","-=","*=","/=","%=","&=","|=","^=",">>=","<<=",">=","<=","!="};
        for(int k=0; k< (sizeof operator2 / sizeof operator2[0]); k++)
        {
            regex r1(operator2[k]);
            text = filemaker(text, r1,f[k]);
        }
        //DIVING INTO WORDS

        regex r2("(\\S+)");
        regexprint(r2,text);
        cout<<nilab;


        file.close();
        file.open("OUTPUTlAB2.txt", ios::out | ios::trunc);
        file << nilab;
        file.close();

    }
}
