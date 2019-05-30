#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

bool checkLatin(char &newChar);
bool readLatFile(std::vector<char> &latinMsg, std::string &inFile);

template <class T>
class Alphabet {
    private:
        std::vector<T> characters;
    public:
        Alphabet(){
        }
        void displayAlphabet(){
            for (int i = 0; i < characters.size(); i++){
                std::cout << characters[i].getLatChar() << " : " << characters[i].getChar() << '\n';
            }
        }
        bool isEmpty() {
            return characters.empty();
        }
        bool doesExist(T &newChar){
            if (isEmpty()){
                std::cerr << "ERROR: attempting to use an empty alphabet.\n";
                return false;                                           //newChar doesnt exist as the characters vector is empty
            }
            for (int i = 0; i < characters.size(); i++){
                if (newChar.getLatChar() == characters[i].getLatChar() && newChar.getChar() == characters[i].getChar() ){
                    std::cout << "Char: '" << newChar.getChar() << "' already exists.\n";
                    return true;
                }
            }
            return false;
        }
        bool doesStrExist(std::string &target){
            if(isEmpty()){
                std::cerr << "ERROR: attempting to use an empty alphabet.\n";
                return false;
            }
            for (int i = 0; i < characters.size(); i++){
                if(target == characters[i].getChar()){
                    return true;
                }
            }
            std::cerr << "ERROR: was not able to locate '" << target << "' in alphabet.\n";
        }
        bool doesLatExist(char &target){

        }
        T getByTypeStr(std::string &target){
            for (int i = 0; i < characters.size(); i++){
                if (target == characters[i].getChar()){
                    return characters[i];
                }
            }
        }
        bool addNewChar(T& newChar){
            characters.push_back(newChar);
        }
};

class morseChar {
    private:
        std::string mChar;
        char lChar;                                                 
    public:
        morseChar(std::string newChar, char latin);
        std::string getChar() {
            return mChar;
        }
        char getLatChar() {
            return lChar;
        }
        static bool check(std::string &newChar, char &latinChar){
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
            }
            return true;
        }
        static bool readLine(Alphabet<morseChar> &dict, std::vector<morseChar> &typeMsg, std::string &line) {
            std::string newCharStr = "";
            for (int i = 0; i < line.size(); i++){
                if (line[i] != ' '){//add to newChar if not a delimiter
                    newCharStr += line[i];
                }
                if (line[i] == ' ' && !newCharStr.empty()){
                    //check the newChar is in dict and if valid push to typeMsg
                    if (dict.doesStrExist(newCharStr)){
                        //push the matching char to the msg vector
                        typeMsg.push_back(dict.getByTypeStr(newCharStr));
                    } else {
                        std::cerr << "ERROR: readLine was not able to match the character '" << newCharStr << "' with any definitions in the alphabet given.\n";
                        return false;
                    }
                    newCharStr = "";
                } else {
                    //consecutive spaces in the file
                }
            }
            return true;
        }
};

class brailleChar {
    private: 
        std::string bChar; 
        char lChar;
    public: 
        brailleChar(std::string newChar, char latin);
        std::string getChar(){
            return bChar;
        }
        char getLatChar(){
            return lChar;
        }
        static bool check(std::string &newChar, char &latinChar){ 
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
        static bool readLine(Alphabet<brailleChar> &dict, std::vector<brailleChar> &typeMsg, std::string &line) {
            std::string newCharStr = "";
            //check if line is of valid size to fit valid characters.
            if (line.size() % 6 != 0){
                std::cerr << "ERROR: the line passed to readLine contains an invalid character.\n";
                return false;
            }

            for (int i = 0; i < line.size(); i++){
                if (i % 6 != 0){
                    //add to newChar if not a delimiter
                    newCharStr += line[i];
                } 
                
                if (i % 6 == 0 && !newCharStr.empty()) {//
                    //check the newChar is in dict and if valid push to typeMsg
                    if (dict.doesStrExist(newCharStr)){
                        //push the matching char to the msg vector
                        typeMsg.push_back(dict.getByTypeStr(newCharStr));
                    } else {
                        std::cerr << "ERROR: readLine was not able to match the character '" << newCharStr << "' with any definitions in the alphabet given.\n";
                        return false;
                    }
                    newCharStr = "";
                }

            }
            return true;
        }
};

template <class T>
bool loadAlphabet(Alphabet<T> &dict, std::string fileName) {
    std::ifstream inFile;
    inFile.open(fileName + ".txt");
    std::string line;
    bool error = false;

    if (inFile) {
        while (getline(inFile, line)) {
            char latinChar = line[0];
            std::string newChar = "";
            if (line[1] != ' ') {
                error = true;
                std::cerr << "ERROR: poorly formed line in " << fileName << ".txt, expected a space between " << fileName << " character and latin correspondent.\n";
                std::cerr << "LINE: " << line << '\n';
                break;
            }
            for (int i = 2; i < line.size(); i++) {
                newChar += line[i];
            }
            if (!T::check(newChar, latinChar)) {
                error = true;
                break;
            }
            T newTChar(newChar, latinChar);
            if (dict.doesExist(newTChar)) {
                error = true;
                std::cerr << "ERROR: attempting to add a new " << fileName << " character that is not unique.\n";
            } else {
                dict.addNewChar(newTChar);
            }
        }
    }
    else{
        std::cerr << "ERROR: Could not open the "<< fileName <<".txt file.\n";
        return false;
    }

    if (error){
        std::cerr << "ERROR: loadAlphabet failed.\n";
        return false;
    }

    std::cout << fileName <<" alphabet loading SUCCESS.\n";
    return true;
}

template <class T>
bool readFile(Alphabet<T> &dict, std::vector<T> &typeMsg, std::string &inFile) {
    //load file
    std::ifstream in;
    in.open(inFile);
    std::string line;
    bool error = false;

    //get string/line
    if (in) {
        while(getline(in, line)){
            if(T::readLine(dict, typeMsg, line)){
                //successfull read
            } else {
                std::cerr << "ERROR: an error occured when trying to read input message.\n";
            }
        }
    } else {
        std::cerr << "ERROR: was not able to open file '" << inFile << '\n';
    }
    if (error) {
        std::cerr << "ERROR: readFile failed to read the coded text.\n";
        return false;
    }
    //the whole input file has been broken down into single characters which have been checked for validity and then added to the typeMsgVector
    return true;
}

#endif
//NOTES: overloading will be for types of customChar and normal char
//morse characters are sperated by spaces, but the whitespace character is represented by an underscore
//in morse space is not underscore anymore but just the whitespace character
//newlines and eof
//newlines: when reading a file ur generally using a getline while loop, so at the end of the while loop you can add a newline character IF were not at last line of the file