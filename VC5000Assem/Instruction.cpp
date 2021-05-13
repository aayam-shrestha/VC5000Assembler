#include"stdafx.h"
#include"Instruction.h"

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