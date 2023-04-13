/*Md Nabil Rahman Khan
190104044*/
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>
using namespace std;
const int ROW = 50;
const int COL = 6;
string symbol_table[50][6];
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
string filemaker(string text,regex r,string text2)
{
    string result;
    regex_replace(back_inserter(result), text.begin(), text.end(),
                  r, text2);
    return result;
}
string filemaker_1(regex rgx,string text)
{
    string keyword[]= {"Kw","Num","Op","Sep","Par","brc"};
    string res="";
    bool flag =true;
    for( sregex_iterator it(text.begin(), text.end(), rgx), it_end; it != it_end; ++it )
    {
        flag =true;
        for(int k=0; k< (sizeof keyword / sizeof keyword[0]); k++)
        {

            if(keyword[k].compare((*it)[0].str())==0) flag=false;//res=res +" " +(*it)[0].str();

        }
        if(flag)res=res +" " +(*it)[0].str();
    }
    return res;

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

bool isOperand(string str)						//check if the given substring is a keyword or not
{

    string Operand[]= {"+","-", "*","/","++","--",">","<","=","<=",">=","!","!=","%","&&","|","||","==","+=","/=","%=","&=","|=","^=",">>=","<<=",">=","<=","!="};
    for(int k=0; k< (sizeof Operand / sizeof Operand[0]); k++)
    {

        if(Operand[k].compare(str)==0)return true;
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

string  tablemaker_(regex rgx,string text)
{
    string temp;
    int r=0,c=0;
    string function_list[20];
    int fl=0;
    for( sregex_iterator it(text.begin(), text.end(), rgx), it_end; it != it_end; ++it )
    {
        temp=(*it)[0].str();
        if( temp.compare("Id")==0 || temp.compare("[")==0  || temp.compare("]")==0 || temp.compare("{")==0 || temp.compare("}")==0 );//IGNORE [] ID// || temp.compare("return")==0 || temp.compare("void")==0
        else
        {
            if(isKeyword(temp))
            {
                c=3;
                symbol_table[r][c]=temp;
            }

            else if(isIdentifier(temp))
            {
                for(int k1=0; k1<=fl; k1++)
                    if(function_list[k1].compare(temp)==0)
                    {
                        r++;
                        break;
                    }

                c=1;
                symbol_table[r][c]=temp;
            }
            else if(temp.compare("=")==0 )
            {
                c=2;
                symbol_table[r][c]="var";
            }
            else if(temp.compare(")")==0   )
            {
                c=2;
                symbol_table[r][c]="var";
                r++;
            }
            else if(temp.compare("(")==0 )
            {
                c=2;
                symbol_table[r][c]="func";
                r++;
                //registerfunctionlist
                function_list[fl]= symbol_table[r-1][1];
                fl++;
            }
            else if(isNum(temp))
            {
                c=5;
                symbol_table[r][c]=temp;
            }
            else if(temp.compare(";")==0)
            {
                r++;
            }
            // cin>>symbol_table[i][j];
        }
    }
    cout<<endl;
    int newrow=r;
    //SETIING SCOPE
    string tempscope="global";
    for(int i=0; i<newrow; i++)
    {

        if( symbol_table[i][2].compare("func")==0)
        {
            tempscope=symbol_table[i][1];
            symbol_table[i][4]="global";

        }
        else
            symbol_table[i][4]=tempscope;

    }
//merging
    for(int i=0; i<newrow; i++)
    {
        for(int j=i+1; j<newrow; j++)
        {
            if(symbol_table[i][1]==symbol_table[j][1] && symbol_table[i][4]==symbol_table[j][4] )
            {
                for(int kl=0; kl<COL; kl++)
                {
                    if(symbol_table[i][kl].compare("-404")==0) symbol_table[i][kl]= symbol_table[j][kl];
                }
            }
        }
    }

    string clean_table[ROW];
    string sy_table[newrow][COL];
    int c_table=0;
    int st_r=0;
    bool flag=true;
    for(int i=0; i<newrow; i++)
    {
        flag=true;
        for(int kc=0; kc<=c_table; kc++)
        {

            if(clean_table[kc].compare(symbol_table[i][1]+symbol_table[i][4])==0 || symbol_table[i][3].compare("return")==0 || symbol_table[i][3].compare("void")==0 || symbol_table[i][3].compare("-404")==0)
            {
                flag=false;
                break;
            }
        }
        if(flag)
        {
            for(int j=0; j<COL; j++)
            {
                if(symbol_table[i][j].compare("-404")==0) sy_table[st_r][j]=" ";
                else  sy_table[st_r][j]=symbol_table[i][j];

            }
            sy_table[st_r][0]=to_string(st_r+1);;
            clean_table[c_table]=symbol_table[i][1]+symbol_table[i][4];
            c_table++;
            st_r++;
        }
    }
    //

    for(int i=0; i<st_r; i++)
    {
        for(int j=0; j<COL; j++)
        {
            //if(symbol_table[i][3].compare("return")==0 || symbol_table[i][3].compare("void")==0)break;
            cout<<sy_table[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout<<text<<"o------k";


    string last_kwd="";
    string scope_="global";
    string unique_idlist[50];
    int ul_size=0;
    int uq_idIndex=0;
    string final_text="";
    string prev_id="";
    int index_of_searching=0;
    string isBalanaced="";
    string last_word="";
    flag=false;
    bool flag2=true;
    for( sregex_iterator it(text.begin(), text.end(), rgx), it_end; it != it_end; ++it )
    {
        temp=(*it)[0].str();
        flag2=true;
        //if(isKeyword(temp) && !(temp.compare("void")==0 || temp.compare("return")==0)){kwd=temp;cout<<kwd<<endl;}


        if(isKeyword((*it)[0].str()))final_text=final_text+" "+temp;
        else if(isNum((*it)[0].str()))final_text=final_text+" "+temp;
        else if(isOperand((*it)[0].str()))final_text=final_text+" "+temp;
        else if(isSeparator((*it)[0].str()))final_text=final_text+" "+temp;
        else if(isPair((*it)[0].str()))
        {
            final_text=final_text+" "+temp;
            if(temp.compare("}")==0 || temp.compare("{")==0)isBalanaced=isBalanaced+temp;
            if(temp.compare("(") ==0 && areBracketsBalanced(isBalanaced))scope_=prev_id;
            if(temp.compare("}")==0 && areBracketsBalanced(isBalanaced))scope_="global";



        }

        else if(isIdentifier((*it)[0].str()))
        {
            if(temp.compare("Id")==0)final_text=final_text+" "+temp;
            else
            {
                prev_id=temp;
                flag=false;
                //searching
                index_of_searching=0;


                if(isIdentifier(temp) && !isKeyword(last_kwd) && last_word.compare("Id")==0)
                {

                    for(int utl=0; utl<COL; utl++)
                    {
                       // cout<<temp<<" "<<sy_table[utl][0]<<endl;

                        if(sy_table[utl][1].compare(temp)==0 && sy_table[utl][2].compare("func")==0)
                        {
                            final_text=final_text+" "+sy_table[utl][0];
                            flag2=false;

                        }


                    }

                }


                if(flag2)
                {

                    for(int utl=0; utl<=ul_size; utl++)
                    {

                        if(unique_idlist[utl].compare(scope_+temp)==0)
                        {
                            flag=true;
                            index_of_searching=utl;
                            break;
                        }

                    }
                    if(flag)
                    {
                        final_text=final_text+" "+to_string(index_of_searching+1);
                    }
                    else
                    {
                        unique_idlist[uq_idIndex]=scope_+temp;
                        uq_idIndex++;
                        final_text=final_text+" "+to_string(uq_idIndex);
                        ul_size++;
                    }

                }





            }

        }

        if(!temp.compare("]")==0 && !temp.compare("[")==0 && !temp.compare("Id")==0)last_kwd=temp;
        if(!temp.compare("]")==0 && !temp.compare("[")==0)last_word=temp;
        //res=res +" " +(*it)[0].str();
    }
    cout<<endl<<final_text;
    return final_text;
}
int main()
{
    fstream file;
    string  text,temp;
    file.open("testinput.txt", ios::in | ios::app);
    if (!file.is_open())cout << "No FIle ! Error";
    else
    {
        while (!file.eof())
        {
            getline(file, temp);
            text = text  + temp + "\n";
        }

        regex r2("(\\S+)");
        text=filemaker_1(r2,text);
        //cout<<text<<"o------k";


        for(int i=0; i<ROW; i++)
        {
            for(int j=0; j<COL; j++)
            {
                symbol_table[i][j]="-404";
            }
        }
        text=tablemaker_(r2,text);
        file.close();
        file.open("OUTPUTlAB2.txt", ios::out | ios::trunc);
        file << text;
        file.close();

    }
}
