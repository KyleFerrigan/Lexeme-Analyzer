//
//  main.cpp
//  CSCE306HW2
//
//  Created by Kyle Ferrigan on 9/21/20.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <typeinfo>
using namespace std;


class LexAnalyzer{
private:
    vector<string> lexemes;  // source code file lexemes
    vector<string> tokens;   // source code file tokens
    map<string, string> tokenmap;  // valid lexeme/token pairs
    // other private methods
    
    int curPos; //Current position within the line
    
    //pre:
    //post:
    string phraseFind(string lineIn){ //finds a phrase based off within lineIn starting at curPos.
        string curPhrase = ""; //reset curPhrase
        if (curPos < lineIn.size()){ //checking to make sure its not end of line
            //INTEGERS
            if(lineIn.at(curPos) >= 48 && lineIn.at(curPos) <= 57){ //first thing a int delcare it as an int: 48-57
                while ((lineIn.at(curPos) >= 48 && lineIn.at(curPos) <= 57) && (curPos < lineIn.size())){ //Keep going until not an int or end of line
                    curPhrase += lineIn.at(curPos);
                    curPos++;
                }
            }
            //STRINGS
            else if(lineIn.at(curPos) == 34){ //" means start of string: 34
                cout << "in strings within phraseFind" << endl; //TODO REMOVE
                while ((lineIn.at(curPos) != 34) && (curPos < lineIn.size())){ //Keep going until the next " or end of line
                    curPhrase += lineIn.at(curPos);
                    curPos++;
                }
                if (curPos >= lineIn.size()){ //Error occured, no data output as phrase isnt valid
                    curPhrase = "";
                }
                else{
                    curPhrase += '"';
                }
            }
            //SYMBOLS
            else if((lineIn.at(curPos) >= 33 && lineIn.at(curPos) <= 47 ) || (lineIn.at(curPos) >= 58 && lineIn.at(curPos) <= 64) || (lineIn.at(curPos) >= 91 && lineIn.at(curPos) <= 96) || (lineIn.at(curPos) >= 123 && lineIn.at(curPos) <= 126)){ //symbols: 33-47 58-64 91-96 123-126
                cout << "in symbols within phraseFind" << endl; //TODO REMOVE
                while(((lineIn.at(curPos) >= 33 && lineIn.at(curPos) <= 47 ) || (lineIn.at(curPos) >= 58 && lineIn.at(curPos) <= 64) || (lineIn.at(curPos) >= 91 && lineIn.at(curPos) <= 96) || (lineIn.at(curPos) >= 123 && lineIn.at(curPos) <= 126)) && ((curPos < lineIn.size()))){ //Keep going until you reach anything other than another symbol or end of line
                        curPhrase += lineIn.at(curPos);
                        curPos++;
                    }
            }
            //LETTERS
            else if(lineIn.at(curPos) == ' '){//letters : 65-90, 97-122
                cout << "in letter within phraseFind" << endl; //TODO REMOVE
                //Keep going until a symbol or space is reached or end of line
                while(((((lineIn.at(curPos) >= 33 && lineIn.at(curPos) <= 47 ) || (lineIn.at(curPos) >= 58 && lineIn.at(curPos) <= 64) || (lineIn.at(curPos) >= 91 && lineIn.at(curPos) <= 96) || (lineIn.at(curPos) >= 123 && lineIn.at(curPos) <= 126)) || lineIn.at(curPos) == 32) == false) && (curPos < lineIn.size())){
                    curPhrase = lineIn.at(curPos);
                    curPos++;
                }
            }
        }
        return curPhrase;
    }
    
    //pre: must be given only a single statement, not a line
    //post:
    string compareToKnownPairs(string strIn){
        //TODO compare to tokenmap then send back string that holds the token if no tokens found return NULL;
        //getline(tokenmap)
        return NULL;
    }
public:
    // pre: parameter refers to open data file consisting of token and lexeme pairs i.e.  s_and and t_begin begin t_int 27.  Each pair appears on its own input line.
    // post: tokenmap has been populated
    LexAnalyzer(istream& infile){//TODO finish this
        cout << "In LexAnalyzer" << endl; //TODO Debug Remove this
        //creates object and fills a tokenmap with the lexeme pairs
        //move infile to tokenmap thats all
        //for (int i = 0; !infile.eof(); i= i+2){
            //tokenmap.insert();
        //}
    }

    // pre: 1st parameter refers to an open text file that contains source code in the language, 2nd parameter refers to an open empty output file.
    // post: If no error, the token and lexeme pairs for the given input file have been written to the output file.  If there is an error, the incomplete token/lexeme pairs, as well as an error message have written to the output file.  A success or fail message has printed to the console.
    void scanFile(istream& infile, ostream& outfile){
        //Identifies the words from the course code and outputs it to file as the lexeme pair
        cout << "In scanFile" << endl;//TODO Debug Remove this
    
        //TODO while file still has data iterate to next line
            //comparing line by line
            string curLine;
            getline(infile, curLine);//put current line into string buffer, iterate this to next line
            //TODO while line still has data
                compareToKnownPairs(phraseFind(curLine)); //TODO Append current line ends when a phrase is found
    }
};

int main() {
    string buffer;
    ifstream lexemeData("tokenlexemedata.txt");//open lemexe data file
    LexAnalyzer lex(lexemeData);//Create LexAnalyzer with lexeme data
    cout << "Input filename of Source Code: " << endl;
    cin >> buffer;
    ifstream sourceCode(buffer);
    buffer = "";
    cout << "Input filename of Output File: " << endl;
    cin >> buffer;
    ofstream lexOut(buffer);
    lex.scanFile(sourceCode, lexOut);//Pass source code to lexanalyzer function
    lexOut.close();//close data file
    return 0;
}
