#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>
using namespace std;
const int ROW = 50;
const int COL = 6;
string symbol_table[ROW][COL];
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
    /*
    This function is used to replace all occurrences of a regular expression in a given text with a specified replacement text.
    It takes in 3 parameters:

    "text" which is the original text in which the replacement will be done.
    "r" which is the regular expression that will be searched for in the text.
    "text2" which is the replacement text that will be used to replace all occurrences of the regular expression in the text.
    It uses the "regex_replace" function from the C++ STL which is a part of the <regex> library, this function will perform the replacement operation.
    The function first creates an empty string variable called "result" and then uses the "regex_replace" function to replace all occurrences of the regular expression "r" in the text "text" with the replacement text "text2" and store the result in the "result" variable.
    Then the function returns the modified text.

    In summary, this function is used to replace all occurrences of a regular expression in a given text with a specified replacement text. It uses the regex_replace function from the C++ STL to perform the replacement operation.
    */
    return result;
}
string filemaker_2(regex rgx,string text)
{
    string keyword[]= {"Kw","Num","Op","Sep","Par","brc"};
    string res="";
    bool flag =true;
    for( sregex_iterator it(text.begin(), text.end(), rgx), it_end; it != it_end; ++it )
    {
        /*sregex_iterator it(text.begin(), text.end(), rgx): This creates an instance of the sregex_iterator class called "it" and initializes it with the text to be searched and the regular expression (rgx) to be used for the search. The text.begin() and text.end() represents the start and end of the text to be searched.
        sregex_iterator it_end: This creates an instance of the sregex_iterator class called "it_end", which is used as the end condition for the loop.
        it != it_end: This is the loop's end condition and it checks whether the iterator (it) has reached the end of the matches (it_end). The loop will continue to run until this condition is no longer true.
        ++it: This is the loop's increment statement and it is used to move the iterator (it) to the next match found in the text after each iteratio
        */
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
    /*
    [a-zA-Z_]: matches the first character of the variable name and must be an uppercase or lowercase letter or an underscore.
    [a-zA-Z0-9_]{0,31}: matches the remaining characters of the variable name, which can be an uppercase or lowercase letter, a digit or an underscore, and can be between 0 to 31 characters long.
    */
    if (regex_match (str,e))
        return true;
    else return false;
}
bool isNum(string str)
{
    regex e("(\-)?(\\d+(?:\.\\d+)?)");
    /*
    (\-)?: an optional hyphen, which indicates that the number may be negative
    \\d+: one or more digits, which make up the whole part of the number
    (?:\.\\d+)?: an optional decimal point followed by one or more digits, which make up the fractional part of the number.
    */
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
    /*
    The first thing it does is check if the matched string is one of the following: "Id", "[", "]", "{", "}", if so, it does nothing and continues to the next iteration.

    If the matched string is not one of the above, it checks if the matched string is a keyword or not by calling the function isKeyword(temp) if it returns true then it sets the symbol_table[r][c] to the matched string, where r and c are counters.

    if the matched string is not a keyword then it checks if it is an identifier or not by calling the function isIdentifier(temp) and if it returns true then it checks if the matched string is already in the function_list by calling function_list[k1].compare(temp) and if it returns true, it increments the row counter (r) and continues to the next iteration, otherwise it sets the symbol_table[r][c] to the matched string.

    if the matched string is not an identifier then it checks if it is an assignment operator "=" or not and if it returns true then it sets the symbol_table[r][c] to "var"

    if the matched string is ")" then it sets the symbol_table[r][c] to "var" and increments the row counter (r).

    if the matched string is "(" then it sets the symbol_table[r][c] to "func" and increments the row counter (r), it also adds the matched string to the function_list and increments the function_list counter (fl).

    if the matched string is a number then it checks if it is a number by calling the function isNum(temp) and if it returns true then it sets the symbol_table[r][c] to the matched string.

    if the matched string is ";" then it increments the row counter (r)
    */
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
    /*
    It starts by initializing two nested for loops, one iterating through the rows of the symbol_table (i) and the other iterating through the rows of the symbol_table starting from the next row of the outer loop (j).
    For each pair of rows, it compares the values of symbol_table[i][1] and symbol_table[j][1], and symbol_table[i][4] and symbol_table[j][4]. If they are equal, it means that the rows have the same name and scope.
    In this case, the innermost for loop iterates through all the columns of the current row (kl) and checks if symbol_table[i][kl] is equal to "-404" using the compare method.
    If symbol_table[i][kl] is equal to "-404", it means that the current entry in row i is empty, and it sets the value of symbol_table[i][kl] to the value of symbol_table[j][kl].
    */

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
                        //cout<<temp<<" "<<sy_table[utl][0]<<endl;

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
    /*
    It starts by initializing several variables such as last_kwd, scope_, unique_idlist, ul_size, uq_idIndex, final_text, prev_id, index_of_searching, isBalanaced, last_word, flag and flag2.
    It then creates a sregex_iterator "it" that iterates through all the matches of the regular expression "rgx" in the input text.
    for each match, it assigns the match to the variable temp.
    It then checks if the temp is keyword, operand, separator, pair and identifier using the functions isKeyword(), isNum(), isOperand(), isSeparator(), isPair() and isIdentifier() respectively.
    If it is a keyword, operand, separator, or pair, it adds the temp to the final_text variable.
    If it is an identifier, it checks whether the identifier is "Id" or not, if it is "Id" it adds "Id" to the final_text variable. If it is not "Id" it performs several checks such as checking whether the identifier is a function or not, and whether the identifier has been encountered previously or not.
    If the identifier is a function, it adds the function name to the final_text variable. If the identifier has been encountered previously, it adds the index of the identifier in the unique_idlist array to the final_text variable. If it is a new identifier, it adds the identifier to the unique_idlist array and adds the index of the identifier to the final_text variable.
    It also keeps track of last_kwd, last_word, scope_, and isBalanaced.
    The final_text variable holds the final text in the new format.
    */
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
        cout<<text<<endl;

        regex r2("(\\S+)");
        text=filemaker_2(r2,text);
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
