#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
#include <string>
#include <vector>

class morseChar {
    private:
        std::string type;
        std::string custChar;
        char lChar;                             //latin character
        bool validateChracter(std::string newChar);                //uses the customeChar type and checks if the string passed to the constructor is made up of the correct symbols
    public:
        morseChar(char charType, std::string newChar, char latin);
        std::string getCustChar();
        char getLatChar();
};

template <class T>
class Alphabet {
    private:
        bool noErrors = true;
        std::vector<T> fromAlphabet;
        std::vector<T> toAlphabet;
    public:
        bool loadAlphabet(char type){
            
        }
        Alphabet(){
            /*
            //load fromAlphabet
            if (fromType == 'M'|| fromType == 'B'){
                loadAlphabet(fromType, fromAlphabet);
            } else if (fromType == 'L'){
                //link to toAlphabet
                fromAlphabet = &toAlphabet;
            } else {
                std::cerr << "ERROR: the language type was not found. fromAlphabet failed to construct.\n";
            }

            //load toAlphabet
            if(toType == 'M'|| toType == 'B'){
                loadAlphabet(toType, toAlphabet);
            } else if (toType == 'L'){
                //link to fromAlphabet
                toAlphabet = &fromAlphabet;
            } else {
                std::cerr << "ERROR: the language type was not found. toAlphabet failed to construct.\n";
            }*/
        }
        bool isFromEmpty() {
            return fromAlphabet.empty();
        }
        bool isToEmpty(){
            return toDictionary.empty();
        }
        bool successfulLoad(){
            return noErrors;
        }
};


#endif
//NOTES: overloading will be for types of customChar and normal char
//morse characters are sperated by spaces, but the whitespace character is represented by an underscore
//in morse space is not underscore anymore but just the whitespace character
//newlines and eof will be tricky to implement
