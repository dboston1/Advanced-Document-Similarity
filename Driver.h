#ifndef Driver_H_INCLUDE
#define Driver_H_INCLUDE

#include<Stem_Exceptions.h>
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
#include<math.h>

// Driver creates exception map object from stem_exceptions, checks for errors in files, and populates a vector of stemmed documents (N). It will perform all calculations on stemmed documents as well.


class Driver{
public:
    vector<unordered_map<string, int> > stemmed_docs;
    vector<double> reading_levels;
    vector<double> tfidf_scores;
    vector<string> fileNames;
    inline Driver(double lR, double uR){lowReadingBound = lR; upperReadingBound = uR;};
    unordered_map<string, double> check_if_we_know_idf;
    double lowReadingBound;
    double upperReadingBound;
    int start(char* argv[]);        
    int checkValidFile(string filename);
    Stem_Exceptions stemExcObj;
    void calculation();
    void order_and_print_map(unordered_map<string, int> tempUn);
    void TFIDF();
    double compare_two(unordered_map<string, int>& A, unordered_map<string, int>& B, unsigned int A_index, unsigned int B_index);
    double readingLevel(int numOfSentences, int numOfWords, int numOfLetters);
    
};

#endif
