#include "template.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

morseChar::morseChar(std::string newChar, char latin){
    mChar = newChar;
    lChar = latin;
}

//TODO: brailleChar constructor

bool checkLatin(char& newChar)
{
    char validLatin[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','_'};
    //NOTE: when reading latin convert whitespace to '_' and skip doing checkLatin and send it to the inMsg txtfile 
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
    } else if (newChar.empty()){
        std::cerr << "ERROR: the new morseChar cannot be an empty string.\n";
        return false;
    }
    for (int i = 0; i < newChar.size(); i++ ){
        if (newChar[i] == '-' || newChar[i] == '.'){
        } else {
            std::cerr << "ERROR: the string \"" << newChar << "\" passed to checkMorse contained the invalid character: \"" << newChar[i] << "\" aborting program.\n";
            return false;
        }
        //NOTE: a morseChar can be any length
    }
    return true;
}

//TODO: double check its all good
bool checkBraille(std::string& newChar, char& latinChar){ 
    if(!checkLatin(latinChar)){
        return false;
    } else if (newChar.empty()){
        std::cerr << "ERROR: the new brailleChar cannot be an empty string.\n";
        return false;
    } else if (newChar.size() != 6){
        std::cerr << "ERROR: the new brailleChar is not 6 digits long.\n";
        return false;
    }
    for (int i = 0; i < newChar.size(); i++){
        if (newChar[i] == '0' || newChar[i] == '1'){
        } else {
            std::cerr << "ERROR: the string \"" << newChar << "\" passed to checkBraille contained the invalid character: \"" << newChar[i] << "\" aborting program.\n";
            return false;
        }
    }
    return true;
}

bool loadAlphabet(Alphabet<morseChar> &mDict){

    std::ifstream inFile;
    inFile.open("Morse.txt");
    std::string line;
    bool error = false;

    if (inFile){
        while (getline(inFile, line)){
            char latinChar = line [0];
            std::string newMChar = "";
            if (line[1] != ' '){
                error = true;
                std::cerr << "ERROR: poorly formed line in Morse.txt, expected a space between morse character and latin correspondent.\n";
                std::cerr << "LINE: " << line << '\n';
                break;
            }
            for (int i = 2; i < line.size(); i++){
                newMChar += line[i];
            }
            if(!checkMorse(newMChar, latinChar)){
                error = true;
                break;
            }
            morseChar newMorseChar(newMChar, latinChar);
            if(mDict.doesExist(newMorseChar)){
                error = true;
                std::cerr << "ERROR: attempting to add a new morse character that is not unique.\n";
            } else {
                mDict.addNewChar(newMorseChar);
            }
        }
    } else {
        std::cerr << "ERROR: Could not open the Morse.txt file.\n";
        return false;
    }

    if (error){
        std::cerr << "ERROR: loadAlphabet failed.\n";
        return false;
    }

    std::cout << "Morse alphabet loading SUCCESS.\n";
    return true;
}

//TODO
bool loadAlphabet(Alphabet<brailleChar> &bDict){
    std::ifstream inFile;
    inFile.open("Braille.txt");
    std::string line;
    bool error = false;

    if (inFile)
    {
        while (getline(inFile, line))
        {
            char latinChar = line[0];
            std::string newBChar = "";
            if (line[1] != ' ')
            {
                error = true;
                std::cerr << "ERROR: poorly formed line in Braille.txt, expected a space between braille binary and latin correspondent.\n";
                std::cerr << "LINE: " << line << '\n';
                break;
            }
            for (int i = 2; i < line.size(); i++)
            {
                newBChar += line[i];
            }
            if (!checkBraille(newBChar, latinChar))
            {
                error = true;
                break;
            }
            brailleChar newBrailleChar(newBChar, latinChar);
            if (bDict.doesExist(newBrailleChar))
            {
                error = true;
                std::cerr << "ERROR: attempting to add a new braille binary that is not unique.\n";
            }
            else
            {
                bDict.addNewChar(newBrailleChar);
            }
        }
    }
    else
    {
        std::cerr << "ERROR: Could not open the Braille.txt file.\n";
        return false;
    }

    if (error)
    {
        std::cerr << "ERROR: loadAlphabet failed.\n";
        return false;
    }
    std::cout << "Braille alphabet loading SUCCESS.\n";
    return true;
}