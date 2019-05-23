#include <iostream>
#include <string>

bool checkArguments(std::string, std::string, std::string, std::string);

int main(int argc, char* argv[]){
//take cli args

bool validArgs = checkArguments(argv[1], argv[2], argv[3], argv[4]);

if (validArgs){
    std::cout << "Valid Arguments were passed\n";
    char From = argv[1][0];
    char To = argv[2][0];
    std::string inFile = argv[3];
    std::string outFile = argv[4];
} else {
    std::cerr << "ERROR: Invalid arguments passed ending program.\n";
}
    //checks from In and Out Txt files

    return true;
}

bool checkArguments(std::string From, std::string To, std::string inTxtFile, std::string outTxtFile)
{
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
    return true;
}