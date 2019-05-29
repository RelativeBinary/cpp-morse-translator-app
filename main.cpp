#include "template.h"

bool checkArguments(std::string, std::string, std::string, std::string);

int main(int argc, char* argv[]){
    //take check args
    bool validArgs = checkArguments(argv[1], argv[2], argv[3], argv[4]);
    char From, To; 
    std::string inFile, outFile;
    //assign args
    if (validArgs){
        std::cout << "Input arguments VALID.\n";
        char From = argv[1][0];
        char To = argv[2][0];
        std::string inFile = argv[3];
        std::string outFile = argv[4];

        //load alphabets and report the results of loading the alphabets
        Alphabet<morseChar> mDict;
        loadAlphabet(mDict);
        Alphabet<brailleChar> bDict;
        loadAlphabet(bDict);
        //using FROM send inMsgFileDie to alphabet of FROM type using std::vector xDict.READFILE(inMsgFileDir); returning the translated result to a vector in main.
        //if its latin then just split the string into a char vector

        //then a report method will be used to report the stats on the translated vector

        //READING FILE COMPLETE

        //TRANSLATE FILE
        //using TO send the resulting charvector to the appropriate alphabet and execute the translation command using if(TO == 'L') then outChars = xDict.ToLatin(inMsg)
        //if translating from 'M' to 'B' then have an intermediary step where a temp vector of latin translation is made using if(TO != 'L') then latinChars = xDictoLatin(inMsg) then  is dont again using TO's type by, if(TO == 'X') then latinChars = xDict.translateToTOType(tempLatin)
    } else {
        std::cerr << "ERROR: Invalid arguments passed ending program.\n";
    }

}

//USED TO CHECK INPUT
bool checkArguments(std::string From, std::string To, std::string inTxtFile, std::string outTxtFile){
    if (!(From.size() == 1)){
        std::cerr << "ERROR: Invalid From input size: " << From.size() << '\n';
        return false;
    }
    else{
        if (From[0] == 'M' || From[0] == 'B' || From[0] == 'L'){
            
        } else {
            std::cerr << "ERROR: Invalid From argument: " << From << '\n';
            return false;
        }
    }

    if (!(To.size() == 1)){
        std::cerr << "ERROR: Invalid To input size: " << To.size() << '\n';
        return false;
    }
    else{
        if (To[0] == 'M' || To[0] == 'B' || To[0] == 'L'){
            if (To == From){
                std::cerr << "ERROR: To and From are both the same argument: " << To << '\n';
                return false;
            }
        } else {
            std::cerr << "ERROR: Invalid To argument: " << To << '\n';
            return false;
        }
    }

    std::string inType = inTxtFile.substr(inTxtFile.size() - 4, 4);
    std::string outType = outTxtFile.substr(outTxtFile.size() - 4, 4);

    if (inType != ".txt" || outType != ".txt"){
        std::cerr << "ERROR: incorrect input/output file type specified. Expected .txt\n";
        return false;
    }//needs further checking


    return true;
}