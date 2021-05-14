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

    //----- Using code from the website for the functions removeComments and ParseLineIntoFilelds -----

    //Search for semicolon in the instruction and remov everything after it
    void removeComments(std::string& a_line);    

    // Break instruction into label, op code, operand1, operand2
    // If it returns an empty std::string for the op code, it indicates an empty std::string
    // Return false if there are extra fields
    bool ParseLineIntoFields(std::string a_line, std::string& a_label, std::string& a_OpCode,
        std::string& a_Operand1, std::string& a_Operand2);

    //Compute and return the type of instruction
    InstructionType computeType(std::string& a_OpCode);

    //Remove comments, parse string into components, and return the type of instruction
    InstructionType ParseInstruction(std::string m_instruction);

    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc);

    // To access the label
    inline std::string &GetLabel() { return m_Label; };

    // To determine if a label is blank.
    inline bool isLabel() { return ! m_Label.empty(); };

    // Convert a std::string to lowercase
    std::string lowerCase(std::string a_OpCode);

    // Translate assembly instruction into machine language
    std::pair<int, std::string> TranslateInstruction(std::string& a_line, int a_loc);

    //Stores symbolic op codes in a map and returns their respective numeric op codes
    int OpCodeNumber(std::string& a_loc);

    //Pads a string with specified leading characters until it has the specified number of characters and then returns it
    std::string zeroPadding(std::string a_temp, int a_length);

private:
    // The elemements of a instruction
    std::string m_Label;            // The label.
    std::string m_OpCode;       // The symbolic op code.
    std::string m_Operand1;     // The first operand. 
    std::string m_Operand2;     // The second operand.
    std::string m_instruction;    // The original instruction.

    // Derived values.
    int m_NumOpCode;     // The numerical value of the op code for machine language equivalents.
    InstructionType m_type; // The type of instruction.

    bool m_IsNumericOperand1;// == true if the operand is numeric.
    int m_Operand1Value;   // The value of the operand if it is numeric.
};