// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY ENCOMPASSING MEMORY READ AND WRITES
// UTILISING INTRINSIC C++ FEATURES TO DYNAMICALLY HELP WITH MEMORY OPERATIONS

#ifndef MMU_MEM_HH
#define MMU_MEM_HH

// NESTED INCLUDES

#include <common.hh>

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
    }
}

#endif