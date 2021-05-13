#include"stdafx.h"
#include"Instruction.h"

//Parse instruction into label, op code, operand1, operand2 and return the type of instruction
Instruction::InstructionType Instruction::ParseInstruction(string m_instruction)
{
    //making a copy of the original instruction
    string a_line = m_instruction;

    //removing comments from a line
    removeComments(a_line);

    //if endStr is not empty, then the instruction is invalid
    if (!ParseLineIntoFields(a_line, m_Label, m_OpCode, m_Operand1, m_Operand2))
    {
        //CHECKCHECK report error - failed to parse b/c instruction was invalid !!!!!!!!
    }

    return computeType(m_OpCode);
}


//remove comments from instruction
void Instruction::removeComments(string& a_line)
{
    // Demonstrating how to remove a semicolon and everything after it from a string

    // The code below searches for the first semicolon in a string and deletes
    // it and everything after it.  If there is no semicolon, it will delete nothing.
    size_t isemi1 = a_line.find(';');
    if (isemi1 != string::npos)
    {
        a_line.erase(isemi1);
    }
    return;
}

//Parse a line of instruction into label, op code, operand1,  and return false if instruction is invalid
bool Instruction::ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
    string& a_Operand1, string& a_Operand2)
{
    // Get rid of any commas from the line.
    replace(a_line.begin(), a_line.end(), ',', ' ');

    // Get the elements of the line.  That is the label, op code, operand1, and operand2.
    string endStr;
    a_label = a_OpCode = a_Operand1 = a_Operand2 = "";
    istringstream ins(a_line);
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
Instruction::InstructionType Instruction::computeType(string& a_OpCode)
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

// Convert string to lower case
string Instruction::lowerCase(string a_OpCode)
{
    for (int i = 0; i < a_OpCode.length(); i++)
    {
        a_OpCode[i] = tolower(a_OpCode[i]);
    }
    return a_OpCode;
}

//Compute locaiton of next instruction
int Instruction::LocationNextInstruction(int a_loc)
{
    //There is no next instruction in the case of a comment
    if (m_type == ST_Comment)
    {
        return a_loc;
    }

    //Checking if the instruction is org
    if (m_type == ST_MachineLanguage && lowerCase(m_OpCode) == "org")
    {
        return stoi(m_Operand1);
    }
    else if (m_type == ST_MachineLanguage && lowerCase(m_OpCode) == "ds")
    {
        return a_loc + stoi(m_Operand1);
    }

    //Increment location by 1
    return a_loc + 1;
}