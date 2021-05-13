//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.  
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}
// Destructor currently does nothing.  You might need to add something as you develop this project.
Assembler::~Assembler( )
{
}

// Pass I establishes the location of the labels.  You will write better function comments according to the coding standards.
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        std::string line; 
        if( ! m_facc.GetNextLine(line) ) 
        {
            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.

            return;
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( line );
               
        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
        if( st == Instruction::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.  Currently this is only comments.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
        }

        // If the instruction has a label, record it and its location in the symbol table.
        if( m_inst.isLabel( ) ) 
        {
            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}

void Assembler::PassII()
{
    // Tracks the location of the instructions to be generated.
    int loc = 0;        

    // Moving file pointer to the beginning of the file and clearing the eof flag
    m_facc.rewind();

    // End statement flag
    bool is_end = false;

    //Initialize error reports
    Errors::InitErrorReporting();

    /*
    //Clear container holding pair of location and content to pass into emulator
    m_machineCode.clear();
    */

    //Header of the translation of program
    std::cout << "Translation of Program: " << std::endl;
    std::cout << "Location" << "\t   " << "Contents" << "\t   " << "Original Statement" << std::endl;

    // Successively process each line of source code.
    for (; ; ) {

        // Read the next line from the source file.
        std::string line;
        if (!m_facc.GetNextLine(line))
        {
            //Do nothing if end statement is in place
            if (is_end == true)
            {
                true;
            }

            /*
            //CHECKCHECK CHECK FOR ERROR !!!!!

            // If there are no more lines, we are missing an end statement.
            //Report error 
            Errors::RecordError("Location: " + to_string(loc) + " -> Missing an END statement");
            break;
            */

            return;
        }

        //Pair to store machine language instruction
        std::pair<int, std::string> translation = m_inst.TranslateInstruction(line, loc);

        //Set end flag when end statement appears
        if (translation == std::pair <int, std::string>(0, "end"))
        {
            is_end = true;
        }

        //If there is no valid machine code
        else if (translation != std::pair<int, std::string>(0, "n/a"))
        {
            m_machineCode.push_back(translation);
        }

        //Get the location of next instruction
        loc = m_inst.LocationNextInstruction(loc);

        /* CHECK CHECK FOR ERROR
        
        //Display error if it is not empty
        if (!Errors::isEmptyErrors())
        {
            Errors::DisplayErrors();
        }

        */
    }
}