#include <algorithm>
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

    SolutionNode()
    {
        this->score = 0;
        this->parent = -1;
    }

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

/// Saves an output to a file.
void saveOutput(string path, int outputSize, int* outputThroughput, int outputSum)
{
    ofstream outFile(path);

    // Write sum of throughputs.
    outFile << outputSum << endl;

    // Write the throughput of each day.
    for (int i = 0; i < outputSize; i++)
    {
        outFile << outputThroughput[i] << ' ';
    }

    // Flush and close file.
    outFile.flush();
    outFile.close();
}

/// TODO: Calculate Sigma via dynamic programming.
int** calculateSigma(ProblemInput input)
{
    return nullptr;
}

/// Calculuate M (score array) via dynamic programming. 
SolutionNode* calculateScores(ProblemInput input, int** sigma)
{
	SolutionNode* M = new SolutionNode[input.n];

	for (int q = 0; q < input.n; q++)
	{
		int maxScore = 0;
		int maxIndex = -1;
		for (int i = 0; i <= q; i++)
		{
			int score = (i <= 1) ? 0 : M[i - 2].score;
			for (int j = i; j <= q; j++)
			{
				score += min(input.X[j], input.S[j - i]);
			}

			if (score > maxScore)
			{
				maxScore = score;
				maxIndex = i;
			}
		}

		M[q].score = maxScore;
		M[q].parent = maxIndex - 1;
	}
	return M;
}

int* calculateTraceback(ProblemInput input, SolutionNode* M)
{
	int* throughput = new int[input.n];

	int i;
	int j = input.n;
	SolutionNode node;
	while (j > 0)
	{
		node = M[--j];
		i = node.parent;
		for (; j > i; j--)
		{
			throughput[j] = min(input.X[j], input.S[j - i - 1]);
		}
		throughput[j] = 0;
	}

	return throughput;
}


int main(int argn, char** args)
{
	// Get input from file.
	string inputPath = "input.txt";
	ProblemInput input = loadInput(inputPath);

	// Calculate solutions
	int** sigma = calculateSigma(input);
	SolutionNode* M = calculateScores(input, sigma);

	// Calculate and save traceback
	string outputPath = "output.txt";
	int* output = calculateTraceback(input, M);
	saveOutput(outputPath, input.n, output, M[input.n - 1].score);

	// Success!
	return 0;
}