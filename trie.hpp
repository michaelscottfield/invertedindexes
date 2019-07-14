//
// Created by mike on 19-7-9.
//

#ifndef MATERIALONTOLOGY_TRIE_HPP
#define MATERIALONTOLOGY_TRIE_HPP

#include "iostream"
#include "string.h"
using namespace std;

class trieNode{
public:
    //const char* c;
    char c;
    trieNode* getRoot(trieNode* node);
    void insertKey(char const* key);
    int getCount(char* word);
    void printTrie();
    trieNode* queryNode(char* word);
    trieNode();
    trieNode(char const*cha, trieNode *thisParent);
    ~trieNode();
    //~trieNode(char *cha, trieNode *thisParent);

private:
    trieNode *parent;
    trieNode **children;
    int count;
};

trieNode* trieNode::getRoot(trieNode *node) {
    if(node == nullptr){
        cout <<"parenthesis is null pointer"<<endl;
        return nullptr;
    }
    trieNode *temp = node;
    while(temp->parent){
        temp = temp->parent;
    }
    //if(*temp->c == '/'){
    if(temp->c == '/'){
        cout <<"getRoot: root node has wrong char value"<<endl;
        return nullptr;
    }
    return temp;
}

void trieNode::printTrie() {
    cout << "char: "<<c <<endl;
    if(children == nullptr){
        return;
    }
    auto **tempChild = children;
    while (*tempChild != nullptr){
        (*tempChild)->printTrie();
        tempChild ++;
        //*tempChild->printTrie();
    }
//    if(*c != '/'){
//        cout <<"insertKey: must be inserted in root"<<endl;
//        return;
//    }
}

void trieNode::insertKey(char const*key) {
    //if(*c != '/'){
    if(c != '/'){
        cout <<"insertKey: must be inserted in root"<<endl;
        return;
    }
    if(key == nullptr){
        cout << "insertKey: key points to null" <<endl;
        return;
    }
    if(strlen(key) == 1){
        if(!((key[0] >= 'a' && key[0] <= 'z') || (key[0] >= 'A' && key[0] <= 'Z'))){
            cout << "insertKey: key is one wrong char"<<endl;
            return;
        }
        if(children == nullptr){
            auto *thisNode = new trieNode(key, this);
            thisNode->count ++;
            //children = thisNode;
            //*children = thisNode;
            //thisNode->parent = this;
        } else{
//            auto **tempChild = children;
//            //while (tempChild != nullptr){
//            while (*tempChild != nullptr){
//                //if(*((*tempChild)->c) == key[0]){
//                if((*tempChild)->c == key[0]){
//                    (*tempChild)->count ++;
//                    cout <<"insert key: word is already in the tree 0"<<endl;
//                    return;
//                }
//                tempChild++;
//            }
            auto *tempChild = children[(*key)>'a'?*key-'a':*key-'A'];
            //if(tempChild->count > 0){
            if(tempChild != nullptr){
                tempChild->count++;
                return;
            }
            auto *thisNode = new trieNode(key, this);
            thisNode->count ++;
            //*(children + 1) = thisNode;
            //thisNode->parent = this;
        }
    } else if(strlen(key) > 1){
        auto *temp = this;
        int i = 0;
        //int j = 0;
        //while(temp->children){
        while (temp->children != nullptr){
//            auto **tempChild = temp->children;
//            //int j = 0;
//            //cout <<"end of world"<<endl;
//            while(*tempChild != nullptr){
//            //while (**tempChild != NULL){
//            //while (*tempChild != NULL){
//                //cout << "all out of love"<<endl;
//                cout << ((*tempChild)->c)<<"---"<<endl;
//                //if(*tempChild->c == key[i]){
//                if(((*tempChild)->c) == key[i]){
//                    temp = *tempChild;
//                    i+=1;
//                    break;
//                }
//                tempChild ++;
//            }
            if(temp->children[key[i]>'a'?key[i]-'a':key[i]-'A'] != nullptr){
                i+=1;
                temp = temp->children[key[i-1]>'a'?key[i-1]-'a':key[i-1]-'A'];
            } else{
                break;
            }
//            if(*tempChild == nullptr){
//                break;
//            }
//            if(i < strlen(key)){
//                break;
//            }else{
            if(i == strlen(key)){
                cout << i <<endl;
                temp->count++;
                //temp->children[key[i-1]>'a'?key[i-1]-'a':key[i-1]-'A']->count++;
                //temp->children[key[i]>'a'?key[i]-'a':key[i]-'A']->count++;
                //cout << (*tempChild)->c<<endl;
                //(*tempChild)->count ++;
                cout <<"insert key: word is already in the tree"<<endl;
                return;
            }
            //else{
//                temp = *tempChild;
//            }
        }
        while(i < strlen(key)){
            auto *newNode = new trieNode(key+i, temp);
            //cout << key[i]<<endl;
            temp = newNode;
            i ++;
        }
        temp->count ++;
        cout <<"insert key: "<<temp->count<<endl;
    }
}

