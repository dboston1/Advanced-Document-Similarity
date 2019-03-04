#include<Driver.h>
#include<Stem_Exceptions.h>
#include<Parse_File.h>
#include<iomanip>
#include<math.h>
using std::setprecision;


int Driver::start(char* argv[]){
    

    if(checkValidFile(argv[1]) != 0){        // first file (to compare)
        return -1;
    }
    if(checkValidFile(argv[2]) != 0){       // file of filenames (first is exception)
        return -1;
    }
    string exceptionsFile;
    ifstream fOpenD(argv[2]);
    fOpenD >> exceptionsFile;        // safe, we know per checkValidFile it contains at least something besides WS
    if(stemExcObj.Stem_Exceptions::setExceptions(exceptionsFile) != 0){
        return -1;
    }
    if((fOpenD >> ws).peek() == EOF){
        cout << "Error: File of filenames only contained exception filename" << endl;
        return -1;
    }
    Parse_File parseObj(stemExcObj);
    string firstFileName = argv[1];
    stemmed_docs.push_back(parseObj.Parse_File::parseStart(firstFileName)); //don't care about first's reading level
    
    
    string nextFileName;
    while((fOpenD >> ws).peek() != EOF){
        fOpenD >> nextFileName;
        if(checkValidFile(nextFileName) != 0){
            return -1;
        }
        else{
                                                  /////////////
            fileNames.push_back(nextFileName);
            stemmed_docs.push_back(parseObj.Parse_File::parseStart(nextFileName));
            int numOfSentences = parseObj.Parse_File::getNumOfSentences();
            int numOfWords = parseObj.Parse_File::getNumOfWords();
            if(numOfWords == 0){
                cout << "Error: Number of Words = 0; Reading Level Requires Dividing By Number Of Words. Cannot Divide By Zero" << endl;
                return -1;
            }
            int numOfLetters = parseObj.Parse_File::getNumOfLetters();
                                                     /////////////
            double readingLevel = Driver::readingLevel(numOfSentences, numOfWords, numOfLetters);
            reading_levels.push_back(readingLevel);
                                              ////////////
        }
    }
   Driver::calculation();      //  used for TFIDF
    

    return 0;
}


double Driver::readingLevel(int numOfSentences, int numOfWords, int numOfLetters){      // already checked for numOfWords == 0 error case
    double L = double(numOfLetters) / double(numOfWords) * 100;
    double S = double(numOfSentences) / double(numOfWords) * 100;
    return ((0.0588 * L) - ((0.296 * S) + 15.8)); 
}


int Driver::checkValidFile(string filename){
    ifstream fOpen(filename);         // opens file to be read 
    if (fOpen.fail()){ 
        cerr << "failed to open file: " << filename << endl; // 
        return -1;
    }
    if((fOpen >> ws).peek() == EOF){        // checks if file is empty at beginning
        cerr << "file: " << filename << " was empty" << endl;
        return -1;
    }
    return 0;   
}

void Driver::calculation(){
  //  unordered_map<string, int> tempUn = stemmed_docs[8];          //uncomment to print unordered_map (stemmed_doc[0] -- could also do in loop)
   // Driver::order_and_print_map(tempUn);
    Driver::TFIDF();      // uncomment this to calculate TFIDF w/ multiple documents 
    
}

void Driver::order_and_print_map(unordered_map<string, int> tempUn){
    map<string, int> temp;
    for(unordered_map<string, int>::iterator iter = tempUn.begin(); iter != tempUn.end(); iter++){
        if(temp.count(iter->first) != 0)
            cout << "error in Driver::calculation" << endl;
        temp[iter->first] = iter-> second;
    }
    for(map<string, int>::iterator iter = temp.begin(); iter != temp.end(); iter++){
        cout << iter->first << " " << iter->second << endl;
    }
}       

void Driver::TFIDF(){       //NOTE:: Assignment 6 had us not consider punctuation strings
        for(unsigned int i = 1; i < stemmed_docs.size(); i++){
            if((reading_levels.at((i-1)) >= lowReadingBound) && (reading_levels.at((i-1)) <= upperReadingBound)){
                tfidf_scores.push_back(compare_two(stemmed_docs[0], stemmed_docs[i], 0, i));
            }
            else{
                tfidf_scores.push_back(-1);     // so, 
            }
    }
//     for (unsigned int j = 0; j < tfidf_scores.size(); j++){
//         cout << fileNames.at(j) << "   " << tfidf_scores.at(j) << endl;
//     }
        double max = -1;
        int position = -1;
        int temp;
        for(unsigned int j = 0; j < tfidf_scores.size(); j++){
            temp = tfidf_scores.at(j);
            if(temp > max){
                max = temp;
                position = j;
            }
        }
        if(position == -1){
            cout << "No matches found for given query document and reading level range." << endl;
            return;
        }
        cout << fileNames.at(position) << endl;
}

double Driver::compare_two(unordered_map<string, int>& A, unordered_map<string, int>& B, unsigned int A_index, unsigned int B_index){
    double sum_of_TFIDF = 0.0;
    string checkA = "";
    for(unordered_map<string, int>::iterator iterA = A.begin(); iterA != A.end(); iterA++){
        checkA = iterA->first;
        if(B.count(checkA) != 0){           // if B contains the word from A....
            double A_tf = double(iterA->second);        
            double B_tf = double(B.at(checkA));          // now we have both TF's, need IDF
            double n = 0.0;
            double idf = 0.0;
           if(check_if_we_know_idf.count(checkA) != 0){
               idf = check_if_we_know_idf.at(checkA);
           }
           else{
                for(unsigned int i = 0; i < stemmed_docs.size(); i++){
                    if((i == A_index) || (i == B_index)){     // because we already know the word exists in A and B
                        n += 1.0;
                    }
                    else{
                        if(stemmed_docs[i].count(checkA) != 0)   // if a doc not A or B contains word, add 1 to n
                            n += 1.0;
                    }
                }
                idf = double(stemmed_docs.size()) / n;
                idf = log10(idf);
               check_if_we_know_idf[checkA] = idf;
           }
            double A_tfidf = A_tf * idf;
            double B_tfidf = B_tf * idf;
            sum_of_TFIDF += A_tfidf * B_tfidf;
        }
    }
    return sum_of_TFIDF;
}
    





