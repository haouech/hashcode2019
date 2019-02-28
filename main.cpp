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

int N;

int readInt(ifstream &in)
{
    string s;
    getline(in, s);
    stringstream ss(s);
    int n;
    ss >> n;
    return n;
}

struct Photo {
    char orientation;
    int id;
    int m;
    set<string> tags;
    void read(ifstream &in) {
        string _s;
        getline(in, _s);
        stringstream ss(_s);
        ss >> orientation >> m;
        cerr << orientation << " " << m << " ";
        for(int i=0; i<m; i++) {
            string x;
            ss >> x;
            cerr << x << " ";
            tags.insert(x);
        }
        cerr << endl;
    }

    bool h() { return orientation == 'H'; }
};

void submit(ofstream &out, vector<Photo> slides, int s)
{
    out << s << "\n";
    for(int i=0; i<slides.size(); i++) {
        Photo photo = slides[i];
        if (photo.h()) {
            out << photo.id << "\n";
        } else {
            out << photo.id << " ";
            i++;
            photo = slides[i];
            out << photo.id << "\n";
        }
    }
}

int main(int argc, char **argv)
{
    ifstream in;
    ofstream out;
    _init(in, out);

    N = readInt(in);
    cerr << N << endl;
    vector<Photo> photos(N);
    vector<int> hs, vs;
    for(int i=0; i<N; i++) {
        photos[i].read(in);
        photos[i].id = i; /// IMPORTANT
        if (photos[i].h()) {
            hs.push_back(i);
        } else {
            vs.push_back(i);
        }
    }
    vector<Photo> slides;
    int s = 0;
    for(int i=0; vs.size() >= 2, i<vs.size(); i+=2) {
        int id = vs[i];
        int id2  = vs[i+1];
        slides.push_back(photos[id]);
        slides.push_back(photos[id2]);
        s ++;
    }
    for(int i=0; i<hs.size(); i++) {
        int id = hs[i];
        slides.push_back(photos[id]);
        s++;
    }
    submit(out, slides, s);
    return 0;
}
