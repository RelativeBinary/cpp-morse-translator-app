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
        loadAlphabet(mDict, "Morse");

        Alphabet<brailleChar> bDict;
        loadAlphabet(bDict, "Braille");

        //testing
        //mDict.displayAlphabet();
        //bDict.displayAlphabet();

        std::vector<char> latinMsg;
        std::vector<morseChar> morseMsg;
        std::vector<brailleChar> brailleMsg;
        //using FROM send inMsgFileDie to alphabet of FROM type using std::vector xDict.READFILE(inMsgFileDir); returning the translated result to a vector in main.
        //if its latin then just split the string into a char vector
        bool processError = false;
        std::string whyError = "";
        if (From == 'L' && To == 'M') { //Latin to Morse
            if(readLatFile(latinMsg, inFile)){//Read latin file from inFile arg
                reportLatMsg(latinMsg);
                if (mDict.translateFromLatin(latinMsg, morseMsg)){//translate inMsg to outMsg
                    reportMsg(morseMsg, mDict);
                    if(!writeFile(morseMsg, outFile)){//write outMsg to file
                        whyError = "writeFile failed.\n";
                        processError = true;
                    }
                } else{
                    whyError = "translation failed.\n";
                    processError = true;
                }
            } else {
                whyError = "readLatFile failed.\n";
                processError = true;
            }
        } else if (From == 'L' && To == 'B') { //Latin to Braille
            if(readLatFile(latinMsg, inFile)){ //Read latin file from inFile arg
                reportLatMsg(latinMsg);
                if (bDict.translateFromLatin(latinMsg, brailleMsg)){//translate inMsg to outMsg
                    reportMsg(brailleMsg, bDict);
                    if(!writeFile(brailleMsg, outFile)){//write outMsg to file
                        whyError = "writeFile failed.\n";
                        processError = true;
                    }
                } else{
                    whyError = "translation failed.\n";
                    processError = true;
                }
            } else {
                whyError = "readLatFile failed.\n";
                processError = true;
            }
        } else if (From == 'M' && To == 'L') { //Morse to Latin
            if(readFile(mDict, morseMsg, inFile)){ //Read morse file from inFile arg
                reportMsg(morseMsg, mDict);
                if (mDict.translateToLatin(morseMsg, latinMsg)){ //translate to latin
                    reportLatMsg(latinMsg);
                    if(!writeLatFile(latinMsg, outFile)){ //write latinMsg to outFile
                        whyError = "writeFile failed to output latin.\n";
                        processError = true;
                    }
                } else{
                    whyError = "translation between morse and latin failed.\n";
                    processError = true;
                }
            } else {
                whyError = "readFile failed to read morse inMsg.\n";
                processError = true;
            }
        } else if (From == 'M' && To == 'B') { //Morse to Braille
            if (readFile(mDict, morseMsg, inFile)){//read morseMsg
                reportMsg(morseMsg, mDict);
                if(mDict.translateToLatin(morseMsg, latinMsg)){//first translate to latin
                    if(bDict.translateFromLatin(latinMsg, brailleMsg)){//translate to braille 
                        reportMsg(brailleMsg, bDict);
                        if(!writeFile(brailleMsg, outFile)){//write to outFile
                            whyError = "writeFile failed.\n";
                            processError = true;
                        }
                    } else {
                        whyError = "translation to braille failed.\n";
                        processError = true;
                    }
                } else {
                    whyError = "failed to translate morseMsg to latinMsg.\n";
                    processError = true;
                }
            } else {
                whyError= "readFile failed to read the morse message.\n";
                processError = true;
            }
        } else if (From == 'B' && To == 'L') { //Braille to Latin
            if(readFile(bDict, brailleMsg, inFile)){ //Read the braille msg
                reportMsg(brailleMsg, bDict);
                if (bDict.translateToLatin(brailleMsg, latinMsg)){ //translate to latin
                    reportLatMsg(latinMsg);
                    if(!writeLatFile(latinMsg, outFile)){
                        whyError = "writeFile failed to output latin.\n";
                        processError = true;
                    }
                } else {
                    whyError = "translation between braille and latin failed.\n";
                }
            } else {
                whyError = "readFile failed to read braille inMsg.\n";
                processError = true;
            }
        } else if (From == 'B' && To == 'M') { //Braille to Morse
            if (readFile(bDict, brailleMsg, inFile)){//read brailleMsg
                reportMsg(brailleMsg, bDict);
                if(bDict.translateToLatin(brailleMsg, latinMsg)){//first translate to latin
                    if(mDict.translateFromLatin(latinMsg, morseMsg)){//translate to morse
                        reportMsg(morseMsg, mDict);
                        if(!writeFile(morseMsg, outFile)){//write to outFile
                            whyError = "writeFile failed.\n";
                            processError = true;
                        }
                    } else {
                        whyError = "translation to morse failed.\n";
                        processError = true;
                    }
                } else {
                    whyError = "failed to translate braille to latinMsg.\n";
                    processError = true;
                }
            } else {
                whyError= "readFile failed to read the braille message.\n";
                processError = true;
            }
        } else {
            std::cerr << "ERROR: Unknown request to translate from '" << From << "' to '" << To << "'.\n";
        }

        if (processError){
            std::cerr << "ERROR: " << whyError << '\n';
            //program 'ends' here
        }else {
            std::cout << "PROGRAM TERMINATED\n";
        } 

    } else {
        std::cerr << "ERROR: Invalid arguments passed ending program.\n";
    }
    return 0;
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

