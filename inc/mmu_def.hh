// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE MOUDLARISATION OF BASIC DEFINES TO DO WITH THE
// MEMORY MANAGEMENT UNIT SPECIFICALLY - FOCUSSING MORE SO ON THE DEFINTIONS FOR
// OPERATION MASKS

#ifndef MMU_DEF_HH
#define MMU_DEF_HH

// NESTED INCLUDES

#include <common.hh>

namespace aquinas
{
    namespace mmu_def
    {
        #define     MMU_ATC_ENTRIES         64
        #define     MMU_ATC_MAX_TLB         7
        #define     MMU_SR_BUS_ERR          0x8000
    }
}

#endif
