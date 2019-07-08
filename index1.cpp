#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

bool readfile(string path, vector<string> &dict, unordered_map<string, vector<string>> &postings) {
    string s;
    ifstream fin(path);
    vector<string>::iterator iter;
    vector<string>::iterator intiter;
    if (!fin) return false;
    int j = 0;
    string temp;
    vector<int> tempost;
    while (getline(fin, s)) {
        for (unsigned int i = 0; i < s.length(); i++) {
            if (s.at(i) == ' ' || s.at(i) == ',') {
                temp = s.substr(j, i - j);
                iter = find(dict.begin(), dict.end(), temp);
                if (iter == dict.end()) {
                    dict.push_back(temp);
                }
                if (postings.find(temp) == postings.end()) {
                    vector<string> newpost;
                    newpost.push_back(path.substr(path.length() - 5, 5));
                    postings.insert(make_pair(temp, newpost));
                }
                else {
                    vector<string> realpost = postings[temp];
                    intiter = find(realpost.begin(), realpost.end(), path.substr(path.length() - 5, 5));
                    if (intiter == realpost.end()) {
                        postings[temp].push_back(path.substr(path.length() - 5, 5));
                    }
                }
                j = i + 1;
                continue;
            }
        }
        temp = s.substr(j, s.length() - j);
        iter = find(dict.begin(), dict.end(), temp);
        if (iter == dict.end()) {
            dict.push_back(temp);
        }
        if (postings.find(temp) == postings.end()) {
            vector<string> newpost;
            newpost.push_back(path.substr(path.length() - 5, 5));
            postings.insert(make_pair(temp, newpost));
        }
        else {
            vector<string> realpost = postings[temp];
            intiter = find(realpost.begin(), realpost.end(), path.substr(path.length() - 5, 5));
            if (intiter == realpost.end()) {
                postings[temp].push_back(path.substr(path.length() - 5, 5));
            }
        }
    }
    fin.close();
    fin.clear();
    return true;
}

int main()
{
    vector<string> dict;
    string file1 = "E:\\kdelab\\1.txt";
    string file2 = "E:\\kdelab\\2.txt";
    string file3 = "E:\\kdelab\\3.txt";
    string file4 = "E:\\kdelab\\4.txt";
    unordered_map<string, vector<string>> postings;
    if (!readfile(file1, dict, postings)) {
        cout << "1.txt does not exist" << endl;
    }
    if (!readfile(file2, dict, postings)) {
        cout << "2.txt does not exist" << endl;
    }
    if (!readfile(file3, dict, postings)) {
        cout << "3.txt does not exist" << endl;
    }
    if (!readfile(file4, dict, postings)) {
        cout << "4.txt does not exist" << endl;
    }
    ofstream ouF;
    ouF.open("E:\\kdelab\\inverted.txt", std::ofstream::binary);
    vector<string>::iterator iter;
    vector<string>::iterator intiter;
    sort(dict.begin(), dict.end());
    for (iter = dict.begin(); iter != dict.end(); iter++) {
        ouF.write((*iter).c_str(), (*iter).length());
        ouF.write(" ", 1);
        vector<string> realpost = postings[*iter];
        for (intiter = realpost.begin(); intiter != realpost.end(); intiter++) {
            ouF.write((*intiter).c_str(), (*intiter).length());
            ouF.write(" ", 1);
        }
        ouF.write("\n", 1);
    }
    ouF.close();
    //system("pause");
}