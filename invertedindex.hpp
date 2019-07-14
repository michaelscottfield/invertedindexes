//
// Created by mike on 19-7-9.
//

#ifndef MATERIALONTOLOGY_INVERTEDINDEX_HPP
#define MATERIALONTOLOGY_INVERTEDINDEX_HPP
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <set>
using namespace std;

template <class TKey>
class InvIndex : public map<TKey, list<int>>{
public:
    vector<vector<TKey>> docs;//文档正排表

public:
    void add(vector<TKey>& doc){
        docs.push_back(doc);
        int curDocID = docs.size();
        //for(auto w : doc){
        for(int w = 0; w < doc.size(); w++){
            typename map<TKey, list<int>>::iterator it;
            it = this->find(doc[w]);

            if(it == this->end()){
                list<int> newList;
                (*this)[doc[w]] = newList;
                it = this->find(doc[w]);
            }
            it->second.push_back(curDocID);

            //map<typename TKey, list<int>>::iterator iterator1;
            //std::map<TKey, list<int>>::iterator it;
            //std::map<char, int>::iterator it;
            //map<TKey, list<int>>::iterator;
            //it = this->find(doc[w]);
        }
    }

    void retrieve(vector<TKey>& query, set<int>& docIDs){
        int termNum = query.size();

        //合并所有term的倒排链
        docIDs.clear();
        for(int t = 0; t < termNum; t++){
            typename map<TKey, list<int>>::iterator it;
            if((it = this->find(query[t])) != this->end()){
                docIDs.insert(it->second.begin(), it->second.end());
            }
        }
    }
};

#endif //MATERIALONTOLOGY_INVERTEDINDEX_HPP
