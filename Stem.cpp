#include<Stem.h>
//using std::Stem;
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
#include<fstream>
using std::ifstream;
using std::ws;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<cstring>
using std::strlen;
#include<ctype.h>
using std::tolower;
#include<unordered_map>
using std::unordered_map;


// NOTE : for future reference, a vector of strings passed to endsWith method was the way to go

Stem::Stem(unordered_map<string, string> excMap){      // ok to be reference? 
    Stem::exMap = excMap;
    Stem::step_7Vec = Stem::step7Vec();
    Stem::step_5Vec = Stem::step5Vec();
    Stem::step_3_1Vec = Stem::step3Vec1();
    Stem::step_3_2Vec = Stem::step3Vec2();
    Stem::step_3_2_2Vec = Stem::step3Vec2_2();
}


vector<string> Stem::step7Vec(){
    vector<string> temp;
    temp.push_back("al");
    temp.push_back("ance");
    temp.push_back("ence");
    temp.push_back("ize");
    temp.push_back("er");
    temp.push_back("ic");
    temp.push_back("able");
    temp.push_back("ible");
    temp.push_back("ant");
    temp.push_back("ement");
    temp.push_back("ment");
    temp.push_back("ent");
    temp.push_back("ism");
    temp.push_back("ate");
    temp.push_back("iti");
    temp.push_back("ous");
    temp.push_back("ive");

    return temp;
}
    
    
    
vector<string> Stem::step3Vec2_2(){
    vector<string> temp;
    temp.push_back("at");
    temp.push_back("bl");
    temp.push_back("iz");
    return temp;
}
    

vector<string> Stem::step3Vec1(){
    vector<string> temp;
    temp.push_back("eed");
    temp.push_back("eedly");
    return temp;
}
vector<string> Stem::step3Vec2(){
    vector<string> temp;
    temp.push_back("ed");
    temp.push_back("edly");
    temp.push_back("ing");
    temp.push_back("ingly");
    return temp;
}

vector<string> Stem::step5Vec(){
    vector<string> temp;
    temp.push_back("ational");
    temp.push_back("ization");
    temp.push_back("tional");
    temp.push_back("ation");
    temp.push_back("ator");
    temp.push_back("izer");
    temp.push_back("enci");
    temp.push_back("anci");
    temp.push_back("abli");
    temp.push_back("entli");
    temp.push_back("alism");
    temp.push_back("aliti");
    temp.push_back("alli");
    temp.push_back("fulness");
    temp.push_back("ousness");
    temp.push_back("ousli");
    temp.push_back("iveness");
    temp.push_back("iviti");
    temp.push_back("biliti");
    temp.push_back("bli");
    temp.push_back("ogi");
    temp.push_back("fulli");
    temp.push_back("lessli");
    temp.push_back("li");
    return temp;
}




// working on converting to maps etc right now. still compiles w errors

void Stem::start(string& word){      
    if(word.size() < 3)
        return;
    if(Stem::exMap.count(word) != 0){
        word = Stem::exMap.at(word);    
        return;
    }    
    Stem::step1(word);
}
    

void Stem::step1(string& word){
    
    if(word.at(0) == '\'')
       word = word.substr(1);
    
    if(Stem::endsWith(word, "\'s\'"))
        word = Stem::replaceSuffix(word, "\'s\'", "");
    else if(Stem::endsWith(word, "\'s"))
        word = Stem::replaceSuffix(word, "\'s", "");
    else if(Stem::endsWith(word, "\'"))
        word = Stem::replaceSuffix(word, "\'", "");
    
    Stem::step2(word);
}
    

void Stem::step2(string& word){
   // cout << "step 2: " << word << endl;
    
    if(Stem::endsWith(word, "sses")){
        word = Stem::replaceSuffix(word, "sses", "ss");
    }
    else if((Stem::endsWith(word, "ied") | (Stem::endsWith(word, "ies")))){
        string temp = Stem::preceder(word, 3);
        if (temp.size() > 1)
            word = Stem::replaceSuffix(word, "ied", "i");
        else
            word = Stem::replaceSuffix(word, "ied", "ie");
    }
    else if(Stem::endsWith(word, "ss") || Stem::endsWith(word, "us"))
        return Stem::step3(word);
    else if(Stem::endsWith(word, "s")){
        string temp = Stem::preceder(word, 2);
        if(Stem::containsVowel(temp))
            word = Stem::replaceSuffix(word, "s", "");
    }
    Stem::step3(word);
}

