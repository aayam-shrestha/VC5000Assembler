#include"stdafx.h"
#include"Instruction.h"
#include"Errors.h"
#include"SymTab.h"
#include<iomanip>

//remove comments from instruction
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
}

//Parse a line of instruction into label, op code, operand1,  and return false if instruction is invalid
bool Instruction::ParseLineIntoFields(std::string a_line, std::string& a_label, std::string& a_OpCode,
    std::string& a_Operand1, std::string& a_Operand2)
{
    // Get rid of any commas from the line.
    replace(a_line.begin(), a_line.end(), ',', ' ');

    // Get the elements of the line.  That is the label, op code, operand1, and operand2.
    std::string endStr;
    a_label = a_OpCode = a_Operand1 = a_Operand2 = "";
    std::stringstream ins(a_line);
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
}

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
}

//Remove comments, parse string into components, and return the type of instruction
Instruction::InstructionType Instruction::ParseInstruction(std::string m_instruction)
{
    //making a copy of the original instruction
    std::string a_line = m_instruction;

    //removing comments from a line
    removeComments(a_line);

    //if endStr is not empty, then the instruction is invalid
    if (!ParseLineIntoFields(a_line, m_Label, m_OpCode, m_Operand1, m_Operand2))
    {
        /*
        Errors::RecordError("Location " + std::to_string(a_loc) + " : More than four fields");
        //CHECKCHECK report error - failed to parse b/c instruction was invalid !!!!!!!!
        */
    }
    
    return computeType(m_OpCode);
}

//Compute locaiton of next instruction
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
}

//Translate a line into machine language
std::pair<int, std::string> Instruction::TranslateInstruction(std::string& a_line, int a_loc)
{
    // Parse the line and get the instruction type.
    InstructionType st = ParseInstruction(a_line);

    //Converting OpCode to lower case
    m_OpCode = lowerCase(m_OpCode);

    //Instruction(0) returns machine code
    if (st == ST_MachineLanguage)
    {
        //Store assembly language code for instruction
        std::string assembly_code = "";
        //Store the location
        int loc = 0;

        //If instruction is a single word
        if (m_Label == "" && m_Operand1 == "" && m_Operand2 == "") {
            m_OpCode = lowerCase(m_OpCode);
            //Check to see if opcode is in assembly langauge istruction
            if (OpCodeNumber(m_OpCode) != -1)
            {
                std::string a = zeroPadding("", 6);
                //Halt is the only opcode without operand
                if (m_OpCode == "halt")
                {
                    assembly_code = "139" + a;
                }
                //If not halt,  instruction is an error
                else
                {
                    Errors::RecordError("Location : " + std::to_string(a_loc) + " : Missing Operand");
                    assembly_code = std::to_string(OpCodeNumber(m_OpCode)) + "????????";
                    assembly_code = zeroPadding(assembly_code, 8);
                }
            }
            //If Operation code not found
            else
            {
                Errors::RecordError("Location : " + std::to_string(a_loc) + " Invalid Operation Command");
                assembly_code = "?????";
            }
        }

        //If two word instruction
        else if (m_Operand2 == "")
        {
            if (OpCodeNumber(m_OpCode) != -1)
            {
                assembly_code = std::to_string(OpCodeNumber(m_OpCode));
                assembly_code = zeroPadding(assembly_code, 2);

                if (SymbolTable::LookupSymbol(m_Operand1, loc))
                {
                    std::string b = zeroPadding("9", 1);
                    assembly_code = assembly_code + b + zeroPadding(std::to_string(loc), 6);
                }
                else
                {
                    Errors::RecordError("Location: " + std::to_string(a_loc) + " Undefined Operand");
                    assembly_code = assembly_code + m_Operand1;
                }
            }
            else
            {
                Errors::RecordError("Location: " + std::to_string(a_loc) + " Invalid Operation Command");
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
                Errors::RecordError("Location: " + std::to_string(a_loc) + " Invalid Operation Command");
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
}

//Stores the Op Codes in a map and returns their respective numbers
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
}

// Convert std::string to lower case
std::string Instruction::lowerCase(std::string a_OpCode)
{
    for (int i = 0; i < a_OpCode.length(); i++)
    {
        a_OpCode[i] = tolower(a_OpCode[i]);
    }
    return a_OpCode;
}

//Pads a string with specified leading zeros until it has the specified number of characters and then returns it
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
}