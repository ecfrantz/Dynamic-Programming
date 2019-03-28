#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

/// A specific instance of the algorithmic problem.
class ProblemInput
{
    public:
    int n;
    vector<int> X;
    vector<int> S;

    ProblemInput(int n, vector<int> X, vector<int> S)
    {
        this->n = n;
        this->X = X;
        this->S = S;
    }
};

/// A node in the dynamic programming array.
struct SolutionNode
{
    public: 
    int score;
    int parent;

    SolutionNode(int score, int parent)
    {
        this->score = score;
        this->parent = parent;
    }
};


/// Loads an input from a file.
ProblemInput loadInput(string path)
{
    ifstream inFile(path);

    // Check that file exists.
    if (inFile.fail())
    {
        cerr << "Error opening input file.";
        exit(1);
    }

    // Get expected number of days.
    int n;
    inFile >> n;

    // Initialize lists to store inputs and capacities.
    vector<int> X;
    vector<int> S;
    X.reserve(n);
    S.reserve(n);

    // Get all days' data input and capacity.
    int x;
    int s;
    for (int i = 0; i < n && !inFile.eof(); i++)
    {
        // Add x and s values to corresponding lists.
        inFile >> x;
        inFile >> s;
        X.push_back(x);
        S.push_back(s);
    }

    // Close and return problem instance.
    inFile.close();
    return ProblemInput(n, X, S);
}

/// TODO: Calculate Sigma via dynamic programming.
int** calculateSigma(ProblemInput input)
{

}

/// TODO: Calculuate M (score array) via dynamic programming. 
SolutionNode* calculateScores(ProblemInput input, int** sigma)
{

}


int main(int argn, char** args)
{
    // Get input from file.
    string inputPath = "input.txt";
    ProblemInput input = loadInput(inputPath);

    // Calculate solutions
    int** sigma = calculateSigma(input);
    SolutionNode* M = calculateScores(input, sigma);

    // Success!
    return 0;
}