#include <iostream> 
#include <fstream> 
#include <string> 


int main(){
    std::ifstream inFile;
    inFile.open("Morse.txt");
    std::string line;
    bool error = false;
    if (inFile){
        while (getline(inFile, line))
        {
            std::cout << "line: " << line << '\n';

            char latinchar = line[0];
            std::string morseChar ;
            if (line[0] != line[0]){
                //check that the first char is latin
                error = true;
                std::cerr << "ERROR: latin character refenced is not valid aborting program. \n";
                break;
            } else if (line[1] != ' '){
                error = true;
                std::cerr << "ERROR: poorly formed expression, expected space between morse character and latin character. \n";
                break;
            }
            for (int i = 2; i < line.size(); i++){
                if(line[i] == '.' || line[i] == '-'){
                    morseChar += line[i];
                } else {

                }
            }
            std::cout << "LATIN: " << latinchar << '\n';
            std::cout << "MORSE: " << morseChar << '\n';
            

        }
    } else {
        std::cout << "error could not open file";
    }
    if (error){
        std::cerr << "program aborted\n";
    }
}