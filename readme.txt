# Code Translator-anator

This is a small project which can code and decode messages from a given translation template.

## How to use
To run this project you'll need to compile the program into a TS executable with a given input and output text file

### Example 
g++ -std=c++11 main.cpp template.cpp -o TS

## Execution
On execution the command is:

./TS [From] [To] In.txt Out.txt

[From] - Indicates the source alphabet. | M, B or L |
 
[To] - Indicates the target alphabet. | M, B or L |

### Example

./TS M B Morse1.txt OutputFile.txt