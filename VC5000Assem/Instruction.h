//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once
#include<sstream>

// The elements of an instruction.
class Instruction{

public:
    Instruction( ) { };
    ~Instruction( ) { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the
    // class?
    enum InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,  		// Assembler Language instruction.
        ST_Comment,          		// Comment or blank line
        ST_End                   		// end instruction.
    };
    // Parse the Instruction.
    InstructionType ParseInstruction(string a_line) 
    { 
        //removing comments from a line
        removeComments(a_line);

        if (ParseLineIntoFields)
        {
            //CHECKCHECK report error - failed to parse b/c instruction was invalid !!!!!!!!
        }



        return ST_MachineLanguage; //CHECKCHECK THIS IS TEMPORARY!!!
    }

    //using code from the website to remove comments and parse instruction into label, op code, operand1, operand2
    void removeComments(string a_line)
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

    // Function to break down a statement into label, op code, operand1, operand2
    // If it returns an empty string for the op code, it indicates an empty string
    // The return value is false if there are extra fields.
    // Make sure you include the algorithm file.
    bool ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
        string& a_Operand1, string& a_Operand2)
    {
        // Get rid of any commas from the line.
        a_line.replace(a_line.begin(), a_line.end(), ',', ' ');

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

    

    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc) { return a_loc + 1; }; //CHECKCHECK

    // To access the label
    inline string &GetLabel( ) 
    {
        return m_Label;
    };
    // To determine if a label is blank.
    inline bool isLabel( ) 
    {
        return ! m_Label.empty();
    };

private:
    // The elemements of a instruction
    string m_Label;            // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand1;     // The first operand. 
    string m_Operand2;     // The second operand.
    string m_instruction;    // The original instruction.

    // Derived values.
    int m_NumOpCode;     // The numerical value of the op code for machine language equivalents.
    InstructionType m_type; // The type of instruction.

    bool m_IsNumericOperand1;// == true if the operand is numeric.
    int m_Operand1Value;   // The value of the operand if it is numeric.
};      