void Stem::step3(string& word){
   // cout << "step 3: " << word << endl;
    
    string regionOne = Stem::region1(word);
    //vector<string> condition1 = Stem::step3Vec1();
    //vector<string> condition2 = Stem::step3Vec2();
    string suffix = Stem::endsWith(word, Stem::step_3_1Vec);
    if(suffix != ""){
        if(Stem::endsWith(regionOne, suffix))
            word = Stem::replaceSuffix(word, suffix, "ee");
        return Stem::step4(word);
    }
    suffix = Stem::endsWith(word, Stem::step_3_2Vec);
    if(suffix != ""){
        string temp = Stem::preceder(word, suffix.size());
        if (Stem::containsVowel(temp)){
            word = Stem::replaceSuffix(word, suffix, "");
            Stem::step3Part2(word);
            return;
        }
    }
    Stem::step4(word);
}

void Stem::step3Part2(string& word){
    //cout << "step 3 - part 2: " << word << endl;
    
   // vector<string> condition2_2 = Stem::step3Vec2_2();
    if(Stem::endsWith(word, Stem::step_3_2_2Vec) != "")
        word += "e";
    else if(Stem::isDouble(word))
        word = Stem::replaceSuffix(word, "Z", "");
    else if(Stem::isShort(word))
        word += "e";
    Stem::step4(word);
}

void Stem::step4(string& word){
    //cout << "step 4: " << word << endl;
    
    if(Stem::endsWith(word, "y")){
        string temp = Stem::preceder(word, 1);
        if(temp.size() < 2){
            Stem::step5(word);
            return;
        }
        if(!(Stem::isVowel(word, word.size()-2)))
            word = Stem::replaceSuffix(word, "y", "i");
    }
     Stem::step5(word);
}

void Stem::step5(string& word){
  //  cout << "step 5: " << word << endl;
    
   // vector<string> step_5Vec = step5Vec();    
    string suffix = (Stem::endsWith(word, Stem::step_5Vec));
    if(suffix == ""){
        Stem::step6(word);
        return;
    }
    else if(suffix == "enci")
        word = Stem::replaceSuffix(word, suffix, "ence");
    else if(suffix == "anci")
        word = Stem::replaceSuffix(word, suffix, "ance");
    else if(suffix == "abli")
        word = Stem::replaceSuffix(word, suffix, "able");
    else if(suffix == "entli")
        word = Stem::replaceSuffix(word, suffix, "ent");
    else if(suffix == "izer" || suffix == "ization")
        word = Stem::replaceSuffix(word, suffix, "ize");
    else if(suffix == "ational" || suffix == "ation" || suffix == "ator")
        word = Stem::replaceSuffix(word, suffix, "ate");
    else if(suffix == "tional")
        word = Stem::replaceSuffix(word, suffix, "tion");
    else if(suffix == "alism" || suffix == "aliti" || suffix == "alli")
        word = Stem::replaceSuffix(word, suffix, "al");
    else if(suffix == "fulness")
        word = Stem::replaceSuffix(word, suffix, "ful");
    else if(suffix == "ousli" || suffix == "ousness")
        word = Stem::replaceSuffix(word, suffix, "ous");
    else if(suffix == "iveness" || suffix == "iviti")
        word = Stem::replaceSuffix(word, suffix, "ive");
    else if(suffix == "biliti" || suffix == "bli")
        word = Stem::replaceSuffix(word, suffix, "ble");
    else if(suffix == "fulli")
        word = Stem::replaceSuffix(word, suffix, "ful");
    else if(suffix == "lessli")
        word = Stem::replaceSuffix(word, suffix, "less");
    else if(suffix == "ogi" && word.size() > 3){
            if(word.at(word.size()-4) == 'l')
            word = Stem::replaceSuffix(word, suffix, "og");
    }
    else if(suffix == "li"){
        string temp = Stem::preceder(word, 2);
        if(Stem::liEnding(temp))
            word = Stem::replaceSuffix(word, suffix, "");
    }
    Stem::step6(word);
}
    
