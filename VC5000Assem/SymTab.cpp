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

// Symbol Table Map, Symbol is the key and location is value to the map here
std::map<std::string, int> m_symbolTable;

void SymbolTable::AddSymbol( const std::string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    std::map<std::string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() )
    {
        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}

void SymbolTable::DisplaySymbolTable() {
    std::cout << "Symbol Table:" << std::endl;
    std::cout << "Symbol #" << "   " << "Symbol" << "   " << "Location" << std::endl;

    int s_num = 0;
    for (auto iter : m_symbolTable) 
    {
        std::cout << s_num << "\t   " << iter.first << "\t    " << iter.second << std::endl;
        s_num++;
    }

    //Prompt for user to press enter
    std::cout << "--------------------------------------------------\n\n";
    std::cout << "Press Enter to Continue...";
    std::cin.get();
}

bool SymbolTable::LookupSymbol(const std::string& a_symbol, int& a_loc) 
{
    std::map<std::string, int>::iterator it = m_symbolTable.find(a_symbol);

    //If iterator reaches the end, the symbol is not in the table
    if (it != m_symbolTable.end())
    {
        //set location to the value corresponding to the symbol in the table
        a_loc = it->second;
        return true;
    }

    return false;
}
