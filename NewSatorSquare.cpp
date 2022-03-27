#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Tool for finding new Sator Squares                   //
// By Eric J. Jenislawski
// https://github.com/ProfJski/NewSatorSquare           //

unsigned int WordSize = 5;
//TODO: Generalize to larger squares than 5x5

void PrintWordArray(const vector<string> &a) {
    for (unsigned int i=0;i<a.size();i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
return;
}

struct SatorSquare {
    string Row0;
    string Row1;
    string Row2;
};

string ReverseString(string a) {
    string r(a.rbegin(),a.rend());
return r;
}

bool isPalindrome(string a) {
    if (a.compare(ReverseString(a))==0) return true;
return false;
}

void PrintSatorSquare(SatorSquare s) {
    cout<<endl;
    cout<<"\t"<<s.Row0<<endl;
    cout<<"\t"<<s.Row1<<endl;
    cout<<"\t"<<s.Row2<<endl;
    cout<<"\t"<<ReverseString(s.Row1)<<endl;
    cout<<"\t"<<ReverseString(s.Row0)<<"\n"<<endl;
return;
}

int main()
{
    cout<<"Opening dictionary...";

    ifstream dictionary;
    dictionary.open("la-novs-nodups.txt",ifstream::in);
    if (!dictionary.is_open()) {
        cerr<<"Error opening dictionary file!"<<endl;
        exit(-1);
    }
    cout<<" success."<<endl;

    vector<string> Words;
    string load_a_word;

    //Load all our words from the dictionary into memory
    while (!dictionary.eof()) {
        getline(dictionary,load_a_word);
        if (load_a_word.length()==WordSize) Words.push_back(load_a_word);
    }
    dictionary.close();
    cout<<"Size of words vector="<<Words.size()<<endl;

    //Discover all the palindromic words
    vector<string> Palindromes;
    for (unsigned int i=0;i<Words.size();i++) {
        if (isPalindrome(Words[i])) Palindromes.push_back(Words[i]);
    }

    cout<<"Size of Palindromes array="<<Palindromes.size()<<endl;
    PrintWordArray(Palindromes);

    unsigned int progressCounter=0;
    unsigned int wsize=Words.size();
    cout<<"Pairs processed="<<flush;
    //Discover all pairs of words in the dictionary where one is the reverse of the other
    vector<string> Pairs;
    for (unsigned int i=0;i<Words.size();i++) {
        progressCounter++;
        if (progressCounter%100==0) cout<<progressCounter<<"("<<(progressCounter*100)/wsize<<"%) "<<std::flush;
        for (unsigned int j=0;j<Words.size();j++) {
            if (Words[i].compare(ReverseString(Words[j]))==0) {
                    Pairs.push_back(Words[i]);
                    break;
            }
        }
    }

    cout<<"\nSize of Pairs array="<<Pairs.size()<<endl;
    PrintWordArray(Pairs);

    //Now we can find a square!
    string Row0,Row1,Row2;
    unsigned int results_counter=0;
    SatorSquare s;
    vector<SatorSquare> results;
    for (unsigned int i=0;i<Pairs.size();i++) {  //For a word with a reverse in the dictionary
        Row0=Pairs[i];
        for (unsigned int j=0;j<Pairs.size();j++) {  //Find any word that works by searching words vector, OR search Pairs vector to make it harder (since the one pair is not an arbitrary word like "Arepo").  See Github for more explanation.
            if ( (Row0.at(1)==Pairs[j].at(0)) && (Row0.at(3)==Pairs[j].at(4)) ) {  // Such that the second letter of Row0 word is first letter of Row1 word, and fourth letter of Row0 word is last letter of Row1 word
                Row1=Pairs[j];
                for (unsigned int k=0;k<Palindromes.size();k++) {  //If we have found that, then find the third word that completes the square
                    if ( (Row0.at(2)==Palindromes[k].at(0)) && (Row1.at(2)==Palindromes[k].at(1)) ) {  //If these conditions are met, all the other reflection conditions are satisfied because of the nature of the palindrome and palindromic pairs
                        Row2=Palindromes[k];
                        s = (SatorSquare){Row0,Row1,Row2};
                        results_counter++;
                        results.push_back(s);
                        PrintSatorSquare(s);
                    }
                }
            }
        }
        cout<<i<<" "<<std::flush;
    }
    cout<<"Total squares found: "<<results_counter<<endl;
    ofstream outputFile;
    outputFile.open("results-latin-pairs.txt");  // So named because the dictionary language is Latin and we insist that all palindromic pairs are in the dictionary
    if (!outputFile.is_open()) {
        cerr<<"Error opening file to store results"<<endl;
        exit(-1);
    }
    for (unsigned int i=0;i<results.size();i++) {
        outputFile<<"\n#"<<i<<endl;
        outputFile<<results[i].Row0<<endl;
        outputFile<<results[i].Row1<<endl;
        outputFile<<results[i].Row2<<endl;
        outputFile<<ReverseString(results[i].Row1)<<endl;
        outputFile<<ReverseString(results[i].Row0)<<endl;
    }
    outputFile.close();


return 0;
}
