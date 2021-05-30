#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"

/**/
/*
bool emulator::insertMemory(int a_location, int a_contents)

NAME

	emulator::insertMemory - inserts line of machine language code into memory location

SYNOPSIS

	bool emulator::insertMemory(int a_location, int a_contents);
	a_location		-->			location of the machine language
	a_contents		-->			content of the machine language

DESCRIPTION

	This function inserts the line of machine code into VC 5000 Computer.

RETURNS

	Returns true if instruction is successfully inserted into memory and false otherwise.

AUTHOR

	Aayam Shrestha

DATE

	2:24 PM 05/12/2021
*/
/**/
bool emulator::insertMemory(int a_location, int a_contents)
{
	if (a_location >= 0 && a_location < MEMSZ)
	{
		m_memory[a_location] = a_contents;
		return true;
	}
	else
	{
		Errors::RecordError("Location Out Of Bound");
		return false;
	}
}  /* bool emulator::insertMemory(int a_location, long long a_contents) */


/**/
/*
bool emulator::runProgram()

NAME

	emulator::runProgram - Runs the VC5000 program that is stored in memory.

SYNOPSIS

	bool emulator::runProgram();

DESCRIPTION

	This function will run the emulator for VC 5000 Computer.

RETURNS

	Returns true if the program executed successfully and fasle otherwise.

AUTHOR

	Aayam Shrestha

DATE

	4:20 PM 05/13/2021
*/
/**/
bool emulator::runProgram()
{
	//String to store user input
	std::string user_input;

	// Integer that stores memory location
	int loc = 100;				

	// Char that stores sign
	char sign = 's';			

	while (true)
	{
		// Instruction at the given location
		int instr = m_memory[loc];		

		// Extracting opcode from machine code
		int opCode = instr / 10000000;	

		// Extracting register number from machine code
		int regNum = instr / 1000000 % 10;	

		// Extracting address from machine code
		int address = instr % 1000000;		 

		// Check op code and perform corresponding actions
		switch (opCode)
		{
		case 1: //ADD
			m_reg[regNum] += m_memory[address];
			loc++;
			break;

		case 2: //SUB
			m_reg[regNum] -= m_memory[address];
			loc++;
			break;

		case 3: //MULT
			m_reg[regNum] *= m_memory[address];
			loc++;
			break;

		case 4: //DIV
			m_reg[regNum] /= m_memory[address];
			loc++;
			break;

		case 5: //LOAD
			m_reg[regNum] = m_memory[address];
			loc++;
			break;

		case 6: //STORE
			address = m_reg[regNum];
			loc++;
			break;

		case 7: //READ
			std::cout << "?";
			std::cin >> user_input;

			//If user input is negative remove the sign
			if (user_input[0] == '-')
			{
				sign = '-';
				//Erase first character from user input
				user_input = user_input.erase(0, 1);
			}

			//Check if user input is a number
			for (auto& it : user_input)
			{
				if (!isdigit(it))
				{
					std::cout << "Error: Each input character must be a number" << std::endl;
				}
			}

			//Store user input in memory
			m_memory[address] = stoi(user_input);
			if (sign == '-')
			{
				m_memory[address] *= -1;
			}
			loc++;
			break;

		case 8: //WRITE
			std::cout << m_memory[address] << std::endl;
			loc++;
			break;

		case 9: //BRANCH  
			loc = address;
			break;

		case 10: //BRANCH MINUS
			if (m_reg[regNum] < 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;

		case 11: //BRANCH ZERO
			if (m_reg[regNum] == 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;

		case 12: //BRANCH POSITIVE
			if (m_reg[regNum] > 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;

		case 13: //HALT
			std::cout << "\nEnd of Emulation" << std::endl;
			exit(1);

		default:
			std::cerr << "Illegal Opcode" << std::endl;
			return false;
		}
	}
	return false;
} /* bool emulator::runProgram() */