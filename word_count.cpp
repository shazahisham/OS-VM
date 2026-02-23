#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include<sstream>
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
    unordered_map<string,int> wordCount;

for (string l : lines) {
    stringstream ss(l);
    string word;
    while (ss >> word) {
        word = cleanWord(word);
        if (word != "") {
            wordCount[word]++;
        }
    }
}

for (auto pair : wordCount) {
    cout << pair.first << " " << pair.second << endl;
}

    return 0;
}