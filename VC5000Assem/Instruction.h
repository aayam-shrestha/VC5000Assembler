//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once
#include<sstream>
#include<algorithm>

// The elements of an instruction.
class Instruction{

public:
    Instruction( ) { };
    ~Instruction( ) { };

    // Codes to indicate the type of instruction we are processing.  Why is this inside the class?
    enum InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,  		// Assembler Language instruction.
        ST_Comment,          		// Comment or blank line
        ST_End                   		// end instruction.
    };
    // Parse the Instruction.
    InstructionType ParseInstruction(string m_instruction);

    //----- Using code from the website for the functions removeComments and ParseLineIntoFilelds -----

    //Search for semicolon in the instruction and remov everything after it
    void removeComments(string& a_line);    

    // Break instruction into label, op code, operand1, operand2
    // If it returns an empty string for the op code, it indicates an empty string
    // Return false if there are extra fields
    bool ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
        string& a_Operand1, string& a_Operand2);

    //Compute and return the type of instruction
    InstructionType computeType(string& a_OpCode);

    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc);

    // To access the label
    inline string &GetLabel() { return m_Label; };

    // To determine if a label is blank.
    inline bool isLabel() { return ! m_Label.empty(); };

    // To convert a string to lowercase
    string lowerCase(string a_OpCode);

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