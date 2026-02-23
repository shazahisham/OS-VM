#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include<sstream>
#include <thread>
using namespace std;

string cleanWord(string word) {
    string result = "";
    for (int i = 0; i < word.size(); i++) {
        if (isalpha(word[i])) {
            result += tolower(word[i]);
        }
    }
    return result;
}

void countWordsInSegment(vector<string>& lines, int start, int end, unordered_map<string,int>& localMap) {
    for (int i = start; i < end; i++) {
        stringstream ss(lines[i]);
        string word;
        while (ss >> word) {
            word = cleanWord(word);
            if (word != "") {
                localMap[word]++;
            }
        }
    }
}

int main() {
    ifstream file("input.txt");
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    for (string l : lines) {
        cout << l << endl;
    }
int numThreads = 4;
if (numThreads > lines.size()) numThreads = lines.size();

vector<thread> threads;
vector<unordered_map<string,int>> threadMaps(numThreads);

int totalLines = lines.size();
int segmentSize = totalLines / numThreads;
int start = 0;

for (int i = 0; i < numThreads; i++) {
    int end = (i == numThreads - 1) ? totalLines : start + segmentSize;
    threads.push_back(thread(countWordsInSegment, ref(lines), start, end, ref(threadMaps[i])));
    start = end;
}

for (int i = 0; i < threads.size(); i++) threads[i].join();

unordered_map<string,int> finalMap;

for (int i = 0; i < numThreads; i++) {
    for (auto pair : threadMaps[i]) {
        finalMap[pair.first] += pair.second;
    }
}

for (auto pair : finalMap) {
    cout << pair.first << " " << pair.second << endl;
}
    return 0;
}