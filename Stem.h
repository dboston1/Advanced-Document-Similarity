#ifndef Stem_H_INCLUDE
#define Stem_H_INCLUDE

#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::cerr;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<map>
using std::map;
#include<unordered_map>
using std::unordered_map;


// Now, vectors are initialized once per document, not per word. Still need to 
// optimize functions themselves

class Stem {
public:
    Stem(unordered_map<string, string> excMap);
    unordered_map<string, string> exMap;
    vector<string> step_7Vec;
    vector<string> step_3_1Vec;
    vector<string> step_3_2Vec;
    vector<string> step_3_2_2Vec;
    vector<string> step_5Vec;
    unordered_map<string, string>::iterator exIter;
    
    const string vowels = "aeiou";
    void start(string& word);
    bool yIsVowel(string& word, int index);
    bool isVowel(string& word, int index);
    bool isDouble(string& word, int index);
    bool liEnding(string& word);
    string region1(string& word);
    string region2(string& word);
    bool contains(string& word, string suffix);
    string preceder(string& word, unsigned int suffix_size);
    bool shortSyllable(string& word);
    bool isShort(string& word);
    void step1(string& word);
    void step2(string& word);
    bool endsWith(string& word, string suffix);
    string replaceSuffix(string& word, const string& suffix, const string& replaceWith);
    bool containsVowel(string& word);
    void step3(string& word);
    void step3Part2(string& word);
    string endsWith(string& word, vector<string>& suffixVec);
    vector<string> step3Vec1();
    vector<string> step3Vec2();
    vector<string> step3Vec2_2();
    bool isDouble(string& word);
    void step4(string& word);
    void step5(string& word);
    void step6(string& word);
    vector<string> step5Vec();
    void step7(string& word);
    vector<string> step7Vec();
    void step8(string& word);
    bool endsInShortSyllable(string& word);
};

#endif
