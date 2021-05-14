//
//		Implementation of the symbol table class.  This is the format I want for commenting functions.
//
#include "stdafx.h"
#include "SymTab.h"

// Symbol Table Map, Symbol is the key and location is value to the map here
std::map<std::string, int> m_symbolTable;

/**/
/*
void SymbolTable::AddSymbol( const std::string &a_symbol, int a_loc )

NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( const std::string &a_symbol, int a_loc );
    a_symbol        --> symbol of op code
    a_loc           --> memory location

DESCRIPTION

    This function will insert a symbol "a_symbol" and its location "a_loc"
    into the symbol table map.

*/
/**/
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
}/*void SymbolTable::AddSymbol( const std::string &a_symbol, int a_loc );*/


/**/
/*
void SymbolTable::DisplaySymbolTable( )

NAME

    DisplaySymbolTable - prints the symbol table generated from Pass I to the console

SYNOPSIS

    void SymbolTable::DisplaySymbolTable();

DESCRIPTION

    This function will print the symbols and locations from the symbol table map

*/
/**/
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
}/*void SymbolTable::DisplaySymbolTable();*/


/**/
/*
bool SymbolTable::LookupSymbol(const std::string& a_symbol, int& a_loc)

NAME

    SymbolTable::LookupSymbol - checks if the symbol is present in the symbol table.

SYNOPSIS

    bool SymbolTable::LookupSymbol(const std::string& a_symbol, int& a_loc);
    a_symbol  -----> symbol to be looked up in the table
    a_loc     -----> if the symbol exists in symbol table, its 
                     corresponding location will be stored in a_loc

DESCRIPTION

    This function will loop through the symbol table to check if the symbol 
    exists in the symbol table. It will update the location if the symbol is 
    found. It returns true if the symbol is present and false otherwise.

*/
/**/
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
}/*bool SymbolTable::LookupSymbol(const std::string& a_symbol, int& a_loc)*/

/**/
/*
bool SymbolTable::MatchSymbol(std::string a_symbol, int a_loc)

NAME

    SymbolTable::MatchSymbol(string a_symbol, int a_loc) - checks if the symbol is present in Symbol Table


SYNOPSIS

    bool SymbolTable::LookupSymbol(std::string a_symbol, int a_loc);
    a_symbol    --> symbol that is to be looked up in the table
    a_loc       --> location to be matched with the symbol

DESCRIPTION

    This function loops through the symbol table and checks is the symbol already exists in the table.
    It also checks if the entered memory location matches that of the symbol.

RETURNS

    Returns true if the entered symbol and location already exist in the symbol table

AUTHOR

    Aayam Shrestha

DATE

    9:24 PM 05/11/2021
*/
/**/
bool SymbolTable::isSymbolMatch(std::string a_symbol, int a_loc)
{
    std::map<std::string, int>::iterator it = m_symbolTable.find(a_symbol);
    if (it != m_symbolTable.end())
    {
        if (a_loc == it->second)
        {
            return true;
        }
    }
    return false;
} /* bool SymbolTable::MatchSymbol(std::string a_symbol, int a_loc) */
