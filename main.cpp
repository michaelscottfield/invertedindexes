#include <iostream>
#include <cstring>
#include "tinyxml2.h"
#include <fstream>
#include <vector>
#include "trie.hpp"
#include "invertedindex.hpp"
//#include <direct.h>
using namespace std;
using namespace tinyxml2;
void readXml()
{

    const char* filepath = "../sic-ceramic-coating-calc.xml";
    //ifstream fin("/home/mike/install.sh");
    //ifstream fin("/home/mike/CLionProjects/materialontology/sic-ceramic-coating-calc.xml");
    //ifstream fin("./sic-ceramic-coating-calc.xml");
    //ifstream fin(".\\materialontology\\sic-ceramic-coating-calc.xml");
    ifstream fin("../sic-ceramic-coating-calc.xml");
    if(!fin){
        printf("error");
    }
    //ifstream  afile;
    //afile.open("file.dat", ios::out | ios::in );
    //string filepath = "sic-ceramic-coating-calc.xml";
    //char* filepath="F:\\readXml.xml";
    XMLDocument doc;
    doc.LoadFile(filepath);
    doc.Print();
}

void example1()
{
    static const char* testXML =
            "<?xml version=\"1.0\"?>"
            "<Hello>World</Hello>";
    XMLDocument doc;
    doc.Parse(testXML); // 通过字符串导入xml
    const char* content= doc.FirstChildElement( "Hello" )->GetText();
    printf( "Hello,%s", content );
}


class keyValue{
    string key;
    string value;
};

class dynamicData{
    int dataLength;
    keyValue* tuples;
    //keyValue** tuples;
};
int main(int argc,char* argv[]) {
    // 关键字集合
    char keys[][9] = {"the", "a", "there", "answer", "any", "by", "bye", "their", "the"};
    auto *root = new trieNode();
    for(auto key : keys){
        cout << key<<", "<<strlen(key)<<endl;
        root->insertKey(key);
        root->printTrie();
    }
    // 检索字符串
    char s[][32] = {"Present in trie", "Not present in trie"};
    //char *word = "the";
    //const char*word = "the";
    //char word[3] = 'the';
    //char *word = "the";
    //char word[3] = "the";
    //char word[] = "the";
    //char word[3] = "the";
    //cout << word[3]<<endl;
    //cout << word[4]<<endl;
    char word[] {"the"};
    cout << root->queryNode(word)<<endl;
    cout << root->getCount(word)<<endl;
    //char word2[] {"there"};
    //cout << root->queryNode(word2)<<endl;
    //cout << root->getCount(word2)<<endl;
    //printf("%s --- %s\n", "the", root->queryNode(word)>0?s[0]:s[1]);
    //printf("%s --- %s\n", "the", root->queryNode("the")>0?s[0]:s[1]);
    //chdir(dirname(argv[0]));
    //readXml();
    //example1();
    std::cout << "Hello, World!" << std::endl;

    string D1_tmp[] = {"谷歌", "地图","之父","跳槽","Facebook"};
    int D1_tmp_size = sizeof(D1_tmp)/ sizeof(string);
    vector<string> D1(D1_tmp, D1_tmp+D1_tmp_size);
    string D2_tmp[] = {"谷歌", "地图", "之父", "加盟", "Facebook"};
    int D2_tmp_size = sizeof(D2_tmp)/ sizeof(string);
    vector<string> D2(D2_tmp, D2_tmp+D2_tmp_size);

    string D3_tmp[] = {"谷歌", "地图", "创始人", "拉斯", "离开", "谷歌", "加盟", "Facebook"};
    int D3_tmp_size = sizeof(D3_tmp) / sizeof(string);
    vector<string> D3(D3_tmp, D3_tmp+D3_tmp_size);

    string D4_tmp[] = {"谷歌", "地图", "创始人", "跳槽", "Facebook", "与", "Wave","项目","取消", "有关"};
    int D4_tmp_size = sizeof(D4_tmp) / sizeof(string);
    vector<string> D4(D4_tmp, D4_tmp+D4_tmp_size);

    string D5_tmp[] = {"谷歌", "地图", "创始人", "拉斯", "加盟", "社交", "网站", "Facebook"};
    int D5_tmp_size = sizeof(D5_tmp) / sizeof(string);
    vector<string> D5(D5_tmp, D5_tmp+D5_tmp_size);

    auto* inverted_index = new InvIndex<string>;
    inverted_index->add(D1);
    inverted_index->add(D2);
    inverted_index->add(D3);
    inverted_index->add(D4);
    inverted_index->add(D5);

    string str_query[] = {"谷歌","地图","之父","跳槽","Facebook","创始人","加盟","拉斯","离开","与","Wave","项目","取消","有关","社交","网站"};

    for(int i = 0; i < sizeof(str_query)/ sizeof(string);i++){
        vector<string> query;
        query.push_back(str_query[i]);
        cout << str_query[i]<<" ";
        set<int> docSet;
        inverted_index->retrieve(query, docSet);
        set<int>::iterator it;
        for(it = docSet.begin(); it != docSet.end(); it++){
            cout << "D"<<*it<<" ";
        }
        cout << endl;
    }
    return 0;
}