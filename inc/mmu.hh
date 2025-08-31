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

        using MMU_HANDLER = void(*)(MMU_BASE*, MMU_FUNC_READ_16, U32);

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
                std::unordered_map<U32, U32> TLB;

                mmu_mem::MEMORY_MANAGER* MEM;

            public:
                MMU_BASE();
                ~MMU_BASE() = default;

                void FLUSH_TLB() noexcept { TLB.clear(); }
                void FLUSH_TLB_ENTRY(U32 ADDRESS) noexcept;
                bool LOOKUP_TLB(U32 LOG_ADDRESS, U32& PHYS_ADDRESS) noexcept;
                void INSERT_TLB(U32 LOG_ADDRESS, U32 PYS_ADDRESS) noexcept;

                [[nodiscard]] U32 GET_CRP() const noexcept { return CRP; }
                void SET_CRP(U32 VALUE) noexcept { CRP = VALUE; }

                [[nodiscard]] U32 GET_SRP() const noexcept { return SRP; }
                void SET_SRP(U32 VALUE) noexcept { SRP = VALUE; }

                [[nodiscard]] U16 GET_TC() const noexcept { return TC; }
                void SET_TC(U32 VALUE) noexcept { TC = VALUE; }

                [[nodiscard]] U16 GET_SR() const noexcept { return SR; }
                void SET_SR(U32 VALUE) noexcept { SR = VALUE; }

                [[nodiscard]] U16 GET_TRANS() const noexcept { return TRANS; }
                void SET_TRANS(U32 VALUE) noexcept { TRANS = VALUE; }

                // INSTRUCTION HANDLERS
                static void PFLUSHA_HANDLER(MMU_BASE* MMU, MMU_FUNC_READ_16 MEM_READ, U32 PC);
                static void PFLUSHAN_HANDLER(MMU_BASE* MMU, MMU_FUNC_READ_16 MEM_READ, U32 PC);
                static void PFLUSH_HANDLER(MMU_BASE* MMU, MMU_FUNC_READ_16 MEM_READ, U32 PC);
                static void PLOADR_HANDLER(MMU_BASE* MMU, MMU_FUNC_READ_16 MEM_READ, U32 PC);
                static void PLOADW_HANDLER(MMU_BASE* MMU, MMU_FUNC_READ_16 MEM_READ, U32 PC);
                static void PMOVE_HANDLER(MMU_BASE* MMU, MMU_FUNC_READ_16 MEM_READ, U32 PC);
                static void PTESTR_HANDLER(MMU_BASE* MMU, MMU_FUNC_READ_16 MEM_READ, U32 PC);
                static void PTESTW_HANDLER(MMU_BASE* MMU, MMU_FUNC_READ_16 MEM_READ, U32 PC);
        };

        namespace opcode
        {
            void MMU_BUILD_OPCODE_TABLE(std::array<MMU_HANDLER, 0x10000>& MMU_OPCODE_TLB,
                                    std::array<U8, 0x10000>& CYCLE_RANGE);

            void MMU_EXEC(MMU_BASE* INST, MMU_FUNC_READ_16 MEM_READ, U32& PC, int MAX_CYCLES);

            extern MMU_OPCODE MMU_OPCODE_HANDLER_TLB[];
        }
    }
}

#endif
