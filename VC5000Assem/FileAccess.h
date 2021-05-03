//
//		File access to source file.
//
#pragma once

#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

private:
    ifstream m_sfile;   // Source file object.

public:
    // Opens the file.
    FileAccess( int argc, char *argv[] );

    // Closes the file.
    ~FileAccess( );

    // Get the next line from the source file. Returns true if there was one.
    bool GetNextLine( string &a_line );

    // Put the file pointer back to the beginning of the file.
    void rewind( );
};