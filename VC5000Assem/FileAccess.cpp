//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

//Constructor for FileAccess class
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }

    // Open the file.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 ); 
    }
}

//Destructor for FileAccess class
FileAccess::~FileAccess( )
{
    // Not that necessary since the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}

// Get the next line from the file.
bool FileAccess::GetNextLine( string &a_line )
{
    // If there is no more data, return false.
    if( m_sfile.eof() )
    {
        return false;
    }
    getline( m_sfile, a_line );
    
    // Return indicating success.
    return true;
}

void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}