void Stem::step6(string& word){
  //   cout << "step 6: " << word << endl;
     
     string regionOne = Stem::region1(word);
     string regionTwo = Stem::region2(word);
     if(Stem::endsWith(word, "ational")){
         if(Stem::endsWith(regionOne, "ational"))
            word = Stem::replaceSuffix(word, "ational", "ate");
     }
     else if(Stem::endsWith(word, "tional")){
         if(Stem::endsWith(regionOne, "tional"))
            word = Stem::replaceSuffix(word, "tional", "tion");
     }
     else if(Stem::endsWith(word, "alize")){
         if(Stem::endsWith(regionOne, "alize"))
            word = Stem::replaceSuffix(word, "alize", "al");
     }
     else if(Stem::endsWith(word, "icate") || Stem::endsWith(word, "iciti")){
         if(Stem::endsWith(regionOne, "icate") || Stem::endsWith(regionOne, "iciti"))
            word = Stem::replaceSuffix(word, "iciti", "ic");
     }
     else if(Stem::endsWith(word, "ical")){
         if(Stem::endsWith(regionOne, "ical"))
            word = Stem::replaceSuffix(word, "ical", "ic");
     }
     else if(Stem::endsWith(word, "ful")){
         if(Stem::endsWith(regionOne, "ful"))
            word = Stem::replaceSuffix(word, "ful", "");
     }
     else if(Stem::endsWith(word, "ness")){
         if(Stem::endsWith(regionOne, "ness"))
            word = Stem::replaceSuffix(word, "ness", "");
     }
     else if (Stem::endsWith(word, "ative")){
         if(Stem::endsWith(regionTwo, "ative"))
            word = Stem::replaceSuffix(word, "ative", "");
     }
     Stem::step7(word);
}

void Stem::step7(string& word){
    //vector<string> strVec_7 = Stem::step7Vec();
    string regionTwo = Stem::region2(word);
    if(regionTwo == ""){
        Stem::step8(word);
        return;
    }
    string suffix = Stem::endsWith(word, step_7Vec);
    if(suffix != "" && Stem::endsWith(regionTwo, suffix))
        word = Stem::replaceSuffix(word, suffix, "");
    else if(Stem::endsWith(regionTwo, "ion")){ 
        string temp = Stem::preceder(word, 3);
        if(temp.at(temp.size()-1) == 's' || temp.at(temp.size()-1) == 't')
            word = Stem::replaceSuffix(word, "ion", "");
    }
  //  cout << word << " end of step 7 " << endl;
    Stem::step8(word);
}

void Stem::step8(string& word){
     string regionTwo = Stem::region2(word);
     string regionOne = Stem::region1(word);
     if(Stem::endsWith(regionTwo, "e"))
         word = Stem::replaceSuffix(word, "e", "");
     else if(Stem::endsWith(regionOne, "e")){
         if(!(Stem::endsInShortSyllable(word)))
             word = Stem::replaceSuffix(word, "e", "");
     }
     else if(Stem::endsWith(regionTwo, "l")){
         string temp = Stem::preceder(word, 1);
         if(temp.at(temp.size() -1) == 'l')
             word = Stem::replaceSuffix(word, "l", "");
     }
}
bool Stem::endsInShortSyllable(string& word){
    int word_index = word.size() -1;
    word_index--;
    if((word.size()-1) < 2)
        return false;
    if((word.size()-1) == 2){
        if(Stem::isVowel(word,0))
            if(!Stem::isVowel(word,1))
                return true;
    }
    if((word.size()-1) == 3){
        if(!Stem::isVowel(word,0))
            if(Stem::isVowel(word,1))
                if(!Stem::isVowel(word,2))
                    if(word.at(2) != 'w' && word.at(2) != 'x' && word.at(2) != 'y')
                        return true;
    }
    if((word.size()-1) > 3){
        if(!Stem::isVowel(word, word_index)){
            char temp = word.at(word_index);
            if(temp != 'w' && temp != 'x' && temp != 'y'){
                word_index--;
                if(Stem::isVowel(word, word_index)){
                    word_index--;
                    if(!Stem::isVowel(word, word_index))
                        return true;
                }
            }
        }
    }
        return false;
}



// helper methods 
string Stem::replaceSuffix(string& word, const string& suffix, const string& replaceWith){         
    unsigned int suffix_size = suffix.size();
    unsigned int word_size = word.size();
    unsigned int new_size = word_size - suffix_size;
    if(new_size == 0)
        return replaceWith;
    string temp = word.substr(0, new_size);
    temp += replaceWith;
    return temp;
}

string Stem::endsWith(string& word, vector<string>& suffixVec){
    string temp;
    for(unsigned int i = 0; i < suffixVec.size(); i++){
        temp = suffixVec.at(i);
        if(Stem::endsWith(word, temp))
            return temp;
    }
    return "";
}

