#ifndef Parse_File_H_INCLUDE
#define Parse_File_H_INCLUDE

#include<Stem.h>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::ostream;
#include<fstream>
using std::ifstream;
using std::ws;
#include<sstream>
using std::stringstream;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<cstring>
using std::strlen;
#include<algorithm>
using std::sort;
#include<unordered_map>
using std::unordered_map;
#include<map>
using std::map;
#include<Stem_Exceptions.h>

// parse_file takes in a filename, which it verifies is valid, opens, and reads. It determines if word is an exception, should be stemmed, etc. and adds to map<string, int>. 


class Parse_File{
public:
    inline Parse_File(Stem_Exceptions& obj) : stemObj(obj.Stem_Exceptions::getExceptions()){};
    unordered_map<string, int> parseStart(string filename);      // change to unordered_map 
    void addToMap(string& word);
    void addToAmbMap(string& word);
    string isAlphaNum(string &s);
    string isPunct(string &s);
    bool checkDigitAfterPunct(string &s, unsigned int index);
    void split(string& s);
    bool endOfSent;         // beginning of sentence applies to first iteration       
    bool possiblyAddPlus;
    unordered_map<string, int> wordCount;
    unordered_map<string, int> ambiguousCap;
    void resolveAmbiguous();
    Stem stemObj;
    int numOfSentences;
    int numOfWords;
    int numOfLetters;
    inline int getNumOfWords(){return numOfWords;};
    inline int getNumOfSentences(){return numOfSentences;};
    inline int getNumOfLetters(){return numOfLetters;};
    
};

#endif
