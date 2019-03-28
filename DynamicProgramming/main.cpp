#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

class ProblemInput
{
    public:
    vector<int> X;
    vector<int> S;

    ProblemInput(vector<int> X, vector<int> S)
    {
        this->X = X;
        this->S = S;
    }
};


ProblemInput loadInput(string path)
{
    ifstream inFile(path);

    if (inFile.fail())
    {
        cerr << "Error opening input file.";
        exit(1);
    }

    int n;
    inFile >> n;

    vector<int> X;
    vector<int> S;
    X.reserve(n);
    S.reserve(n);

    int x;
    int s;
    for (int i = 0; i < n && !inFile.eof(); i++)
    {
        inFile >> x;
        inFile >> s;

        X.push_back(x);
        S.push_back(s);
    }

    inFile.close();

    return ProblemInput(X, S);
}


int main(int argn, char** args)
{
    string inputPath = "input.txt";
    ProblemInput input = loadInput(inputPath);

    return 0;
}