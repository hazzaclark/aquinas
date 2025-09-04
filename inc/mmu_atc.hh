// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE MOUDLARISATION OF THE MMU
// PARTICULARLY FOCUSSING ON THE ATC ENTRIES FOR THE PAGING TLB 

#ifndef MMU_ATC_HH
#define MMU_ATC_HH

// NESTED INCLUDES

#include <mmu_def.hh>
#include <util.hh>

// SYSTEM INCLUDES

#include <memory>

namespace aquinas
{
    namespace atc
    {
        // DEFINE THE BASIS FOR A PROPRIATORY ATC ENTRY
        struct ATC_ENTRY
        {
            U32 LOG_ADDR;
            U32 PHYS_ADDR;
            U16 PERM;
            U8 FUNC_CODE;
            bool IS_VALID;
            bool MODIFIED;
            bool USED;
            bool CACHED;
            U32 LAST_ACCESS;

            ATC_ENTRY()  :  LOG_ADDR(0), PHYS_ADDR(0), PERM(0),
                            FUNC_CODE(0), IS_VALID(false), MODIFIED(false),
                            USED(false), CACHED(false), LAST_ACCESS(0) {}
        };

        // GENERIC PERFORMANCE MONITORING FOR ATC OPERATIONS
        struct ATC_STATS
        {
            U32 HITS;
            U32 MISSES;
            U32 EVICT;
            U32 PRELOAD;
            U32 FLUSHES;
            std::float_t RATE() const { return HITS + MISSES > 0 ? (std::float_t)HITS / (HITS + MISSES) * 100.0f : 0; }
        };
    }
}


#endif