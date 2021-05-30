#include"stdafx.h"
#include"Instruction.h"
#include"Errors.h"
#include"SymTab.h"
#include<iomanip>

/**/
/*
void Instruction::removeComments(std::string& a_line)

NAME

    Instruction::removeComments - remove comments from instruction

SYNOPSIS

    void Instruction::removeComments(std::string& a_line);
    a_line      ---> a line of assembly language code

DESCRIPTION

    This function checks for semicolon in the instruction and 
    removes everything after and including the semicolon

RETURNS

    Returns a string that doesn't contain comments by reference

*/
/**/
void Instruction::removeComments(std::string& a_line)
{
    // Demonstrating how to remove a semicolon and everything after it from a std::string

    // The code below searches for the first semicolon in a std::string and deletes
    // it and everything after it.  If there is no semicolon, it will delete nothing.
    size_t isemi1 = a_line.find(';');
    if (isemi1 != std::string::npos)
    {
        a_line.erase(isemi1);
    }
    return;
}/* void Instruction::removeComments(std::string& a_line); */


/**/
/*
bool Instruction::ParseLineIntoFields(std::string a_line, std::string& a_label, std::string& a_OpCode,
    std::string& a_Operand1, std::string& a_Operand2)

NAME

    Instruction::ParseLineIntoFields - parse the incoming instruction.

SYNOPSIS

    bool Instruction::ParseLineIntoFields(std::string a_line, std::string& a_label, 
    std::string& a_OpCode, std::string& a_Operand1, std::string& a_Operand2);

DESCRIPTION

    This function will parse a line of code into label, opcode, operand1, and operand2 and 
    returns false if the instruction contains more than 4 elements as it is an invalid instruction

RETURNS

    Returns true if the entered line of code contains at most 4 
    elements(label, opCode, operand1, operand2) and false otherwise.
*/
bool Instruction::ParseLineIntoFields(std::string a_line, std::string& a_label, std::string& a_OpCode,
    std::string& a_Operand1, std::string& a_Operand2)
{
    // Get rid of any commas from the line.
    replace(a_line.begin(), a_line.end(), ',', ' ');

    // Get the elements of the line.  That is the label, op code, operand1, and operand2.
    std::string endStr = "";
    a_label = a_OpCode = a_Operand1 = a_Operand2 = "";
    std::stringstream ins(a_line);

    //if first character is an empty space or tab, the instruction doesn't contain a label
    if (a_line[0] == ' ' || a_line[0] == '\t')
    {
        a_label = "";
        ins >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
    }
    else
    {
        ins >> a_label >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
    }
    // If there is extra data, return false.
    return endStr.empty() ? true : false;
}/* bool Instruction::ParseLineIntoFields(std::string a_line, std::string& a_label, 
    std::string& a_OpCode, std::string& a_Operand1, std::string& a_Operand2); */


/**/
/*
Instruction::InstructionType Instruction::computeType(std::string& a_OpCode)

NAME

    Instruction::removeComments - remove comments from instruction

SYNOPSIS

    Instruction::InstructionType Instruction::computeType(std::string& a_OpCode);
    a_OpCode      ---> Operation Code of an instruction

DESCRIPTION

    This function will compare the entered op code with different
    assembly language instructions and statements to determine the
    type of instruction

RETURNS

    Returns an enum that gives instruction type (Machine language,
    Assembly language, Comment, End statement)

AUTHOR

    Aayam Shretha

DATE

    3:40 PM 5/2/2021

*/
/**/
//Compute and return instruction type(Machine language, assembly language, end statement or comment)
Instruction::InstructionType Instruction::computeType(std::string& a_OpCode)
{
    //Check OpCode to determine and return the type of instruction
    if (m_OpCode == "ds" || m_OpCode == "dc" || m_OpCode == "org")
    {
        return ST_AssemblerInstr;
    }
    else if (m_OpCode == "end")
    {
        return ST_End;
    }
    else if (m_OpCode == "")
    {
        return ST_Comment;
    }
    else
    {
        return ST_MachineLanguage;
    }
}/* Instruction::InstructionType Instruction::computeType(std::string& a_OpCode); */

