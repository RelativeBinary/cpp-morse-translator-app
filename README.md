# Code Translator-anator

This is a small project which can code and decode messages from a given translation template.

## How to use
To run this project you'll need to compile the program into a TS executable with a given input and output text file

### Example 
g++ -std=c++11 *.cpp -o TS

## Execution
On execution the command is:

`./TS [From] [To] In.txt Out.txt`

`[From]` - Indicates the source alphabet. | M, B or L |
 
`[To]` - Indicates the target alphabet. | M, B or L |

### M = Mores. 
 - Morse uses sequences of dots (.) and dashes (-) to represent letters and numbers. Although this program is limited to just using letters, and a symbol for space. 
 - The translation rule for Latin to Morse is given in the file `Morse.txt`.
 - `----` dashes to represent a whitespace in Morse. *this is not part of standard morse code*

### B = Braille.
- Braille uses a 2 by 3 grid of flat or raised positions. Which are represented in a binary string i.e. `000000` = all flat positions
- Since we are only limited to letters and space 6 bits is enough
- The translation rule for Latin to Braille is given in the file `Braille.txt`
- `000000` in braille to represent whitespace

### L = Latin.
- The allowed symbols are the standard lower case letters used in English and a space ' '.

### How it works

- Containers/arrays will hold objects of an appropriate alphabet
- One container will hold all the 'characters' read in from `In.txt`
- One container will hold all the 'characters' after being translated into the output code, ready to be fed into `Out.txt`
- Translating between [B] and [M] *and vise versa* will require an additional container to store intermediate [L] translation

#### Processes
1. Execution : ./TS [From] [To] In.txt Out.txt
2. The program will begin preperations for the appropriate aplphabets
   - The [From] and [To] classes will be initialized based on the input.
   - The translation rules will be taken from the files
   - Translation rules will then be updated on the Morse and Braille classes
   - The system will validate and report on the loading processes (durring and after).
3. Validation 
   - Involes making sure only appropriate Morse/Braille symbols are used and that every Latin letter is mapped uniquely.
4. In.txt file will start being read into a container of symbols and at the same time the program will check if each symbol is consistent with the alphabet being used.
5. Report - after reading In.txt the file will report on the over all length (*based on number of symbols*) and the symbol distribution within it.
6. Translation - The program will now begin cycling through the In.txt container and converting each symbol into the corresponding [To] alphabet and placing it in the output container.
7. Report - after translation is complete another report displaying the length and symbol distribution of the out.txt container will be displayed, including the output txt
8. Out.txt the contents of out.txt's container will then be fed into the appropriate file.

### Notes

- To translate morse to braille or vice versa the message will need to be converted to latin which will be done within the program
- The alphabet file names are hard coded.
- "An instance of one of the alphabet classes contains a single valid symbol for that class." There is only one argument specifier for a certain language, otherwise error incorrect input.