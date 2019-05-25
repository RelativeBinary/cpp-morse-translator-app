#ifndef TEMP_H
#define TEMP_H
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class morseChar {
    private:
        T cust;
        char latin;
    public:
        morseChar(T, char);
        T getCustChar();
        char getLatin();
};

template <typename T>
class alphabet {
    private:
        T characters[27]; //a-z and whitespace
    public: 
        void push(T const&);
        void pop();
        bool isEmpty() {
            return characters.empty();
        }
};


#endif