/**/
/*
Instruction::InstructionType Instruction::ParseInstruction(std::string m_instruction)

NAME

    Instruction::ParseInstruction- parse the incoming instruction.

SYNOPSIS

    Instruction::InstructionType Instruction::ParseInstruction(std::string m_instruction);
    m_instruction   --> line from the source code that is to be parsed

DESCRIPTION

    This function removes comments from the line, parses it into opcode, operand and label 
    and returns the type of instruction. Errors are not checked here

RETURNS

    Returns an enum by computing the type of 
    instuction(Machine Language, Assembly Language, Comment, or End Statement)

AUTHOR
    
    Aayam Shrestha

DATE

    12:30 PM 5/5/2021

*/
Instruction::InstructionType Instruction::ParseInstruction(std::string m_instruction)
{
    //making a copy of the original instruction
    std::string a_line = m_instruction;

    //removing comments from a line
    removeComments(a_line);

    //if endStr is not empty, then the instruction is invalid
    ParseLineIntoFields(a_line, m_Label, m_OpCode, m_Operand1, m_Operand2);
    
    return computeType(m_OpCode);
}/* Instruction::InstructionType Instruction::ParseInstruction(std::string m_instruction); */


/**/
/*
int Instruction::LocationNextInstruction(int a_loc)

NAME

    Instruction::LocationNextInstruction - compute location of next instruction.

SYNOPSIS

    int Instruction::LocationNextInstruction(int a_loc);
    a_loc   --> memory location of instruction

DESCRIPTION

    This function takes a memory location as input argument and computes
    the location of the next instruction by checking the op codes and operands
    in the line of instruction.

RETURNS

    Returns an integer that gives the memory location of the next instruction.

AUTHOR

    Aayam Shrestha

DATE

    4:14 PM 5/5/2021

*/
int Instruction::LocationNextInstruction(int a_loc)
{
    //We will not increment location if we have a comment or end statement
    if (m_type == ST_Comment || m_type == ST_End)
    {
        return a_loc;
    }

    //Check if instruction is org and return the origin location as integer
    if (m_type == ST_MachineLanguage && lowerCase(m_OpCode) == "org")
    {
        return stoi(m_Operand1);
    }

    //Check if instruction is define storage and return new location after incrementing
    else if (m_type == ST_MachineLanguage && lowerCase(m_OpCode) == "ds")
    {
        return a_loc + stoi(m_Operand1);
    }

    //Increment location by 1
    return a_loc + 1;
}/* int Instruction::LocationNextInstruction(int a_loc); */


