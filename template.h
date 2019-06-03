#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

bool checkLatin(char &newChar);
bool readLatFile(std::vector<char> &latinMsg, std::string &inFile);
bool reportLatMsg(std::vector<char> &latinMsg);
bool writeLatFile(std::vector<char> &latinMsg, std::string &outFile);

template <class T>
class Alphabet {
    private:
        std::vector<T> characters;
    public:
        Alphabet(){
        }
        void displayAlphabet(){//for testing purposes
            for (int i = 0; i < characters.size(); i++){
                std::cout << characters[i].getLatChar() << " : " << characters[i].getChar() << '\n';
            }
        }
        bool isEmpty() {//checks if there characters vector has any characters in it
            return characters.empty();
        }
        bool doesExist(T &target){//checks if a new characters latin or typeChar already exists in the alphabet 
            if (isEmpty()){
                return false;//newChar doesnt exist as the characters vector is empty
            }
            for (int i = 0; i < characters.size(); i++){
                if (target.getLatChar() == characters[i].getLatChar() || target.getChar() == characters[i].getChar() ){
                    return true;
                }
            }
            return false;
        }
        bool doesStrExist(std::string &target){//checks if a character exists by checking the typeStrings
            if(isEmpty()){
                return false;
            }
            for (int i = 0; i < characters.size(); i++){
                if(target == characters[i].getChar()){
                    return true;
                }
            }
            return false;
        }
        bool doesLatExist(char &target){//checks if a latin characters exists by checking the lati characters
            if(isEmpty()){
                return false;
            }
            for (int i = 0; i < characters.size(); i++){
                if(target == characters[i].getLatChar()){
                    return true;
                }
            }
            return false;

        }
        T getByTypeStr(std::string &target){//returns a character based on a typeString
            for (int i = 0; i < characters.size(); i++){
                if (target == characters[i].getChar()){
                    return characters[i];
                }
            }
            throw "ERROR : getByTypeStr attempted get a character that does not exist.\n";
        }
        T getByLatin(char &target){
            for (int i = 0; i < characters.size(); i++){//returns a character based on a latin character
                if (target == characters[i].getLatChar()){
                    return characters[i];
                }
            }
            throw "ERROR : getByLatin attemped to get a character that does not exist.\n";
        }
        bool addNewChar(T& newChar){//add new character to characters
            characters.push_back(newChar);
        }
        bool translateFromLatin(std::vector<char> &inMsg, std::vector<T> &outMsg){//matching latin characters to their typeString to be added to outmsg vector
            //loop through inMsg
            for(int i = 0; i < inMsg.size(); i++){
                //NOTE: all spaces are currently in _ format when read from latin file into inMsg
                //check if inMsg latin is in alphabet
                if (doesLatExist(inMsg[i])){
                    outMsg.push_back(getByLatin(inMsg[i]));
                } else {
                    throw "ERROR: translateToLatin encountered an unknown character\n";
                }
            }
            return true;
        }
        bool translateToLatin(std::vector<T> &inMsg, std::vector<char> &outMsg){//matching typeString characters to their latin to be added to outsg vector
            //loop through inMsg
            for (int i = 0; i < inMsg.size(); i++){
                //NOTE: all _ need to be converted to ' ' before being pushed to outMsg
                //check if inMsg char is in alphabet
                if (doesExist(inMsg[i])){//makesure the character exists in the characters vector
                    if (inMsg[i].getLatChar() == '_'){//if valid send the inMsg character to the outMsg vector
                        outMsg.push_back('_');
                    } else {
                        outMsg.push_back(inMsg[i].getLatChar());
                    }

                } else {
                    throw "ERROR: translateToLatin encountered an unknown character '" + inMsg[i].getChar() + "'\n";
                    return false;
                }
            }
            return true;
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
        static bool check(std::string &newChar, char &latinChar){//check if a new morseChar is valid
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
            //used in template function readFile to check a morse specific text
            std::string newCharStr = "";
            for (int i = 0; i < line.size(); i++){
                if (line[i] != ' '){//add to newChar if not a delimiter
                    newCharStr += line[i];
                }
                //check if delimeter was reached or if this is the last character
                if ((line[i] == ' ' || i+1 >= line.size()) && !newCharStr.empty()){
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
                    //ignor consecutive spaces in the file
                }
            }
            return true;
        }
        std::string outputChar() {//adds spaces to the end
            return getChar() + " ";
        }
        static bool getSymbolCount(std::vector<morseChar> &typeMsg){//gets dot and dash count for reporting on morse messages
            int dashes=0;
            int dots=0;
            for (int i = 0; i < typeMsg.size(); i++ ){
                std::string tempStr = typeMsg[i].getChar();
                for (int j = 0; j < tempStr.size(); j++){
                    if (tempStr[j] == '-'){
                        dashes++;
                    } else if (tempStr[j] == '.'){
                        dots++;
                    } else {
                        std::cerr << "ERROR: getSymbolCount encountered an unknown character: " << tempStr[j] << '\n';
                    }
                }
            }
            std::cout << "Dashes: " << dashes << '\n';
            std::cout << "Dots: " << dots << '\n';
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
        static bool check(std::string &newChar, char &latinChar){ //used to make sure that the new brailleCharacter is valid
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
            //used in readFile template functions to read braille specific file
            std::string newCharStr = "";
            //check if line is of valid size to fit valid characters.
            if (line.size() % 6 != 0){
                std::cerr << "ERROR: the line passed to readLine contains an invalid character.\n";
                return false;
            }

            for (int i = 0; i < line.size(); i++){
                newCharStr += line[i];
                if (newCharStr.size() >= 6){
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
        std::string outputChar() {//exists because the writeFile template function uses outputChar for morse so braille needs to do the same 
            return getChar();
        }
        static bool getSymbolCount(std::vector<brailleChar> &typeMsg){
            //used to display symbol counts when reporting on braille messages
            int zeros=0;
            int ones=0;
            for (int i = 0; i < typeMsg.size(); i++ ){
                std::string tempStr = typeMsg[i].getChar();
                for (int j = 0; j < tempStr.size(); j++){
                    if (tempStr[j] == '0'){
                        zeros++;
                    } else if (tempStr[j] == '1'){
                        ones++;
                    } else {
                        std::cerr << "ERROR: getSymbolCount encountered an unknown character: " << tempStr[j] << '\n';
                    }
                }
            }
            std::cout << "Dashes: " << zeros << '\n';
            std::cout << "Dots: " << ones << '\n';
            return true;
        }
};

template <class T>
bool loadAlphabet(Alphabet<T> &dict, std::string fileName) {//used to load the alphabets with their appropriate characters and latin correspondends
    std::ifstream inFile;
    inFile.open(fileName + ".txt");
    std::string line;
    bool error = false;

    if (inFile) {//check for file access
        while (getline(inFile, line)) {
            char latinChar = line[0];
            std::string newChar = "";
            if (line[1] != ' ') {//check for space between latin and typeString
                error = true;
                std::cerr << "ERROR: poorly formed line in " << fileName << ".txt, expected a space between " << fileName << " character and latin correspondent.\n";
                std::cerr << "LINE: " << line << '\n';
                break;
            }
            for (int i = 2; i < line.size(); i++) {//grab typeString
                newChar += line[i];
            }
            if (!T::check(newChar, latinChar)) {//check for valid data
                error = true;
                break;
            }
            T newTChar(newChar, latinChar);
            if (dict.doesExist(newTChar)) {//check if already exists
                error = true;
                std::cerr << "ERROR: attempting to add a new " << fileName << " character "<< newChar << ":" << latinChar << " that is not unique.\n";
            } else {
                dict.addNewChar(newTChar);//add to characters vector
            }
        }
    }
    else{
        std::cerr << "ERROR: Could not open the "<< fileName <<".txt file.\n";
        return false;
    }
    //function execution results
    if (error){
        std::cerr << "ERROR: loadAlphabet failed.\n";
        dict.displayAlphabet();
        return false;
    }

    std::cout << fileName <<" alphabet loading SUCCESS.\n";
    return true;
}

template <class T>
bool readFile(Alphabet<T> &dict, std::vector<T> &typeMsg, std::string &inFile) {//reads morse and braille file types
    //load file
    std::ifstream in;
    in.open(inFile);
    std::string line;
    bool error = false;

    //get string/line
    if (in) {
        while(getline(in, line)){
            if(T::readLine(dict, typeMsg, line)){
                //successfull read typeMsg should now have characters
            } else {
                std::cerr << "ERROR: an error occured when trying to read input message.\n";
                return false;
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

template <class T> 
bool reportMsg(std::vector<T> &typeMsg, Alphabet<T> &dict){//reports on morse and braille types
    //report on length of message.
    std::cout << "\t\t:REPORT:\n\n";
    std::cout << "Message Size:\t" << typeMsg.size() << '\n';
    //gathering data
    if (!typeMsg.empty()){
        std::cout << "Message:\t";
        for (int i = 0; i < typeMsg.size(); i++){
            std::cout << typeMsg[i].getChar() << " ";
        }
        std::cout << '\n';
        std::cout << "Symbol Counts:\n";
        if(!T::getSymbolCount(typeMsg)){
            std::cerr << "ERROR: getSymbolCount failed.\n";
            return false;
        }
        std::cout << "Character Distribution:\n";
        std::map<std::string, int> dist;
        std::map<std::string, int>::iterator it;
        for (int i = 0; i < typeMsg.size(); i++){
            if (dist.empty()){
                dist[typeMsg[i].getChar()] = 1;
            } else if (dist.find(typeMsg[i].getChar()) != dist.end()){
                //map contains the key, increment its value
                it = dist.find(typeMsg[i].getChar());
                it->second++;
            } else if (dist.find(typeMsg[i].getChar()) == dist.end()){
                //map doesnt contain key, add to map
                dist[typeMsg[i].getChar()] = 1;
            }
        }
        std::cout << "Character:\tCount\n";
        for(auto const& item : dist){
            std::string temp = item.first;
            T tempItem = dict.getByTypeStr(temp);
            std::cout << item.first << " " << tempItem.getLatChar() << " \t:\t" << item.second << '\n';
        }
    } else {
        std::cout << "There are not characters logged to typeMsg.\n";
    }

    std::cout<< "END OF REPORT.\n";
    return true;
}

template <class T>
bool writeFile(std::vector<T> &outMsg, std::string &outFile){//writes morse and braille type functions to outfile
    std::ofstream oFile(outFile);
    if(oFile.is_open()){
        for (int i = 0; i < outMsg.size(); i++){
            oFile << outMsg[i].outputChar();
        }
        return true;
    } else {
        std::cerr << "ERROR: writeFile could not open the out file.\n";
        return false;
    }
}


#endif
