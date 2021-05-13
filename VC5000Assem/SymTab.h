//
//		Symbol table class.
//
#pragma once

// This class is our symbol table.
class SymbolTable {

private:
    // This is the actual symbol table.  The symbol is the key to the map.  The value is the location.
    std::map<std::string, int> m_symbolTable;

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
    bool LookupSymbol(const std::string& a_symbol, int& a_loc);
};