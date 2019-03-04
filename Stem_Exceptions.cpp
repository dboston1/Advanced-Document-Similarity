
#include<Stem_Exceptions.h>


int Stem_Exceptions::setExceptions(string filename){
    ifstream fOpen(filename);
    if (fOpen.fail()){ 
        cerr << "failed to open exception file" << endl; // 
        return -1;
    }
    if((fOpen >> ws).peek() == EOF){        // checks if file is empty at beginning
        return 0;
    }
    string line = "";
    string temp0;
    string temp1;
    string errorCheck;
    while (!((fOpen >> ws).peek() == EOF)){       // while not at end of file, put items of file into vector
        getline(fOpen, line);
        if (fOpen.fail()){                          //redundant check - string input will not fail 
            cerr << "string input failed (exception file)" << endl;
            return -1;
        }
        stringstream str(line);
        str >> temp0;   
        str >> temp1;
        
        if(str.fail()){
            cerr << "error in exception file" << endl;
            return -1;
        }
        str >> errorCheck;
        if(!(str.fail())){
            cerr<< "error in exception file!" << endl;
            return -1;
        }
        Stem_Exceptions::exceptions[temp0] = temp1;       // will overwrite previous entries of identical exception - alright as clarified by project details
    }
    return 0;
}
