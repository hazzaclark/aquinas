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

        template<typename MMU_EA_READER>
        using MMU_HANDLER = std::function<void(MMU_BASE*, U32 EA, U16 MASK, MMU_EA_READER READ_EA)>;

        // CREATE A HANDLER TYPE FOR THE OPCODE HANDLER STRUCTURE
        // WHICH WILL PRESUPPOSE THE BASELINE MMU HANDLER TO DETERMINE EA
        // IN CONJUNCTION WITH THE MASK, MATCH AND CYCLES

        template<typename MMU_EA_READER>
        struct MMU_OPCODE
        {
            MMU_HANDLER<MMU_EA_READER> HANDLER;
            U16 MASK;
            U16 MATCH;
            U8 CYCLES;
            const char* NAME;

            MMU_OPCODE() = default;
            MMU_OPCODE(MMU_HANDLER<MMU_EA_READER> HANDLER_, U16 MASK_, U16 MATCH_, U8 CYCLES_, const char* NAME_)
                : HANDLER(HANDLER_), MASK(MASK_), MATCH(MATCH_), CYCLES(CYCLES_), NAME(NAME_) {} 
        };

        class MMU_BASE
        {
            public:
                template<typename MMU_EA_READER>
                using MMU_HANDLER_TABLE = std::array<MMU_HANDLER<MMU_EA_HANDLER>, 0x10000>;

                using MMU_CYCLES_TABLE = std::array<U8, 0x10000>;

                MMU_BASE();
                ~MMU_BASE() = default;

                // OPCODE HANDLER DECLARATIONS
                template<typename MMU_EA_READER>
                static void PFLUSHA_HANDLER(MMU_BASE* MMU, U32 EA, U16 MASK, MMU_EA_READER EA_);

                template<typename MMU_EA_READER>
                static void PFLUSHAN_HANDLER(MMU_BASE* MMU, U32 EA, U16 MASK, MMU_EA_READER EA_);

                template<typename MMU_EA_READER>
                static void PFLUSH_HANDLER(MMU_BASE* MMU, U32 EA, U16 MASK, MMU_EA_READER EA_);

                template<typename MMU_EA_READER>
                static void PLOADR_HANDLER(MMU_BASE* MMU, U32 EA, U16 MASK, MMU_EA_READER EA_);

                template<typename MMU_EA_READER>
                static void PLOADW_HANDLER(MMU_BASE* MMU, U32 EA, U16 MASK, MMU_EA_READER EA_);

                template<typename MMU_EA_READER>
                static void PMOVE_HANDLER(MMU_BASE* MMU, U32 EA, U16 MASK, MMU_EA_READER EA_);

                template<typename MMU_EA_READER>
                static void PTESTR_HANDLER(MMU_BASE* MMU, U32 EA, U16 MASK, MMU_EA_READER EA_);

                template<typename MMU_EA_READER>
                static void PTESTW_HANDLER(MMU_BASE* MMU, U32 EA, U16 MASK, MMU_EA_READER EA_);

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
