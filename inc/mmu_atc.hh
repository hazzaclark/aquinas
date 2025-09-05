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

        // ATC PERMISSION FLAGS
        enum class ATC_PERMS : U8
        {
            ATC_PERM_NONE = 0x00,
            ATC_PERM_READ = 0x01,
            ATC_PERM_WRITE = 0x02,
            ATC_PERM_EXEC = 0x04,
            ATC_PERM_ALL = 0x07
        };  

        // ATC FUNCTION CODE DEFS FOR ADDRESS SPACES
        enum class ATC_FUNC_CODES : U8
        {
            ATC_FC_USR_DATA = 1,
            ATC_FC_USR_PROG = 2,
            ATC_FC_RES_1 = 3,
            ATC_FC_RES_2 = 4,
            ATC_FC_SPV_DATA = 5,
            ATC_FC_SPV_PROG = 6,
            ATC_FC_CPU_SPACE = 7
        };
    }
}


#endif
