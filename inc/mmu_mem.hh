// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY ENCOMPASSING MEMORY READ AND WRITES
// UTILISING INTRINSIC C++ FEATURES TO DYNAMICALLY HELP WITH MEMORY OPERATIONS

#ifndef MMU_MEM_HH
#define MMU_MEM_HH

// NESTED INCLUDES

#include <common.hh>
#include <util.hh>

// SYSTEM INCLUDES  

#include <array>
#include <algorithm>

namespace aquinas
{
    namespace mmu_mem
    {
        #define     MAX_BUFFERS             5
        #define     MAX_ADDR_START          0x0000000
        #define     MAX_MEMORY_SIZE         0x1000000
        #define     MAX_ADDR_END            (MAX_ADDR_START + MAX_MEMORY_SIZE - 1)

        enum class MEMORY_OPTION : char
        {
            READ = 'R',
            WRITE = 'W',
            INVALID_READ = '!',
            INVALID_WRITE = '?',
            MAP = 'M',
            UNMAP = 'U',
            MOVE = 'O',
            ERROR = 'E'
        };

        enum class MEMORY_SIZE : U8
        {
            SIZE_8 = 8,
            SIZE_16 = 16,
            SIZE_32 = 32
        };
    }
}

#endif
