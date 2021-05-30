//
//		Emulator class - supports the emulation of VC1620 programs
//
#pragma once
class emulator {

public:

    // The size of VC5000 memory
    const static int MEMSZ = 1000000;

    emulator() 
    {
         m_memory.resize(MEMSZ, 0);
    }

    // Stores translated instructions in VC5000 memory
    bool insertMemory( int a_location, int a_contents );
    
    // Runs the VC5000 machine language that is stored in memory
    bool runProgram( );

private:

    // Container to simulate memory for the VC5000
    std::vector<int> m_memory;   

    // Container to simulate registers for the VC5000
    int m_reg[10];           
};