#include <bits/stdc++.h>

using namespace std;

string _output(string inputFile, int i)
{
    stringstream ss;
    ss << setw(4) << setfill('0') << i;
    return inputFile + ss.str();
}

pair<string, int> getOutputFile(string inputFile)
{
    fstream file;
    string outputFileName = _output(inputFile, 1);
    file.open(outputFileName);
    int cur;
    for(cur=2; file; cur++) {
        file.close();
        outputFileName = _output(inputFile, cur);
        file.open(outputFileName);
    }
    file.close();
    return {outputFileName, cur-1}; // Couldn't return the file stream directly for some reason
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    ifstream config;
    config.open("project.conf");

    string inputFileName;
    getline(config, inputFileName);

    pair<string, int> outputFilePayload = getOutputFile(inputFileName);
    string outputFileName = outputFilePayload.first;
    int outputFileIndex = outputFilePayload.second;
    ifstream inputFile(inputFileName);
    if(!inputFile) {
        cerr << "Error: No input file found\n";
        exit(1);
    }
    ofstream outputFile(outputFileName);
    _copyFile("main.cpp", outputFileIndex);
    cerr << "Using input file : " << inputFileName << "\n";
    cerr << "Using output file: " << outputFileName << "\n";

    return 0;
}
