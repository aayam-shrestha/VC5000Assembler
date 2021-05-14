#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"

/**/
/*
bool emulator::insertMemory(int a_location, long long a_contents)

NAME

	emulator::insertMemory(int a_location, long long a_contents)) - Inserts the machine language contents into the memory location

SYNOPSIS

	bool emulator::insertMemory(int a_location, long long a_contents)
	a_location		-->			location of the machine language
	a_contents		-->			content of the machine language

DESCRIPTION

	This function inserts the contents into VC 5000 Computer.

RETURNS

	Returns true if successfully inserted in memory and false if not.

AUTHOR

	Aayam Shrestha

DATE

	2:42 PM 05/11/2021
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

	emulator:: runProgram - Runs the VC5000 program recorded in memory.

SYNOPSIS

	bool emulator::runProgram();

DESCRIPTION

	This function will run the emulator for VC 5000 Computer.

RETURNS

	Returns true if the program executed successfully and fasle otherwise.

AUTHOR

	Aayam Shrestha

DATE

	4:20 PM 05/12/2021
*/
/**/
bool emulator::runProgram()
{

	int loc = 100;			//Variable to store location
	std::string user_input;		// Variable to store user input
	char sign = 'n';	 //Variable to store sign

	while (true)
	{
		int instr = m_memory[loc]; //Instruction at the given location
		int opCode = instr / 10000000;		//Extracting opcode from machine code
		int regNum = instr / 1000000 % 10;	//Extracting register number from machine code
		int address = instr % 1000000;		//Extracting address from machine code 

		switch (opCode)
		{
		case 1:
			//ADD
			m_reg[regNum] += m_memory[address];
			++loc;
			break;
		case 2:
			//SUB
			m_reg[regNum] -= m_memory[address];
			++loc;
			break;
		case 3:
			//MULT
			m_reg[regNum] *= m_memory[address];
			++loc;
			break;
		case 4:
			//DIV
			m_reg[regNum] /= m_memory[address];
			++loc;
			break;
		case 5:
			//LOAD
			m_reg[regNum] = m_memory[address];
			++loc;
			break;
		case 6:
			//STORE
			address = m_reg[regNum];
			++loc;
			break;
		case 7:
			//READ
			std::cout << "?";
			std::cin >> user_input;
			//Check if the user input is negative or positive
			//Remove the sign if negative 
			if (user_input[0] == '-')
			{
				sign = user_input[0];
				//Erase first character from user input
				user_input = user_input.erase(0, 1);
			}

			//Check if the user input is number
			for (auto& it : user_input)
			{
				if (!isdigit(it))
				{
					std::cout << "Each character of input must be a number" << std::endl;
				}
			}
			//Store user input to memory address
			m_memory[address] = stoi(user_input);
			if (sign == '-')
			{
				m_memory[address] *= -1;
			}
			loc++;
			break;
		case 8:
			//WRITE
			std::cout << m_memory[address] << std::endl;
			loc++;
			break;
		case 9:
			//BRANCH  
			loc = address;
			break;
		case 10:
			//BRANCH MINUS
			if (m_reg[regNum] < 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;
		case 11:
			//BRANCH ZERO
			if (m_reg[regNum] == 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;
		case 12:
			//BRANCH POSITIVE
			if (m_reg[regNum] > 0)
			{
				loc = address;
			}
			else
			{
				loc++;
			}
			break;
		case 13:
			//HALT
			exit(1);

		default:
			std::cerr << "Illegal Opcode" << std::endl;
			return false;
		}
		//Check if the program ends
		/*if (is_end)
		{
			return true;
		}*/
	}
	return false;
} /* bool emulator::runProgram() */