bool Stem::endsWith(string& word, string suffix){        
    if(!(Stem::contains(word, suffix)))
        return false;
    unsigned int suffix_size = suffix.size();
    unsigned int word_size = word.size();
    if(word_size == suffix_size)                // so word = "ing", suffix = "ing" returns true
        return true;
    if(suffix_size > word_size)
        return false;
    unsigned int new_size = word_size - suffix_size;
    string temp = word.substr(new_size);
    if(!(Stem::contains(temp, suffix)))
        return false;
    return true;
}    
    
    
bool Stem::yIsVowel(string& word, int index){
    if(index == 0)
        return false;
    else if(Stem::isVowel(word, (index-1)))
        return false;
    return true;
}

bool Stem::containsVowel(string& word){
    for (unsigned int i = 0; i < word.size(); i++){
        if(Stem::isVowel(word, i))
            return true;
    }
    return false;
}

bool Stem::isVowel(string& word, int index){
    char temp = word.at(index);
    if(temp == 'y')
        return Stem::yIsVowel(word, index);
    else if(vowels.find(temp) == string::npos)
        return false;
    return true;
}
bool Stem::isDouble(string& word){
    return Stem::isDouble(word, (word.size()-1));
}

bool Stem::isDouble(string& word, int index){        //NOTE: index here is second letter (ie if word is add, index should be 2 (second 'd'))
    if (index < 1)
        return false;
    else{
        string temp = word.substr((index-1), 2);
        if(temp == "bb" || temp == "ff" || temp == "dd" || temp == "gg" || temp == "mm" || temp == "nn" || temp == "pp" || temp == "rr" || temp == "tt")
            return true;
    }
    return false;
}

bool Stem::liEnding(string& word){
    if(word.size() == 0)
        return false;
    char temp = word.at(word.size()-1);
    if (temp == 'c' || temp == 'g' || temp == 'd' || temp == 'e' || temp == 'h' || temp == 'k' || temp == 'm' || temp == 'n' || temp == 'r' || temp == 't')
        return true;
    return false;
}

string Stem::region1(string& word){
    bool lastWasVowel = false;
    string temp = "";
    for (unsigned int i = 0; i < word.size(); i++){
        if((lastWasVowel == true) && (!(Stem::isVowel(word, i)))){
            if(i == word.size())
                return temp;
            else{
                temp = word.substr(i+1);
                break;
            }
        }
        if(Stem::isVowel(word, i)){
            lastWasVowel = true;
        }
    }
    
    return temp;
}

string Stem::region2(string& word){
   bool lastWasVowel1 = false;
   bool lastWasCons = false;
   bool lastWasVowel2 = false;
    string temp = "";
    for (unsigned int i = 0; i < word.size(); i++){
        if((lastWasVowel2 == true) && (!(Stem::isVowel(word,i)))){
            if(i == word.size())
                return temp;
            else{
                temp = word.substr(i+1);
                break;
            }
        }
        else if((lastWasVowel1 == true) && (Stem::isVowel(word, i)) && (lastWasCons == true)){
            lastWasVowel2 = true;
        }
        else if(Stem::isVowel(word, i)){
            lastWasVowel1 = true;
        }
        else if((lastWasVowel1 == true) && !Stem::isVowel(word, i))
            lastWasCons = true;
    }
    return temp;
}
    
bool Stem::contains(string& word, string suffix){
    if(suffix.size() > word.size())
        return false;
    if(word.find(suffix) != string::npos){
        return true;
    }
    return false;
}
    
string Stem::preceder(string& word, unsigned int suffix_size){ 
    unsigned int word_size = word.size();
    if(suffix_size >= word_size){                   
        return "";
    }
    unsigned int new_size = word_size - suffix_size;
    
    return(word.substr(0, new_size));
}    

bool Stem::shortSyllable(string& word){
    if(word == "")
        return false;
    if(word.size() < 2)
        return false;
    else if(word.size() == 2){
        if(Stem::isVowel(word, 0)){
            if(!Stem::isVowel(word, 1))
                return true;
        }
        return false;
    }
    unsigned int index = word.size() - 1;
    char temp = word.at(index);
    if((Stem::isVowel(word, index)) | (temp == 'w') | (temp == 'x') | (temp == 'y'))
        return false;
    index--;
    if(!(Stem::isVowel(word, index)))
        return false;
    index--;       
    if(Stem::isVowel(word, index))
        return false;
    return true;
}

bool Stem::isShort(string& word){
    if((Stem::region1(word) == "") && (Stem::shortSyllable(word)))
        return true;
    return false;
}
 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
