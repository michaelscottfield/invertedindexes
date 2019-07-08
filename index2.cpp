#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <strstream>
#include <unordered_map>
#include <map>
using namespace std;

int convertStringToInt(const string &s)
{
    int val;
    strstream ss;
    ss << s;
    ss >> val;
    return val;
}

bool readfile(string path, string listtxt, map<string, int> &dict) {
    string s;
    ifstream fin(path);
    ifstream lin(listtxt);
    unordered_map<string, vector<int>> postings;
    map<string, int>::iterator postiter;
    int docnum = int(path.at(path.length() - 5)) - 48;
    if (!fin) return false;
    string temp;
    int tempnum;
    int offset = 0;
    int j = 0;
    vector<int>::iterator iter;
    if (!lin) {

    }
    else {
    while (getline(lin, s)) {
            vector<int> intpost;
            j = 0;
            unsigned int i = 0;
            offset = 0;
            while (i < s.length()) {
                for (i = offset; i < s.length(); i++) {
                    if (s.at(i) == ' ' || i == s.length() - 1) {
                        tempnum = convertStringToInt(s.substr(j, i - j));
                        j = i + 1;
                        break;
                    }
                }
                intpost.clear();
                for (i = j; i < s.length(); i++) {
                    if (s.at(i) == ' ') {
                        temp = s.substr(j, i - j);
                        j = i + 1;
                        intpost.push_back(convertStringToInt(temp));
                        if (intpost.size() == tempnum) {
                            break;
                        }
                    }
                }
                for (postiter = dict.begin(); postiter != dict.end(); postiter++) {
                    if (postiter->second == offset) {
                        postings.insert(make_pair(postiter->first, intpost));
                        break;
                    }
                }
                offset = j;
            }
        }
    }
    while (getline(fin, s)) {
        j = 0;
        for (unsigned int i = 0; i < s.length(); i++) {
            if (s.at(i) == ' ' || s.at(i) == ',') {
                temp = s.substr(j, i - j);
                j = i + 1;
                if (postings.find(temp) != postings.end()) {
                    vector<int> newdoc = postings[temp];
                    iter = find(newdoc.begin(), newdoc.end(), docnum);
                    if (iter != newdoc.end()) {
                        newdoc.push_back(docnum);
                        postings[temp] = newdoc;
                    }
                }
                else {
                    dict.insert(make_pair(temp, offset));
                    vector<int> newdoc = { docnum };
                    postings.insert(make_pair(temp, newdoc));
                    }
                continue;
            }
        }
        temp = s.substr(j, s.length() - j);
        if (postings.find(temp) != postings.end()) {
            vector<int> newdoc = postings[temp];
            iter = find(newdoc.begin(), newdoc.end(), docnum);
            if (iter != newdoc.end()) {
                newdoc.push_back(docnum);
                postings[temp] = newdoc;
            }
        }
        else {
            dict.insert(make_pair(temp, offset));
            vector<int> newdoc = { docnum };
            postings.insert(make_pair(temp, newdoc));
        }
    }
    vector<string> sorteddict;
    for (postiter = dict.begin(); postiter != dict.end(); postiter++) {
        sorteddict.push_back(postiter->first);
    }
    sort(sorteddict.begin(), sorteddict.end());
    dict.clear();
    vector<string>::iterator striter;
    fin.close();
    fin.clear();
    lin.close();
    lin.clear();
    ofstream out(listtxt, ios::out);
    int newoffset = 0;
    for (striter = sorteddict.begin(); striter != sorteddict.end(); striter++) {
        vector<int> docnums = postings[*striter];
        dict.insert(make_pair(*striter, newoffset));
        out << docnums.size() << " ";
        newoffset++;
        for (iter = docnums.begin(); iter != docnums.end(); iter++) {
            out << *iter << " ";
            newoffset++;
            newoffset++;
        }
        newoffset++;
    }
    out.close();
    return true;
}
int main()
{
    string file1 = "E:\\kdelab\\1.txt";
    string file2 = "E:\\kdelab\\2.txt";
    string file3 = "E:\\kdelab\\3.txt";
    string file4 = "E:\\kdelab\\4.txt";
    map<string, int> dict;
    string listtxt = "E:\\kdelab\\list.txt";
    remove(listtxt.c_str());
    map<string, int>::iterator iter;
    if (!readfile(file1, listtxt, dict)) {
        cout << "1.txt does not exist" << endl;
    }
    if (!readfile(file2, listtxt, dict)) {
        cout << "2.txt does not exist" << endl;
    }
    if (!readfile(file3, listtxt, dict)) {
        cout << "3.txt does not exist" << endl;
    }
    if (!readfile(file4, listtxt, dict)) {
        cout << "4.txt does not exist" << endl;
    }
    ofstream out2("E:\\kdelab\\dict.txt", ios::out);
    for (iter = dict.begin(); iter != dict.end(); iter++) {
        out2 << iter->first << " " << iter->second << endl;
    }
    out2.close();
    //system("pause");
}