#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main()
//This routine simply eliminates duplicates from our (unmunched) Latin dictionary by building a <set> of words to swiftly check for novelty.
  
{
    ifstream dictIn;
    dictIn.open("latinwords-noVs.txt",ifstream::in);
    if (!dictIn.is_open()) {
        cerr<<"Error opening latinwords-noVs.txt file!"<<endl;
        exit(-1);
    }
    cout<<"la.aff opened for reading."<<endl;

    ofstream dictOut;
    dictOut.open("la-novs-nodups.txt",ofstream::out);
    if (!dictOut.is_open()) {
        cerr<<"Error opening la-novs-nodups.txt file for writing."<<endl;
        exit(-1);
    }
    cout<<"la-novs-nodups.txt opened for writing."<<endl;

    set<string> vocab;
    string load_a_word;
    pair <set<string>::iterator,bool> ret;

    while (!dictIn.eof()) {
        getline(dictIn,load_a_word);
        ret=vocab.insert(load_a_word);
        if (ret.second) dictOut<<load_a_word<<endl;  //second element of the return value pair == true if insertion added a new item, false if item already in set.
    }

    dictIn.close();
    dictOut.close();

return 0;
}
