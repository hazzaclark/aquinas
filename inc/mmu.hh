// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE MOUDLARISATION OF THE MMU

#ifndef MMU_HH
#define MMU_HH

// NESTED INCLUDES

#include <mmu_def.hh>
#include <mmu_mem.hh>
#include <util.hh>

// SYSTEM INCLUDES

#include <functional>

namespace aquinas
{
    namespace mmu
    {
        class MMU_BASE; 
        
        // CREATE A HANDLER TYPE FOR BEING ABLE TO DELEGATE THE FORWARD
        // DECLARATION OF THE MMU AGAINST COMMON PARAMS
        template<typename MMU_EA_READER>
        using MMU_HANDLER = std::function<void(MMU_BASE*, U32 EA, U16 MASK, MMU_EA_READER READ_EA);
    }
}

#endif
