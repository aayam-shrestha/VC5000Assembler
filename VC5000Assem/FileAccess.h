//
//		File access to source file.
//
#pragma once

#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

private:

    // Source file object
    std::ifstream m_sfile;   

public:
    // Opens the file.
    FileAccess( int argc, char *argv[] );

    // Closes the file.
    ~FileAccess( );

    // Get the next line from the source file. Returns true if there was one.
    bool GetNextLine( std::string &a_line );

    // Put the file pointer back to the beginning of the file.
    void rewind( );

    //Prints each line of the file
    void PrintFile();
};