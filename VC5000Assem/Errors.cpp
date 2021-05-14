#include"Errors.h"
#include"stdafx.h"

// Vector to store and record the error messages
std::vector<std::string> Errors::m_ErrorMsgs;

void Errors::InitErrorReporting()
{
	m_ErrorMsgs.clear();
}

void Errors::RecordError(std::string a_emsg)
{
	m_ErrorMsgs.push_back(a_emsg);
}

void Errors::DisplayErrors()
{
    for (size_t i = 0; i < m_ErrorMsgs.size(); i++)
    {
        std::cerr << m_ErrorMsgs[i] << std::endl;
    }
    m_ErrorMsgs.clear();
}