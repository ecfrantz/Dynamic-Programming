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
    // Allocate space for the score array for n days
	SolutionNode* M = new SolutionNode[input.n];

    // Solve for M[q] (index corrected) for q = 1 to n (complete score array)
	for (int q = 0; q < input.n; q++)
	{
        // Initialize maximum score trackers
		int maxScore = 0;
		int maxIndex = -1;

        // M[q] is the maximum of the scores assuming we reboot on day i
        // or we do not reboot at all. 
		for (int i = 0; i <= q; i++)
		{
            // Get base score, M[i - 1] (index corrected), where M[-1] = M[0] = 0
			int score = (i <= 1) ? 0 : M[i - 2].score;

            // Add up scores of days after reboot
			for (int j = i; j <= q; j++)
			{
				score += min(input.X[j], input.S[j - i]);
			}

            // There is a new maximum score so record where it was found 
			if (score > maxScore)
			{
				maxScore = score;
				maxIndex = i;
			}
		}

        // Set maximum score for first q days where there is a reboot on day i 
		M[q].score = maxScore;
		M[q].parent = maxIndex - 1;
	}

	return M;
}

/// Calculate the traceback of the algorithm (the throughput of each day).
int* calculateTraceback(ProblemInput input, SolutionNode* M)
{
    // Allocate space for the traceback.
	int* throughput = new int[input.n];

    // Initialize two pointers (i = low pointer), (j = high pointer)
	int i;
	int j = input.n;
	SolutionNode node;

    // Walk from end to beginning calculating the throughput.
    // Index j indicates the day we are calculating.
    // Index i indicates the most recent reboot.
    // Initializes to parent of M[n].
	while (j > 0)
	{
        // Set the day before the latest reboot.
		node = M[--j];
		i = node.parent;

        // Set days after and until reboot to throughput.
		for (; j > i; j--)
		{
			throughput[j] = min(input.X[j], input.S[j - i - 1]);
		}

        // Set day of reboot to 0.
		throughput[j] = 0;
	}

	return throughput;
}


/// Entry point to the program
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