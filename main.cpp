#include <bits/stdc++.h>

using namespace std;

string _output(string inputFile, int i)
{
    stringstream ss;
    ss << setw(4) << setfill('0') << i;
    return inputFile + ss.str();
}

string getOutputFile(string inputFile)
{
    fstream file;
    string outputFileName = _output(inputFile, 1);
    file.open(outputFileName);
    for(int cur=2; file; cur++) {
        file.close();
        outputFileName = _output(inputFile, cur);
        file.open(outputFileName);
    }
    file.close();
    return outputFileName; // Couldn't return the file stream directly for some reason
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    ifstream config;
    config.open("project.conf");

    string inputFileName;
    getline(config, inputFileName);

    string outputFileName = getOutputFile(inputFileName);
    ifstream inputFile(inputFileName);
    if(!inputFile) {
        cerr << "Error: No input file found\n";
        exit(1);
    }
    ofstream outputFile(outputFileName);
    cerr << "Using input file : " << inputFileName << "\n";
    cerr << "Using output file: " << outputFileName << "\n";

    return 0;
}