/*
std::pair<int, std::string> Instruction::TranslateInstruction(std::string& a_line, int a_loc)

NAME

    Instruction::TranslateInstruction - tranlate a line of code into machine language.

SYNOPSIS

    std::pair<int, std::string> Instruction::TranslateInstruction(std::string& a_line, int a_loc);
    a_line      ---> the line of instruction that is to be parsed and translated to machine code
    a_loc       ---> memory location of the instruction for translated machine code

DESCRIPTION

    This function translates a given line of instruction to the equivalent machine code. 
    It also deals with any errors taht may come up while translating.

RETURNS

    Returns a pair consisting of location of machine code and corresponding machine code 
    for emulator program after formatting it in the form of the VC5000's machine code.

AUTHOR

    Aayam Shrestha

DATE

    2:31 PM 5/6/2021

*/
/**/
std::pair<int, std::string> Instruction::TranslateInstruction(std::string& a_line, int a_loc)
{
    // Parse the line and get the instruction type.
    InstructionType st = ParseInstruction(a_line);

    //Report error if constant is larger than the size of a word
    if (lowerCase(m_OpCode) == "ds")
    {
        if (stoi(m_Operand1) > 999999)
        {
            Errors::RecordError("Location: " + std::to_string(a_loc) + "  Error: Constant too large");
        }
    }

    //Report error if label or operand is longer than twenty characters
    if (m_Label.length() > 20 || m_Operand1.length() > 20 || m_Operand2.length() > 20)
    {
        Errors::RecordError("Location: " + std::to_string(a_loc) + "  Error: More than twenty characters");
    }

    //Checks if instruction is machine code and performs corresponding actions
    if (st == ST_MachineLanguage)
    {
        //Store assembly language code for instruction
        std::string assembly_code = "";
        //Store the location
        int loc = 0;

        //If instruction is a single word
        if (m_Label == "" && m_Operand1 == "" && m_Operand2 == "") {
            m_OpCode = m_OpCode;
            //Check to see if opcode is in assembly langauge istruction
            if (OpCodeNumber(m_OpCode) != -1)
            {
                std::string temp_loc = zeroPadding("", 6);
                //Halt is the only opcode that doesn't have an operand
                if (m_OpCode == "halt")
                {
                    assembly_code = "139" +temp_loc;
                }
                //If the instruction is not halt and it is only one word, it is an error
                else
                {
                    Errors::RecordError("Location: " + std::to_string(a_loc) + "  Error : Missing Operand");
                    assembly_code = std::to_string(OpCodeNumber(m_OpCode)) + "????????";
                    assembly_code = zeroPadding(assembly_code, 8);
                }
            }
            //If op code not found
            else
            {
                Errors::RecordError("Location : " + std::to_string(a_loc) + "  Error: Invalid Operation Command");
                assembly_code = "?????";
            }
        }

        //If instruction has a single operand
        else if (m_Operand2 == "")
        {
            //Check if label exists
            if (isLabel())
            {
                //Check if label is multiply defined 
                if (SymbolTable::isSymbolMatch(m_Label, -999))
                {
                    Errors::RecordError("Location : " + std::to_string(a_loc) + "  Error: Multiply Defined Symbol");
                }
            }
            if (OpCodeNumber(m_OpCode) != -1)
            {
                assembly_code = std::to_string(OpCodeNumber(m_OpCode));
                assembly_code = zeroPadding(assembly_code, 2);

                if (SymbolTable::LookupSymbol(m_Operand1, loc))
                {
                    std::string temp_reg = zeroPadding("9", 1);
                    assembly_code = assembly_code + temp_reg + zeroPadding(std::to_string(loc), 6);
                }
                else
                {
                    Errors::RecordError("Location: " + std::to_string(a_loc) + "  Error: Undefined Operand");
                    assembly_code = assembly_code + m_Operand1;
                }
            }
            else
            {
                Errors::RecordError("Location: " + std::to_string(a_loc) + "  Error: Invalid Operation Command");
                assembly_code = "???";
            }
        }
        else if (m_OpCode != "" && m_Operand1 != "" && m_Operand2 != "")
        {
            if (OpCodeNumber(m_OpCode) != -1)
            {
                assembly_code = std::to_string(OpCodeNumber(m_OpCode));
                assembly_code = zeroPadding(assembly_code, 2);
                std::string b = std::to_string(loc);
                assembly_code = assembly_code + m_Operand1;

                if (SymbolTable::LookupSymbol(m_Operand2, loc))
                {
                    std::string c = std::to_string(loc);
                    assembly_code = assembly_code + zeroPadding(c, 6);
                }
                else
                {
                    std::string d = "0";
                    assembly_code = assembly_code + zeroPadding(d, 5);
                }

            }
            else
            {
                Errors::RecordError("Location: " + std::to_string(a_loc) + "  Error: Invalid Operation Command");
                assembly_code = "?????";
            }
        }
        else
        {
            assembly_code = "?????";
        }

        std::cout << std::setw(14) << std::left << a_loc << std::setw(17) << std::left << assembly_code << a_line << std::endl;
        
        return std::pair<int, std::string>(a_loc, assembly_code);
    }
    if (st == ST_AssemblerInstr && m_Operand2 == "" && lowerCase(m_OpCode) == "dc")
        std::cout << std::setw(14) << std::left << a_loc << std::setw(14) << std::left << zeroPadding(m_Operand1, 9) << a_line << std::endl;

    else if (st == ST_AssemblerInstr)
        std::cout << std::setw(14) << std::left << a_loc << std::setw(14) << std::left << "" << a_line << std::endl;

    else
        std::cout << std::setw(30) << " " << a_line << std::endl;

    if (st == ST_End)
        return std::pair < int, std::string>(0, "end");

    return std::pair <int, std::string>(0, "n/a");
}/* std::pair<int, std::string> Instruction::TranslateInstruction(std::string& a_line, int a_loc); */


