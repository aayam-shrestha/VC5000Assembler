//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"
#include<vector>

class Assembler {
private:

    //Objects for each class for the assembler
    FileAccess m_facc;	    // File Access object
    SymbolTable m_symtab; // Symbol table object
    Instruction m_inst;	    // Instruction object
    emulator m_emul;        // Emulator object

    //Vector to store the machine language translation
    std::vector <std::pair <int, std::string>> m_machineCode;

public:

    //Constructor for assembler class
    Assembler( int argc, char *argv[] );
    ~Assembler( );

    // Pass I - establish the locations of the symbols
    void PassI( );

    // Display the symbols in the symbol table.
    void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }

    // Pass II - generate a translation
    void PassII();
    
    // Run emulator on the translation.
    void RunProgramInEmulator();
};