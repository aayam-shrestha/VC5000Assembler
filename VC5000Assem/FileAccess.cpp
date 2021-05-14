//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

/*
FileAccess::FileAccess( int argc, char *argv[] )

NAME

    FileAccess::FileAccess - Constructor for FileAccess class that opens source file for reading

SYNOPSIS

    FileAccess::FileAccess( int argc, char *argv[] );
    argc		-->			total number of command line arguments
    argv		-->			pointer to the array of arguments passed through the command line

DESCRIPTION

    This constructor will open the file passed as command line argument for reading.
    It will throw an error message and terminate the program if the file couldn't be opened.

*/
/**/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        std::cerr << "Usage: Assem <FileName>" << std::endl;
        exit( 1 );
    }

    // Open the file.
    m_sfile.open( argv[1], std::ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        std::cerr << "Source file could not be opened, assembler terminated."<< std::endl;
        exit( 1 ); 
    }
}
//Destructor for FileAccess class
FileAccess::~FileAccess( )
{
    // Not that necessary since the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}/* FileAccess::FileAccess( int argc, char *argv[] ); */


/**/
/*
bool FileAccess::GetNextLine( string &a_line )

NAME

    FileAccess::GetNextLine - gets the next line from the source file

SYNOPSIS

    bool FileAccess::GetNextLine( string &a_line );
    a_line	-> string that will store a line of instructions after reading

DESCRIPTION

   This function will read a line from the file and store it in a_line.

RETURNS

    Returns true if read was successful and false otherwise.

*/
/**/
bool FileAccess::GetNextLine( std::string &a_line )
{
    // If there is no more data, return false.
    if( m_sfile.eof() )
    {
        return false;
    }
    getline( m_sfile, a_line );
    
    // Return indicating success.
    return true;
}/* bool FileAccess::GetNextLine( std::string &a_line ); */


/**/
/*
void FileAccess::rewind( )

NAME

    FileAccess::rewind - resets file pointer and eof flag

SYNOPSIS

    void FileAccess::rewind( );

DESCRIPTION

    This function clears the eof flag and moves file pointer to the beginning of the file.

RETURNS

    VOID

*/
/**/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, std::ios::beg );
}/* void FileAccess::rewind( ); */