/**/
/*
int Instruction::OpCodeNumber(std::string& a_loc)

NAME

    Instruction::OpcodeNumber - get op code for an operation

SYNOPSIS

    int Instruction::OpCodeNumber(std::string& a_loc);
    a_loc    ----> variable to store the numberic opCode

DESCRIPTION

    This function stores the symbolic op code in a map and returns 
    the location of the op code
    
RETURNS

    Returns an integer that contains the location of op code.
    Returns -1 if the op code doesn't exist in the map.

AUTHOR

    Aayam Shrestha

DATE

    7:51 PM 5/6/2021

*/
/**/
int Instruction::OpCodeNumber(std::string& a_loc)
{
    // Storing the Opcodes and Assembly Language Instruction in Map
    std::map<std::string, int> opcode_map
    {
        {"add", 1}, {"sub", 2}, {"mult", 3}, {"div", 4}, {"load", 5}, 
        {"store", 6}, {"read", 7}, {"write", 8}, {"b", 9},
        {"bm", 10}, {"bz", 11}, {"bp", 12}, {"halt", 13}
    };

    if (opcode_map[a_loc] <= 13 && opcode_map[a_loc] >= 1)
        return opcode_map[a_loc];

    return -1;
}/* int Instruction::OpCodeNumber(std::string& a_loc); */

/**/
/*
std::string Instruction::lowerCase(std::string a_OpCode)

NAME

    Instruction::lowerCase(string& a_OpCode) - converts a string to lowecase

SYNOPSIS

    std::string Instruction::lowerCase(std::string a_OpCode);
    a_OpCode          ---> string that is to be converted to lowercase

DESCRIPTION

    This function will convert every letter of a string to lowercase and return it

RETURNS

    Returns a string that has been converted to lowercase

AUTHOR

    Aayam Shrestha

DATE

    10:23 PM 5/5/2021

*/
/**/
std::string Instruction::lowerCase(std::string a_OpCode)
{
    for (int i = 0; i < a_OpCode.length(); i++)
    {
        a_OpCode[i] = tolower(a_OpCode[i]);
    }
    return a_OpCode;
}/* std::string Instruction::lowerCase(std::string a_OpCode); */


/*
std::string Instruction::zeroPadding(std::string a_temp, int a_length)

NAME

    Instruction::zeroPadding - Pads a string with leading zeros until it reaches the entered length

SYNOPSIS

    std::string Instruction::zeroPadding(std::string a_temp, int a_length);
    a_temp          ---> string that is to be formatted with leading zeros
    a_length        ---> the length to which the string is to be formatted

DESCRIPTION

    This function formats the string by adding leading zeros beginning until the given length of string is reached.

RETURNS

    Returns a string of the specified length that contains leading zeros.

AUTHOR

    Aayam Shrestha

DATE

    11:58 PM 5/5/2021

*/
std::string Instruction::zeroPadding(std::string a_temp, int a_length)
{
    if (a_temp.size() == a_length)
        return a_temp;
    else
    {
        for (int i = a_temp.size(); i < a_length; i++)
            a_temp.insert(0, "0");
    }
    return a_temp;
}/* std::string Instruction::zeroPadding(std::string a_temp, int a_length); */