#include <iostream>
#include <vector>
#include <istream>
#include <fstream>

int main() {
    vector<int> x;
    vector<int> s;
    ifstream inFile(test);
    if(inFile.fail()){
        cerr << "Error opening input file";
        exit(1);
    }
    int xval;
    int sval;
    while(inFile.eof() == false){
        inFile >> xval;
        x.push_back(xval);
        inFile >> sval;
        s.push_back(sval);
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}