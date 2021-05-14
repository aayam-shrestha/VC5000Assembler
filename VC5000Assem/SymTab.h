//
//		Symbol table class.
//
#pragma once

// This class is our symbol table.
class SymbolTable {

private:

public:
    // Get rid of constructor and destructor later if you don't need them.
    SymbolTable( ) {};
    ~SymbolTable( ) {};
    
    const int multiplyDefinedSymbol = -999;

    // Add a new symbol to the symbol table.
    void AddSymbol( const std::string &a_symbol, int a_loc );

    // Display the symbol table.
    void DisplaySymbolTable();

    // Lookup a symbol in the symbol table.
    static bool LookupSymbol(const std::string& a_symbol, int& a_loc);
};