int trieNode::getCount(char *word) {
    if(c != '/'){
        cout <<"queryNode: must query from root"<<endl;
        return 0;
        //return nullptr;
    }
    if(word == nullptr){
        cout << "queryNode: word is null pointer"<<endl;
        return 0;
        //return nullptr;
    }
    trieNode *temp = this;
    while(true){
        if(temp->children == nullptr){
            cout << "queryNode: word is not in the tree 1" <<endl;
            return 0;
            //return nullptr;
        }
        if(temp->children[*word>'a'?*word-'a':*word-'A'] != nullptr){
            temp = temp->children[*word>'a'?*word-'a':*word-'A'];
            word++;
            //if(!word){
            if(*word == '\0'){
                return temp->count;
            }
        } else{
            cout <<"queryNode: word is not in the tree 2"<<endl;
            return 0;
        }
//        trieNode **tempChild = temp->children;
//        while (tempChild != nullptr){
//            if((*tempChild)->c == *word){
//                cout <<"queryNode "<< (*tempChild)->c<<endl;
//                temp = *tempChild;
//                word++;
//                //cout << int(*word) <<endl;
//                //cout << *word <<endl;
//                //if(word == nullptr){
//                //if((*word) == ""){
//                //if(*word == NULL){
//                //if(*word = ''){
//                if(*word == '\0'){
//                    if(temp->children == nullptr || temp->count > 0){
//                        return temp->count;
//                        //return temp;
//                    } else{
//                        cout <<"queryNode: word is not in the tree 2"<<endl;
//                        return 0;
//                        //return nullptr;
//                    }
//                }
//                break;
//            }
//            tempChild ++;
//        }
        //cout <<"queryNode: word is not in the tree 3"<<endl;
        //return nullptr;
        //word ++;
    }
}

trieNode* trieNode::queryNode(char *word) {
    if(c != '/'){
        cout <<"queryNode: must query from root"<<endl;
        return nullptr;
    }
    if(word == nullptr){
        cout << "queryNode: word is null pointer"<<endl;
        return nullptr;
    }
    trieNode *temp = this;
    while(true){
        if(temp->children == nullptr){
            cout << "queryNode: word is not in the tree 1" <<endl;
            return nullptr;
        }
        if(temp->children[*word>'a'?*word-'a':*word-'A'] != nullptr){
            temp = temp->children[*word>'a'?*word-'a':*word-'A'];
            word++;
            //if(!word){
            if(*word == '\0'){
                return temp;
            }
        } else{
            cout <<"queryNode: word is not in the tree 2"<<endl;
            return nullptr;
        }
        //trieNode **tempChild = temp->children;
//        while (tempChild != nullptr){
//            if((*tempChild)->c == *word){
//                cout <<"queryNode "<< (*tempChild)->c<<endl;
//                temp = *tempChild;
//                word++;
//                //cout << int(*word) <<endl;
//                //cout << *word <<endl;
//                //if(word == nullptr){
//                //if((*word) == ""){
//                //if(*word == NULL){
//                //if(*word = ''){
//                if(*word == '\0'){
//                    if(temp->children == nullptr || temp->count > 0){
//                        return temp;
//                    } else{
//                        cout <<"queryNode: word is not in the tree 2"<<endl;
//                        return nullptr;
//                    }
//                }
//                break;
//            }
//            tempChild ++;
//        }
        //cout <<"queryNode: word is not in the tree 3"<<endl;
        //return nullptr;
        //word ++;
    }
}

trieNode::trieNode() {
    //const char temp = '/';
    //c = &temp;
    //c = &('/');
    //c = nullptr;
    //*c = '/';
    c = '/';
    parent = nullptr;
    children = nullptr;
    count = 0;
}

trieNode::trieNode(char const*cha, trieNode *thisParent) {
    //strcpy(c, cha);
    //c = cha;
    //c = cha[0];
    //strcpy(c, cha[0]);
    //char temp = cha[0];
    //static char temp = cha[0];
    //const char temp = cha[0];
    //cout << cha[0]<<"what the fuck"<<endl;
    //c = &temp;

    //cout << *c <<"the fuck"<< endl;
    count = 0;
    //*c = *cha;
    //c ="x";
    c = cha[0];
    parent = thisParent;
    children = nullptr;
    if(thisParent->children == nullptr){
        thisParent->children = new trieNode*[26];
        thisParent->children[c>'a'?c-'a':c-'A'] = this;
        //**(thisParent->children) = &this;
        //*(thisParent->children) = this;
        //**thisParent->children = &this;
    } else{
        thisParent->children[c>'a'?c-'a':c-'A'] = this;
        //cout << sizeof(thisParent->children) / sizeof(trieNode*)<<endl;
        //trieNode **temp = thisParent->children;
//        int i = 0;
//        while (*(thisParent->children+i) != nullptr){
//            i++;
//            //temp++;
//        }
//        cout << i << endl;
//        //*(thisParent->children+i) = (trieNode*) malloc(sizeof(trieNode*));
//        *(thisParent->children+i) = this;
//        cout <<(*(thisParent->children+i))->c<<endl;
        //*temp = (trieNode*) malloc(sizeof(trieNode));
        //*temp = this;
        //cout << sizeof(thisParent->children) / sizeof(trieNode*)<<endl;
        //cout << (*temp)->c<<endl;
    }
}

trieNode::~trieNode() {
    cout << "trieNode is being deleted"<<endl;
}

class trieTree{

};

#endif //MATERIALONTOLOGY_TRIE_HPP
