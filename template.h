#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
#include <string>
#include <vector>

class morseChar {
    private:
        std::string mChar;
        char lChar;                                                 //latin character
    public:
        morseChar(std::string newChar, char latin);
        std::string getMorChar() {
            return mChar;
        }
        char getLatChar() {
            return lChar;
        }
};

class brailleChar {
    private: 
        std::string bChar; 
        char lChar;
    public: 
        brailleChar(std::string newChar, char latin);
        std::string getBraChar(){
            return bChar;
        }
        char getLatChar(){
            return lChar;
        }
};

template <class T>
class Alphabet {
    private:
        std::vector<T> characters;
    public:
        Alphabet(){
        }
        void displayAlphabet();
        bool isEmpty() {
            return characters.empty();
        }
        bool doesExist(morseChar& newChar){
            if (isEmpty()){
                return false;                                           //newChar doesnt exist as the characters vector is empty
            }
            for (int i = 0; i < characters.size(); i++){
                if (newChar.getLatChar() == characters[i].getLatChar() && newChar.getMorChar() == characters[i].getMorChar() ){
                    std::cout << "MorseChar: '" << newChar.getMorChar() << "' already exists.\n";
                    return true;
                }
            }
            return false;
        }
        bool doesExist(brailleChar &newChar)
        {
            if (isEmpty())
            {
                return false; //newChar doesnt exist as the characters vector is empty
            }
            for (int i = 0; i < characters.size(); i++)
            {
                if (newChar.getLatChar() == characters[i].getLatChar() && newChar.getBraChar() == characters[i].getBraChar())
                {
                    std::cout << "MorseChar: '" << newChar.getBraChar() << "' already exists.\n";
                    return true;
                }
            }
            return false;
        }
        bool addNewChar(T& newChar){
            characters.push_back(newChar);
        }

};

//check as much intermediate data before even making the char objs
bool checkMorse(std::string newChar);                                   //uses the morseChar type and checks if the string passed is made up of the correct symbols
bool checkBraille(std::string newChar);                                 //uses the brailleChar type and checks if the string passed is made up of the correct symbols
bool loadAlphabet(Alphabet<morseChar> &);                               //opens file for morse, loads/checks new morse chars into the alphabet's character vector given
bool loadAlphabet(Alphabet<brailleChar> &);                             //opens file for braille, loads/checks new braille chars into alphabet's character vector given

#endif
//NOTES: overloading will be for types of customChar and normal char
//morse characters are sperated by spaces, but the whitespace character is represented by an underscore
//in morse space is not underscore anymore but just the whitespace character
//newlines and eof 
//newlines: when reading a file ur generally using a getline while loop, so at the end of the while loop you can add a newline character IF were not at last line of the file