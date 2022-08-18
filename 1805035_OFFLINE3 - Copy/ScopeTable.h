#ifndef SCOPETABLE_H_INCLUDED
#define SCOPETABLE_H_INCLUDED


#include <bits/stdc++.h>
#include "SymbolInfo.h"
using namespace std;
class ScopeTable
{
private:
    int nextScopeID=1;
    string ScopeID;
    SymbolInfo** hashTable;
    int numberOfBucket;
    ScopeTable*parentScopeTable;
    

public:

    ScopeTable(int bucketNumber ,string ScopeID);
    ~ScopeTable();
    int hashf(string Name);
    void printInsertSuccess(int row,int col){cout<<"Inserted in ScopeTable# "<<ScopeID<<" at position "<<row<<", "<<col<<endl;}
    bool Insert(SymbolInfo* symbol);
    void LexPrint(ofstream &logWritter);
    SymbolInfo* LookUp(string Name);
    void Print();
    bool Delete(string Name);

    //getter FOR NEXT SCOPE ID
    string getNextScopeID(){return this->ScopeID+"."+to_string(nextScopeID++);}
    //GETTER AND SETTER FOR PARENT SCOPE TABLE
    void setParentScopeTable(ScopeTable* parent){
        parentScopeTable=parent;
    }
    ScopeTable* getParentScopeTable(){return parentScopeTable;}
    string getID(){
        return this->ScopeID;
    }
};


static unsigned long
 sdbm(unsigned char *str);
#endif // SCOPETABLE_H_INCLUDED
