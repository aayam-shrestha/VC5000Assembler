//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( const string &a_symbol, int a_loc );

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/

void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() )
    {
        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

void SymbolTable::DisplaySymbolTable() {
    cout << "Symbol Table:" << endl;
    cout << "Symbol #" << "   " << "Symbol" << "   " << "Location" << endl;

    int s_num = 0;
    for (auto iter : m_symbolTable) 
    {
        cout << s_num << "\t   " << iter.first << "\t    " << iter.second << endl;
        s_num++;
    }
    std::cout << "--------------------------------------------------\n\n";
    std::cout << "Press Enter to Continue...";
    cin.get();
}

bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc) 
{
    return true;
}
