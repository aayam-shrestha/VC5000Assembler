//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
// What other choices do we have to accomplish the same thing?
//
#pragma once

#include <string>
#include <vector>

class Errors {

public:
    
    // Initializes error reports.
    static void InitErrorReporting();

    // Records an error message.
    static void RecordError(std::string a_emsg);

    // Displays the collected error message.
    static void DisplayErrors();

    //Check if vector for error messages is empty and returns a bool
    static bool IsEmpty();

private:

    static std::vector<std::string> m_ErrorMsgs;  // This must be declared in the .cpp file.  Why?
};