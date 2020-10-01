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
#include <string>
using namespace std;


class LexAnalyzer{
private:
    vector<string> lexemes;  // source code file lexemes
    vector<string> tokens;   // source code file tokens
    map<string, string> tokenmap;  // valid lexeme/token pairs
    // other private methods
    int curPos = 0; //Current position within on the current line
    
    //pre: needs a line of source code, uses curPos to keep track of where it is on that line
    //post: returns single "word"
    string phraseFind(string lineIn){ //finds a phrase based off within lineIn starting at curPos.
        string curPhrase = ""; //reset curPhrase
        if (curPos < lineIn.length()-1){ //checking to make sure its not end of line
            //INTEGERS
            if(lineIn.at(curPos) >= 48 && lineIn.at(curPos) <= 57){ //first thing a int delcare it as an int: ASCII 48-57
                while ((lineIn.at(curPos) >= 48 && lineIn.at(curPos) <= 57) && (curPos < lineIn.length())){ //Keep going until not an int or end of line
                    curPhrase.push_back(lineIn.at(curPos));
                    curPos++;
                }
            }
            //STRINGS
            else if(lineIn.at(curPos) == 34){ //" means start of string: ASCII 34
                while ((lineIn.at(curPos) != 34) && (curPos < lineIn.length())){ //Keep going until the next " or end of line
                    curPhrase.push_back(lineIn.at(curPos));
                    curPos++;
                }
                if (curPos == lineIn.size()){ //Error occured, no data output as phrase isnt valid
                    cout << "String error";
                    curPhrase = "";//clear output as its garbage data
                }
                else{
                    curPhrase.push_back('"');
                    curPos++;
                }
            }
            //SYMBOLS
            else if((lineIn.at(curPos) >= 33 && lineIn.at(curPos) <= 47 ) || (lineIn.at(curPos) >= 58 && lineIn.at(curPos) <= 64) || (lineIn.at(curPos) >= 91 && lineIn.at(curPos) <= 96) || (lineIn.at(curPos) >= 123 && lineIn.at(curPos) <= 126)){ //symbols:  ASCII 33-47 58-64 91-96 123-126
                while(((curPos < lineIn.length())) && ((lineIn.at(curPos) >= 33 && lineIn.at(curPos) <= 47 ) || (lineIn.at(curPos) >= 58 && lineIn.at(curPos) <= 64) || (lineIn.at(curPos) >= 91 && lineIn.at(curPos) <= 96) || (lineIn.at(curPos) >= 123 && lineIn.at(curPos) <= 126))){ //Keep going until you reach anything other than another symbol or end of line
                        curPhrase.push_back(lineIn.at(curPos));
                        curPos++;

                }
            }
            //LETTERS
            else if((lineIn.at(curPos) >= 65 && lineIn.at(curPos) <= 90) || (lineIn.at(curPos) >= 97 && lineIn.at(curPos) <= 122)){//letters : ASCII 65-90, 97-122
                //Keep going until a symbol or space is reached or end of line
                while((curPos < lineIn.length())&&((((lineIn.at(curPos) >= 33 && lineIn.at(curPos) <= 47 ) || (lineIn.at(curPos) >= 58 && lineIn.at(curPos) <= 64) || (lineIn.at(curPos) >= 91 && lineIn.at(curPos) <= 96) || (lineIn.at(curPos) >= 123 && lineIn.at(curPos) <= 126)) || (lineIn.at(curPos) == 32)) == false)){
                    curPhrase.push_back(lineIn.at(curPos));
                    curPos++;

                }
            }
            else if (lineIn.at(curPos) == 32){
                curPos++;
            }
            else{
                cout << "Character Not Recognized" << endl;
                curPos++;
            }
        }
        return curPhrase;
    }

public:
    // pre: parameter refers to open data file consisting of token and lexeme pairs i.e.  s_and and t_begin begin t_int 27.  Each pair appears on its own input line.
    // post: tokenmap has been populated
    LexAnalyzer(istream& infile){
        //creates object and fills a tokenmap with the lexeme pairs
        //move infile to tokenmap thats all
        string word;
        string word2;
        while (infile >> word) {
            infile >> word2;
            tokenmap.insert(pair<string, string>(word2, word));
        }
    }

    // pre: 1st parameter refers to an open text file that contains source code in the language, 2nd parameter refers to an open empty output file.
    // post: If no error, the token and lexeme pairs for the given input file have been written to the output file.  If there is an error, the incomplete token/lexeme pairs, as well as an error message have written to the output file.  A success or fail message has printed to the console.
    void scanFile(istream& infile, ostream& outfile){
        //Identifies the words from the course code and outputs it to file as the lexeme pair
        string curLine;

        while (getline(infile, curLine)){//While file still has data iterate to next line
            curPos = 0;
            while (curPos < curLine.length()-1){//while line still has data
                string phrase = "";
                phrase = phraseFind(curLine);
                try{outfile << tokenmap.at(phrase) << " : " << phrase << '\n';} //Compare to tokenmap then send back string that holds the token working?
                catch (const std::out_of_range&){
                    if (phrase == ""){

                    }
                    else if (phrase.at(0) >= 48 && phrase.at(0) <= 57){ //integer
                        outfile << "t_int" << " : " << phrase << '\n';
                    }
                    else if (phrase.at(0) == '"'){ //String
                         outfile << "t_str" << " : " << phrase << '\n';
                    }
                    else{ //Identifier
                        outfile << "t_id" << " : " << phrase << '\n';
                    }
                }
            }
        }
    }
};

int main() {
    string buffer = "";
    ifstream lexemeData("C:\\Users\\KyleF\\iCloudDrive\\Documents\\Code\\Xcode\\SoftwareDevHW\\Homework2\\CSCE306HW2\\CSCE306HW2\\tokenlexemedata.txt");//open lemexe data file
    LexAnalyzer lex(lexemeData);//Create LexAnalyzer with lexeme data
    cout << "Input filename of Source Code: " << endl;
    //cin >> buffer;
    buffer = "C:\\Users\\KyleF\\iCloudDrive\\Documents\\Code\\Xcode\\SoftwareDevHW\\Homework2\\CSCE306HW2\\CSCE306HW2\\sourceCode.txt";
    //todo uncomment delete placeholder below
    ifstream sourceCode(buffer);
    cout << "Input filename of Output File: " << endl;
    //cin >> buffer;
    //todo uncomment and delete placeholder below
    buffer = "C:\\Users\\KyleF\\iCloudDrive\\Documents\\Code\\Xcode\\SoftwareDevHW\\Homework2\\CSCE306HW2\\CSCE306HW2\\output.txt";
    ofstream lexOut(buffer);
    lex.scanFile(sourceCode, lexOut);//Pass source code to lexanalyzer function
    lexOut.close();//close data file
    return 0;
}
