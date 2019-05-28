#include "template.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/*morseChar::morseChar(char charType, std::string newChar, char latin){
    type = charType;
    newChar = custChar;
    lChar = latin;
}*/

bool checkLatin(char& newChar)
{
    char validLatin[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','_'};
    //NOTE: when reading latin text - before passing to checkLatin if (char[i] == ' ') then convert to '_'  
    for (int i = 0; i < 27; i++){
        if (newChar == validLatin[i]){
            return true;
        }
    }
    std::cerr << "ERROR: the char passed to checkLatin '" << newChar << "' is not valid. aborting program.\n";
    return false;
}

bool checkMorse(std::string& newChar, char& latinChar){
    if (!checkLatin(latinChar)){
        return false;
    } 
    for (int i = 0; i < newChar.size(); i++ ){
        if (newChar[i] != '-' || newChar[i] != '.'){
            std::cerr << "ERROR: the string passed to checkMorse contained the invalid character: \"" << newChar[i] << "\" aborting program.\n";
            return false;
        }
        //NOTE: a morseChar can be any length, 
    }
    return true;
}

bool checkBraille(std::string& newChar){ 
    return true;
}

bool loadAlphabet(Alphabet<morseChar> &){
    //initialize file
    std::ifstream inFile("Morse.txt");

    //get first line 

    //check first line data for correctness (split the first line into latinType, morseType based on spaces)

    //check if first line data if it already exists

    //create new morseChar

    //add new morseChar

    //repeat
}

bool loadAlphabet(Alphabet<brailleChar> &){
}