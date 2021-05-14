#include"Errors.h"
#include"stdafx.h"

// Vector to store and record the error messages
std::vector<std::string> Errors::m_ErrorMsgs;

/*
void Errors::InitErrorReporting()

NAME

    Errors::InitErrorReporting - Initializes error reports

SYNOPSIS

    void Errors::InitErrorReporting();

DESCRIPTION

    This function will initialize error reporting by erasing all 
    previous errors from the vector containing error messages

*/
/**/
void Errors::InitErrorReporting()
{
	m_ErrorMsgs.clear();
}/*void Errors::InitErrorReporting();*/


/**/
/*
void Errors::RecordError(const std::string a_emsg)

NAME

    Errors::RecordError - records error messages in a vector

SYNOPSIS

    void Errors::RecordError(const std::string a_emsg)
    a_emsg  ---> Constant String Error Messages generated at different section of programs

DESCRIPTION

    This function records any type of errors found while parsing, translating or emulating the VC1620 Assembler
    It pushes back error into vector

RETURNS

    VOID

AUTHOR

    Aayam Shrestha

DATE

    10:00 AM 5/1/2021

*/
/**/
void Errors::RecordError(std::string a_emsg)
{
	m_ErrorMsgs.push_back(a_emsg);
}/*void Errors::RecordError(std::string a_emsg);*/


/**/
/*
void Errors:: DisplayErrors()

NAME

    Errors:: DisplayErrors - Displays the collected error messages

SYNOPSIS

    void Errors:: DisplayErrors();

DESCRIPTION

    This function displays/ prints the errors from the vector generated at different point of program like parsing, translating and emulating

RETURNS

    VOID

AUTHOR

    Aayam Shrestha

DATE

    11:19 PM 5/1/2021

*/
/**/
void Errors::DisplayErrors()
{
    for (size_t i = 0; i < m_ErrorMsgs.size(); i++)
    {
        std::cerr << m_ErrorMsgs[i] << std::endl;
    }
    m_ErrorMsgs.clear();
}/*void Errors::DisplayErrors();*/


/**/
/*
bool Errors::isEmpty()

NAME

    Errors::isEmpty - Check if vector for error messages is empty and returns a bool

SYNOPSIS

    bool Errors::isEmpty();

DESCRIPTION

    This function checks if there are any errors present. If it's empty it returns true

RETURNS

    Returns true if error messages are empty. Otherwise returns false

AUTHOR

    Aayam Shrestha

DATE

    11:51 PM 12/21/2020

*/
/**/
bool Errors::isEmpty()
{
    if (m_ErrorMsgs.empty())
    {
        return true;
    }
    return false;
}/* bool Errors::isEmpty(); */