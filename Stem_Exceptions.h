#ifndef Stem_Exceptions_H_INCLUDE
#define Stem_Exceptions_H_INCLUDE

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


class Stem_Exceptions{
public:
    int setExceptions(string filename);
    unordered_map<string,string> exceptions;
    inline unordered_map<string, string> getExceptions(){return exceptions;};
};

#endif

