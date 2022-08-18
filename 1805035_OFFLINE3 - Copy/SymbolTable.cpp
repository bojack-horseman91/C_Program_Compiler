#include "ScopeTable.h"
#include <bits/stdc++.h>
#include "SymbolInfo.h"
#include "SymbolTable.h"
using namespace std;


void SymbolTable::EnterScope(){
    if(compilerTable.empty()){
        compilerTable.push(new ScopeTable(numberOfBuckets,to_string(baseScopeID++)));
        cout<<"New ScopeTable with id "<<compilerTable.top()->getID()<<" created"<<endl;
        return;
    }
    string  nextID=compilerTable.top()->getNextScopeID();
    ScopeTable* newTable=new ScopeTable(numberOfBuckets,nextID);
    newTable->setParentScopeTable(compilerTable.top());
    compilerTable.push(newTable);
    cout<<"New ScopeTable with id "<<compilerTable.top()->getID()<<" created"<<endl;
    }
string SymbolTable::getCurrentScopeID(){
    return compilerTable.top()->getID();
}
SymbolInfo* SymbolTable::LookUp(string Name){
    if(compilerTable.empty()){
      return NULL;
    }
    ScopeTable* current=compilerTable.top();
    do{
            SymbolInfo* symbol=current->LookUp(Name);
        if(symbol!=NULL)
        {
            return symbol;
        }
        current=current->getParentScopeTable();
    }while(current!=NULL);
    return NULL;
}
void SymbolTable::ExitScope(){
    if(compilerTable.empty()){
        cout<<"No more scopes Found!!!!"<<endl;
        return;
    }
    ScopeTable* scope=compilerTable.top();
    cout<<"ScopeTable with id "<<scope->getID()<<" removed"<<endl;
    delete scope;
    compilerTable.pop();
}

SymbolTable::SymbolTable(int numberOfBuckets)
{
    this->numberOfBuckets=numberOfBuckets;
    baseScopeID=1;
}

SymbolTable::~SymbolTable()
{
    while(!compilerTable.empty()){
        this->ExitScope();
    }
}

