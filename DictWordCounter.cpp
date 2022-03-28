#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Simply opens the plaintext word-list dictionary and tallies the number of words vs. word length
// Used to gather stats on various candidate dictionaries for the New Sator Square project

int main(int argc, char** argv)
{
  char filename[]="la-novs-nodups.txt";  //Comment out to use a filename supplied on the command line
  argv[1]=filename;

  if (argv[1]) {
    cout<<"Opening dictionary...";
  } else {
    fprintf(stderr,"correct syntax is:\n");
    fprintf(stderr,"WordCounter textfile.txt\n");
    exit(1);
  }

    ifstream dictionary;
    dictionary.open(argv[1],ifstream::in);
    if (!dictionary.is_open()) {
        cerr<<"Error opening dictionary file!"<<endl;
        exit(-1);
    }
    cout<<" success."<<endl;

    vector<unsigned int> stats(32,0);
    string load_a_word;
    unsigned int counter=0;
    unsigned int wordlength=0;
    vector<string> interesting;
    vector<vector<string> > AllWordsByLength;
    AllWordsByLength.reserve(32);


    while (!dictionary.eof()) {
        getline(dictionary,load_a_word);
        counter++;
        if (counter%100000==0) cout<<"Processed "<<counter<<endl;
        wordlength=load_a_word.length();
        //if (wordlength==2) interesting.push_back(load_a_word);
        //if (wordlength>30) stats[31]++; else stats[wordlength]++;
        if (wordlength>30) {
            stats[31]++;
            AllWordsByLength[31].push_back(load_a_word);
        }
        else {
            stats[wordlength]++;
            AllWordsByLength[wordlength].push_back(load_a_word);
        }
    }

    cout<<"Analysis completed.  Total words processed="<<counter<<endl;
    dictionary.close();

    ofstream res;
    res.open("results-lat-noVs.txt",ofstream::out);
    if (!res.is_open()) {cerr<<"Can't open results file for writing"<<endl; exit(-1);}
    res<<"Analysis completed.  Total words processed="<<counter<<endl;

    for (unsigned int i=1;i<stats.size();i++) {
        cout<<"Word size: "<<i<<" Words: "<<stats[i]<<endl;
        res<<"Word size: "<<i<<" Words: "<<stats[i]<<endl;
    }

    unsigned int selector=1;
    do {
        cin>>selector;
         cout<<"Words of size "<<selector<<" are: "<<endl;
         for (unsigned int i=0;i<AllWordsByLength[selector].size();i++) {
            cout<<AllWordsByLength[selector].at(i)<<" ";
        }
        cout<<endl;
    } while (selector!=0);

    res.close();

return 0;
}
