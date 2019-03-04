
#include<Parse_File.h>
#include<Stem.h>
#include<Stem_Exceptions.h>
#define apos '\''

unordered_map<string, int> Parse_File::parseStart(string filename){
    Parse_File:: wordCount.clear();
    Parse_File::ambiguousCap.clear();
    endOfSent = true; 
    possiblyAddPlus = false;
    numOfSentences = 0;
    numOfLetters = 0;
    numOfWords = 0;
    ifstream fOpen(filename);
    string temp = "";
    while(!((fOpen >> ws).peek() == EOF)){  
        fOpen >> temp;
        Parse_File::split(temp);
    }
    Parse_File::resolveAmbiguous();
    return Parse_File::wordCount;
}

void Parse_File::resolveAmbiguous(){
    string check = "";
    for(unordered_map<string, int>::iterator iter = ambiguousCap.begin(); iter != ambiguousCap.end(); iter++){
        check = iter->first;
        if(wordCount.count(check) != 0){
            wordCount.at(check) += iter->second;
        }
        else{
            check.front() = tolower(check.front());
            if(check.size() > 2){
                stemObj.Stem::start(check);
            }
            
            if(Parse_File::wordCount.count(check) != 0)
                Parse_File::wordCount.at(check) += iter->second;
            else
                Parse_File::wordCount[check] = iter->second;
        }
    }
}

void Parse_File::addToAmbMap(string& word){
    if(Parse_File::ambiguousCap.count(word) != 0){
        Parse_File::ambiguousCap.at(word) += 1;
    }
    else{
        Parse_File::ambiguousCap[word] = 1;
    }
    
}


void Parse_File::addToMap(string& word){
    if(Parse_File::wordCount.count(word) != 0){
        Parse_File::wordCount.at(word) += 1;
    }
    else{
        Parse_File::wordCount[word] = 1;
    }
    
}
    


void Parse_File::split(string& s){
    
    while(s.size() > 0){              
        if(isspace(s.front()))
            s.erase(0,1);
        char firstChar = s.at(0);
        
        if(isalpha(firstChar) || firstChar == apos || isdigit(firstChar) || firstChar == apos){    
            s = Parse_File::isAlphaNum(s);
        }
        else if(firstChar == '.' || firstChar == ','){
            if(checkDigitAfterPunct(s, 0)){
                endOfSent = false;
                s = isAlphaNum(s);
            }
            else{
                s = Parse_File::isPunct(s);
            }
        }
        else{
            s = Parse_File::isPunct(s);
        }  
    }
}



string Parse_File::isAlphaNum(string &s){
    ++numOfWords;
    bool stem_var = true;
    string word = "";
    char firstChar = s.at(0);
    if(endOfSent && isupper(firstChar)){ // need acronym check, digit in word check
        stem_var = false;
        possiblyAddPlus = true;
        
    }
    if(isupper(firstChar) || isdigit(firstChar)){
        stem_var = false;
    }
    
    endOfSent = false;
    word += firstChar;
    for (unsigned int i = 1; i < s.size(); ++i){        // check for more alphabetic chars
        char nextChar = s[i];
        
        if(isdigit(nextChar) || isupper(nextChar)){
            stem_var = false;
            possiblyAddPlus = false;
        }
        
        if (!ispunct(nextChar) || nextChar == apos){
            word += nextChar;
        }
        else if (nextChar == '.' || nextChar == ','){
            if(Parse_File::checkDigitAfterPunct(s, i)){
                stem_var = false;
                word += nextChar;
                possiblyAddPlus = false;
            }
            else{
                if(possiblyAddPlus == true){
                    numOfLetters += word.size();        //NOTE
                    Parse_File::addToAmbMap(word);     //////////////
                    possiblyAddPlus = false;
                    stem_var = false;
                }
                
                else if(!stem_var || (word.size() < 3)){
                    numOfLetters += word.size();        //NOTE
                    Parse_File::addToMap(word);   
                }
                else{
                    numOfLetters += word.size();        //NOTE
                    stemObj.Stem::start(word);
                    Parse_File::addToMap(word);
                }
                return s.substr(i, s.size());
            }
        }
        else{
            if(possiblyAddPlus == true){
                numOfLetters += word.size();        //NOTE
                Parse_File::addToAmbMap(word);     //////////////
                possiblyAddPlus = false;
                stem_var = false;
            }
            else if(!stem_var || (word.size() < 3)){
                numOfLetters += word.size();        //NOTE
                Parse_File::addToMap(word);  
            }
            else{
                numOfLetters += word.size();        //NOTE
                stemObj.Stem::start(word);                         ////////////change
                Parse_File::addToMap(word);
            }   
            return s.substr(i, s.size());
        }
    }
    if(possiblyAddPlus == true){        
        numOfLetters += word.size();        //NOTE
        Parse_File::addToAmbMap(word);         //////////
        possiblyAddPlus = false;
        stem_var = false;
    }
    else if(!stem_var || (word.size() < 3)){
        numOfLetters += word.size();        //NOTE
        Parse_File::addToMap(word);   
    }
    else{
        numOfLetters += word.size();        //NOTE
        stemObj.Stem::start(word);
        Parse_File::addToMap(word);
    }      
    return "";
}

bool Parse_File::checkDigitAfterPunct(string &s, unsigned int index){
    if(index < (s.size() - 1)){
        char nextChar = s.at(index+1);
        if(index != 0){
            char prevChar = s.at(index-1);
            if(isdigit(prevChar) && isdigit(nextChar))
                return true;
            else if (isalpha(prevChar) && isdigit(nextChar) && s.at(index) == '.'){
                s.insert((index+1), " ");
                return false;
            }
            
        }
        else if ( (index == 0) && (s.at(index) == '.') ){
            if(isdigit(nextChar))
                return true;            
        }
        
    }
    if (s.at(index) == '.')
        Parse_File::endOfSent = true;
    
    return false;
}

string Parse_File::isPunct(string &s){
    Parse_File::endOfSent = false;
    string word = "";
    for (unsigned int i = 0; i < s.size(); ++i){
        char nextChar = s.at(i);
        if (nextChar == '.' || nextChar == '!' || nextChar == '?'){
            if(endOfSent == false){
                ++numOfSentences;       //NOTE
            }
            word += nextChar;
            Parse_File::endOfSent = true;
        }
        else if (ispunct(nextChar) && nextChar != apos){
            word += nextChar;
        }
        else{
            //Parse_File::addToMap(word);                   ////////////////////////////////////////
            return s.substr(i, s.size());
        }
    }
   // Parse_File::addToMap(word);                       ////////////////////////////////////////
    return "";
    
}
    
