#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>

// Code for eliminating .aff file rules which use V's for U's.
// 
// Because the Hunspell la.aff is arranged such that most of the rules which use Vs for Us come immediately following the same morphology rule written using Us for Us,
// All I did was compare one line of the .aff file to the next.  If the next differed only by using Vs for Us, that line was not copied to our new .aff file.
// This does not eliminate all rules that use a V for a U simply because some rules aren't detected (because the character sequence in the last column sometimes throws the comparison off) 
// But the rest can be eliminated by hand, which I did in the resultant la-novs.aff file after this program generated it.

bool DiffByVs(string a, string b) {
    if (a.length()!=b.length()) return false;
    string c;
    for (string::iterator ait=a.begin();ait!=a.end();ait++) {
        if (*ait=='u') c.push_back('v'); else c.push_back(*ait);
    }
    cout<<"Turning " <<a<< "into "<<c<<" and comparing with "<<b<<endl;
    if (b.compare(c)==0) return true;
return false;
}

using namespace std;

int main()
{
    //Convert affix rule file to eliminate rules involving using Vs for Us.
    ifstream affin;
    affin.open("la.aff",ifstream::in);
    if (!affin.is_open()) {
        cerr<<"Error opening la.aff file!"<<endl;
        exit(-1);
    }
    cout<<"la.aff opened for reading."<<endl;

    ofstream affout;
    affout.open("la-novs.aff",ofstream::out);
    if (!affout.is_open()) {
        cerr<<"Error opening la-novs.aff file for writing."<<endl;
        exit(-1);
    }
    cout<<"la-novs.aff opened for writing."<<endl;

    string line1,line2;
    while(!affin.eof()) {
        line1=line2;
        getline(affin,line2);
        if (!DiffByVs(line1,line2)) affout<<line2<<endl;
    }

    affin.close();
    affout.close();

return 0;
}
