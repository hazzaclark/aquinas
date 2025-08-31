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
        
        // CREATE A HANDLER TYPE FOR BEING ABLE TO DELEGATE THE FORWARD
        // DECLARATION OF THE MMU AGAINST COMMON PARAMS

        using MMU_HANDLER = void(*)(MMU_BASE*, U32);

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
            private:
                U32 CRP;
                U32 SRP;
                U16 TC;
                U16 SR;
                U32 TRANS;

            public:
                mmu_mem::MEMORY_MANAGER* MEM;
                std::unordered_map<U32, U32> TLB;

            public:
                MMU_BASE();
                MMU_BASE(mmu_mem::MEMORY_MANAGER* MEM);

                void FLUSH_TLB() noexcept { TLB.clear(); }
                void FLUSH_TLB_ENTRY(U32 ADDRESS) noexcept;
                bool LOOKUP_TLB(U32 LOG_ADDRESS, U32& PHYS_ADDRESS) noexcept;
                void INSERT_TLB(U32 LOG_ADDRESS, U32 PYS_ADDRESS) noexcept;

                U32 GET_CRP() const noexcept { return CRP; }
                void SET_CRP(U32 VALUE) noexcept { CRP = VALUE; }

                U32 GET_SRP() const noexcept { return SRP; }
                void SET_SRP(U32 VALUE) noexcept { SRP = VALUE; }

                U16 GET_TC() const noexcept { return TC; }
                void SET_TC(U32 VALUE) noexcept { TC = VALUE; }

                U16 GET_SR() const noexcept { return SR; }
                void SET_SR(U32 VALUE) noexcept { SR = VALUE; }

                U16 GET_TRANS() const noexcept { return TRANS; }
                void SET_TRANS(U32 VALUE) noexcept { TRANS = VALUE; }
        };

        namespace opcode
        {
            void MMU_BUILD_OPCODE_TABLE(std::array<MMU_HANDLER, 0x10000>& MMU_OPCODE_TLB,
                                    std::array<U8, 0x10000>& CYCLE_RANGE);

            void MMU_EXEC(MMU_BASE* INST, U32& PC, int MAX_CYCLES);

            #define MMU_MAKE_OPCODE(OP, IMPL) \
            static void OP##_HANDLER(MMU_BASE* MMU, U32 PC)  \
            { \
                IMPL \
            }
        }
    }
}

#endif
