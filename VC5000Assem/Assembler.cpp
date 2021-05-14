//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

/**/
/*
Assembler::Assembler( int argc, char *argv[] )

NAME

    Assembler::Assembler - Constructor for the assembler that takes in file name as arguments

SYNOPSIS

    Assembler::Assembler(int argc, char *argv[]);
    argc		-->			Total number of arguments in the command line
    argv		-->			Pointer to the array of arguments passed through the command line

DESCRIPTION

    This function is the constructor for the Assembler class. 
    We are passing argc and argv to the file access constructor.

*/
/**/ 
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}

// Destructor currently does nothing.  You might need to add something as you develop this project.
Assembler::~Assembler( ) 
{
}/* Assembler::Assembler( int argc, char *argv[] ) */

/**/
/*
void Assembler::PassI( )

NAME

    Assembler::PassI - Performs first pass through the code and adds symbols to the symbol table

SYNOPSIS

    void Assembler::PassI()

DESCRIPTION

    This function establishes the location of the labels.
    It doesn't handle errors.

*/
/**/
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
}/* void Assembler::PassI( ) ; */


/**/
/*
void Assembler::PassII( )

NAME

    Assembler::PassII - generates translation of the assembly language into machine code.

SYNOPSIS

    void Assembler::PassII();

DESCRIPTION

    This function translates the assembly language code into machine code for the VC5000 computer.
    The function records any errors encountered while translating and stores the translated instructions in a vector of pairs for
    passing into the emulator program. It also prints the translation of each line with the original statement and reports any errors
    at the end.

*/
/**/
void Assembler::PassII()
{
    // Tracks the location of the instructions to be generated.
    int loc = 0;

    // Flag that indicates if the code has reached the end statement
    bool is_end = false;

    // Moving file pointer to the beginning of the file and clearing the eof flag
    m_facc.rewind();

    //Initialize error reports
    Errors::InitErrorReporting();

    //Clear the vector that's holding the pair of location and content
    m_machineCode.clear();

    //Output message for translation of program
    std::cout << "\nTranslation of Program: " << std::endl;
    std::cout << "Location" << "   " << "Contents" << "   " << "Original Statement" << std::endl;

    // Processing each line of source code
    for (; ; ) {

        // Read the next line from the source file.
        std::string line;
        if (!m_facc.GetNextLine(line))
        {
            if (is_end == true)
            {
                break;
            }

            // If there are no more lines, we are missing an end statement.
            //Report error 
            Errors::RecordError("Location: " + std::to_string(loc) + " -> Missing an END statement");
            break;
        }

        //Pair to store machine language instruction
        std::pair<int, std::string> translation = m_inst.TranslateInstruction(line, loc);

        

        //Set end flag to true when end statement appears
        if (translation == std::pair <int, std::string>(0, "end"))
            is_end = true;

        //If there is no valid machine code
        else if (translation != std::pair<int, std::string>(0, "n/a"))
        {
           m_machineCode.push_back(translation);
        }

        if (m_inst.computeType(line) == m_inst.ST_Comment || m_inst.computeType(line) == m_inst.ST_End)
        {
            continue;
        }
        else
        {
            //Get the location of next instruction
            loc = m_inst.LocationNextInstruction(loc);
        }

        //Display error if it is not empty
        if (!Errors::isEmpty())
        {
            Errors::DisplayErrors();
        }
    }
    
    //Prompt for user to press enter
    std::cout << "--------------------------------------------------\n\n";
    std::cout << "Press Enter to Continue...";
    std::cin.get();
    return;
}/* void Assembler::PassII(); */

/**/
/*
    void Assembler::RunProgramInEmulator()

NAME

   Assembler::RunProgramInEmulator - runs translated machine code in the emulator

SYNOPSIS

    void Assembler::RunProgramInEmulator90;

DESCRIPTION

    This function runs the machine language program in the VC5000 emulator and reports any errors that may arise

RETURNS

    VOID

AUTHOR

    Aayam Shrestha

DATE

    3:40 PM 05/12/2021
*/
/**/
void Assembler::RunProgramInEmulator()
{
    std::cout << "Results from emulating program" << std::endl;
    //Terminate the emulation if there are errors
    if (!Errors::isEmpty())
    {
        std::cout << "Errors encountered. End of emulation." << std::endl;
        return;
    }

    //Insert the machine code into the emulator class and report error
    for (std::vector<std::pair<int, std::string>>::iterator it = m_machineCode.begin(); it != m_machineCode.end(); ++it)
    {
        bool insert_check = m_emul.insertMemory(it->first, stoi(it->second));

        if (!insert_check)
        {
            Errors::RecordError("Error inserting the command: " + std::to_string(it->first) + " " + it->second + "in emulator.");
        }
    }
    //Run emulator program and check for error
    bool check_error = m_emul.runProgram();

    if (!check_error)
    {
        Errors::RecordError("Errors running the Emulator ");
    }

    //Display errors encountered during emulation
    if (!Errors::isEmpty())
    {
        Errors::DisplayErrors();
    }
    std::cout << "Press Enter to Continue..." << std::endl;
    std::cin.ignore();
}   /* void Assembler::RunProgramInEmulator() */