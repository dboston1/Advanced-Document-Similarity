#include<Driver.h>
#include<iostream>
using std::cerr;
using std::cout;
using std::endl;
#include<sstream>
using std::stringstream;

int main(int argc, char* argv[])
{
    // check for correct number of arguments 
    if (argc != 5){          
        cerr << "missing / additional file argument " << argc << endl;
        return -1;
    }
    double low_reading;
    double upper_reading;
    int low_reading_int;
    int upper_reading_int;
    
    stringstream sstr0(argv[3]);
    sstr0 >> low_reading;
    if(sstr0.fail()){
        sstr0.clear();
        sstr0 >> low_reading_int;
        if(sstr0.fail()){
            cout << "lower boundary failed: stringstream" << endl;
            return -1;
        }
        low_reading = static_cast<double>(low_reading_int);
    }
    stringstream sstr1(argv[4]);
    sstr1 >> upper_reading;
    if(sstr1.fail()){
        sstr1.clear();
        sstr0 >> upper_reading_int;
        if(sstr0.fail()){
            cout << "upper boundary failed: stringstream" << endl;
            return -1;
        }
        upper_reading = static_cast<double>(upper_reading_int);
    }
    
    if (low_reading > upper_reading){
        cout << "Lower reading level cannot exceed upper reading level" << endl;
        return -1;
    }
    
    Driver temp(low_reading, upper_reading);
    return temp.Driver::start(argv);
}

        
