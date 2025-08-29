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

#include <array>
#include <functional>
#include <unordered_map>

namespace aquinas
{
    namespace mmu
    {
        class MMU_BASE; 

        // RAW FUNCTION POINTER FOR MEMORY READ
        // MITIGATE THE OVERHEAD FOR NEEDLESS TEMPLATE CREATION

        using MMU_FUNC_READ_16 = std::function<U16(U32)>;
        
        // CREATE A HANDLER TYPE FOR BEING ABLE TO DELEGATE THE FORWARD
        // DECLARATION OF THE MMU AGAINST COMMON PARAMS

        using MMU_HANDLER = std::function<void(MMU_BASE*, MMU_FUNC_READ_16, U32)>;

        // CREATE A HANDLER TYPE FOR THE OPCODE HANDLER STRUCTURE
        // WHICH WILL PRESUPPOSE THE BASELINE MMU HANDLER TO DETERMINE EA
        // IN CONJUNCTION WITH THE MASK, MATCH AND CYCLES

        struct MMU_OPCODE
        {
            MMU_HANDLER HANDLER;
            U16 MASK;
            U16 MATCH;
            U8 CYCLES;
            const char* NAME;
        };

        class MMU_BASE
        {
            public:
                MMU_BASE();
                ~MMU_BASE() = default;

                void FLUSH_TLB() noexcept { TLB.clear(); }
                void FLUSH_TLB_ENTRY(U32 ADDRESS) noexcept;
                bool LOOKUP_TLB(U32 LOG_ADDRESS, U32& PHYS_ADDRESS) noexcept;
                void INSERT_TLB(U32 LOG_ADDRESS, U32 PYS_ADDRESS) noexcept;

            private:
                U32 CRP;
                U32 SRP;
                U16 TC;
                U16 SR;
                U32 TRANS;

                // CACHE FOR TRANSLATION TLB
                std::unordered_map<U32, U32> TLB;
        };
    }
}

#endif
