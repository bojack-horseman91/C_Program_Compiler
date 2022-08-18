#include <bits/stdc++.h>
#include "SymbolInfo.h"
using namespace std;

SymbolInfo::SymbolInfo()
{
    this->Next = nullptr;
    sizeOfArray = "";
    typeOfID = "";
    typeOfVar = "";
    isFunction = false;
    isFunctionDefined = false;
    isFunctionDeclared = false;
    returnTypeOfFunction = "";
}
SymbolInfo::SymbolInfo(string Name, string Type)
{
    this->Name = Name;
    this->Type = Type;
    sizeOfArray = "";
    typeOfID = "";
    typeOfVar = "";
    isFunction = false;
    isFunctionDefined = false;
    isFunctionDeclared = false;
    returnTypeOfFunction = "";
    Next = NULL;
}

SymbolInfo::~SymbolInfo()
{
    delete Next;
}
