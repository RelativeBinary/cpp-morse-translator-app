#include "template.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

bool checkLatin(char &newChar) {
    char validLatin[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
    //NOTE: when reading latin convert whitespace to '_' and skip doing checkLatin and send it to the inMsg txtfile
    for (int i = 0; i < 27; i++)
    {
        if (newChar == validLatin[i])
        {
            return true;
        }
    }
    std::cerr << "ERROR: the char passed to checkLatin '" << newChar << "' is not valid. aborting program.\n";
    return false;
}

morseChar::morseChar(std::string newChar, char latin) {
    mChar = newChar;
    lChar = latin;
}

brailleChar::brailleChar(std::string newChar, char latin) {
    bChar = newChar;
    lChar = latin;
}

//LATIN USE ONLY
bool readLatFile(std::vector<char> &latinMsg, std::string &inFile) {
    //load file
    std::ifstream in;
    in.open(inFile);
    std::string line;
    bool error = false;
    //split file into chars as you put them into vector
    if (in) {
        while(getline(in, line)) {
            for (int i = 0; i < line.size(); i++){
                char newLat = line[i]; 
                if (newLat == ' '){
                    newLat = '_';
                }
                if (checkLatin(newLat)){
                    latinMsg.push_back(newLat);
                } else {
                    std::cerr << "ERROR: readLatFile failed.\n";
                    error = true;
                    break;
                }
            }
        }
    } else {
        std::cerr << "ERROR: was not able to open '" << inFile << '\n';
        return false;
    }
    if (error) {
        std::cerr << "ERROR: readFile failed to read the latin text.\n";
        return false;
    }

    return true;
}