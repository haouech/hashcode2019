#include <bits/stdc++.h>

using namespace std;

string _output(string inputFile, int i)
{
    stringstream ss;
    ss << setw(4) << setfill('0') << i;
    return inputFile + ss.str();
}

void _copyFile(string name, int version)
{
    string fileType = name.substr(name.rfind('.') + 1);
    ifstream in(name, ios::binary);
    name.erase(name.rfind('.'));
    string newName = _output(name, version) + "." + fileType;
    ofstream out(newName);
    out << in.rdbuf();
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

void _init(ifstream &inputFile, ofstream &outputFile)
{
    srand(time(NULL));

    ifstream config;
    config.open("project.conf");

    string inputFileName;
    getline(config, inputFileName);

    pair<string, int> outputFilePayload = getOutputFile(inputFileName);
    string outputFileName = outputFilePayload.first;
    int outputFileIndex = outputFilePayload.second;
    inputFile.open(inputFileName);
    if(!inputFile) {
        cerr << "Error: No input file found\n";
        exit(1);
    }
    outputFile.open(outputFileName);
    _copyFile("main.cpp", outputFileIndex);
    cerr << "Using input file : " << inputFileName << "\n";
    cerr << "Using output file: " << outputFileName << "\n";
}

int main(int argc, char **argv)
{
    ifstream in;
    ofstream out;
    _init(in, out);
    return 0;
}
