// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY ENCOMPASSING MEMORY READ AND WRITES
// UTILISING INTRINSIC C++ FEATURES TO DYNAMICALLY HELP WITH MEMORY OPERATIONS

// MOREOVER, THIS IS ESSENTIALLY A C++ PORT OF LIB68K_MEM - WHICH IS BEING REPURPOSED
// FOR THE SOLE BENEFIT OF REPRODUCING THE SAME EFFICIENT READ AND WRITES AS PER THE 68K BUS
// ALBEIT WITH SLIGHT ALTERATIONS TO ACCOMMODATE FOR THE INTRINSIC'S OF THE MMU

#ifndef MMU_MEM_HH
#define MMU_MEM_HH

// NESTED INCLUDES

#include <common.hh>
#include <util.hh>

// SYSTEM INCLUDES  

#include <array>
#include <algorithm>
#include <bitset>
#include <memory>
#include <vector>

namespace aquinas
{
    namespace mmu_mem_opts
    {
        #define     MAX_BUFFERS             5
        #define     MAX_ADDR_START          0x0000000
        #define     MAX_MEMORY_SIZE         0x1000000
        #define     MAX_ADDR_END            (MAX_ADDR_START + MAX_MEMORY_SIZE - 1)

        // DEFINE ENUM'S TO INADVERTENTLY REPLACE THE NEED FOR CONSTANT EXPRESSIONS
        // HELPS WITH BEING ABLE TO REPURPOSE AND MODULARISE LATER ON

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

        enum class MEMORY_ERROR
        {
            OK,
            BOUNDS,
            READONLY,
            UNMAPPED,
            BUS,
            BUFFER,
            SIZE,
            RESERVED,
            OVERF,
            BAD_READ,
            BAD_WRITE
        };

        enum class MEMORY_OPT_FLAG : U8
        {
            BASIC = 1 << 0,
            VERBOSE = 1 << 1,
        };
    }

    namespace mmu_mem
    {
        struct MEMORY_USAGE
        {
            U32 READ_COUNT;
            U32 WRITE_COUNT;
            U32 LAST_READ;
            U32 LAST_WRITE;
            U32 VIOLATION;
            bool ACCESSED;
        };

        class MEMORY_BUFFER
        {
            private:
                std::unique_ptr<U8[]> BUFFER;
                U32 BASE;
                U32 END;
                U32 SIZE;
                MEMORY_USAGE USAGE;
                bool WRITEABLE;

            // CONSTRUCT A BASE OBJECT OF THE MEMORY BUFFER - WHICH WILL PRESUPPOSE THE ARBITARY
            // STATE OF THE START AND END.

            // LEVERAGES A UNIQUE IDENTIFIER TO BE ABLE TO CREATE AN BUFFER OBJECT OF AN ARBITARY TYPE
            // TO MOULD TO THE CIRCUMSTANCES BY WHICH THE OBJECT IS CREATED FOR

            // UPON CREATION, FILL THE RANGE WITH THE PARAMETERS OF THE BUFFER
            // IN RELATION TO THE START

            public:
                MEMORY_BUFFER(U32 START, U32 END, bool WRITEABLE) 
                : BASE(START), END(END), SIZE(END - BASE + 1), WRITEABLE(WRITEABLE)
                {
                    BUFFER = std::make_unique<U8[]>(SIZE);
                    std::fill_n(BUFFER.get(), SIZE, 0);
                }

                // GETTER METHODS FOR ACCESSING CLASS ATTRIBUTES
                bool MEM_CONTAINS(U32 ADDRESS) const noexcept;
                U32 MEM_BASE() const noexcept { return BASE; }
                U32 MEM_END() const noexcept { return END; }
                U32 MEM_SIZE() const noexcept { return SIZE; }
                bool MEM_WRITEABLE() const noexcept { return WRITEABLE; }
                const MEMORY_USAGE& MEM_USAGE() const noexcept { return USAGE; }

                // MEMORY OPERATIONS
                std::unique_ptr<U32> MEM_READ(U32 ADDRESS, aquinas::mmu_mem_opts::MEMORY_SIZE MEM_SIZE);
                bool MEM_WRITE(U32 ADDRESS, U32 VALUE, aquinas::mmu_mem_opts::MEMORY_SIZE MEM_SIZE);
        };

        class MEMORY_MANAGER
        {
            private:
                std::vector<std::unique_ptr<MEMORY_BUFFER>> BUFFERS;
                std::bitset<8> ENABLED_FLAGS;
                bool TRACE_ENABLED = true;
                bool STOPPED = false;

                static constexpr std::array<const char*, 11> ERROR_MSG = 
                {
                    "OK",
                    "MEMORY OUT OF BOUNDS",
                    "MEMORY IS READ ONLY", 
                    "MEMORY REGION IS UNMAPPED",
                    "MEMORY HAS EXCEEDED BUS LIMIT",
                    "MEMORY HAS TOO MANY BUFFERS",
                    "MEMORY HAS AN INVALID SIZE FOR REGION",
                    "MEMORY VIOLATES A RESERVED RANGE",
                    "MEMORY OVERFLOW",
                    "MEMORY ENCOUNTERED A BAD READ",
                    "MEMORY ENCOUNTERED A BAD WRITE"
                };

                bool IS_TRACE_ENABLED(aquinas::mmu_mem_opts::MEMORY_OPT_FLAG FLAG) const noexcept;
                void ENABLE_TRACE_FLAGS(aquinas::mmu_mem_opts::MEMORY_OPT_FLAG FLAG) noexcept;
                void DISABLE_TRACE_FLAGS(aquinas::mmu_mem_opts::MEMORY_OPT_FLAG FLAG) noexcept;

            // WHAT MAKES THESE PRIVATE METHODS DIFFERENT TO THE MEMORY BUFFER
            // IS THAT THIS ENCOMPASSES THE GENERAL MANAGEMENT OF THE OPERATIONS

            // THIS ESPECIALLY HELPS WITH BEING ABLE TO ACCESS THE INTRINSICS PASSED THROUGH
            // IN THE SOURCE FILE

            private:
                U32 MEMORY_READ(U32 ADDRESS, aquinas::mmu_mem_opts::MEMORY_SIZE MEM_SIZE);
                void MEMORY_WRITE(U32 ADDRESS, U32 VALUE, aquinas::mmu_mem_opts::MEMORY_SIZE MEM_SIZE);

            public:
                MEMORY_MANAGER();

                void SET_STOPPED(bool STOPPED) { STOPPED = STOPPED; }
                void SHOW_MEMORY_MAPS() const;
                
                bool MAP_MEMORY(U32 BASE, U32 END, bool WRITEABLE);
                MEMORY_BUFFER* MEM_FIND(U32 ADDRESS);

                U8 MEM_READ_8(U32 ADDRESS);
                U16 MEM_READ_16(U32 ADDRESS);
                U32 MEM_READ_32(U32 ADDRESS);

                void MEM_WRITE_8(U32 ADDRESS, U8 VALUE);
                void MEM_WRITE_16(U32 ADDRESS, U16 VALUE);
                void MEM_WRITE_32(U32 ADDRESS, U32 VALUE);

            private:
                void MEM_TRACE(aquinas::mmu_mem_opts::MEMORY_OPTION OP, U32 ADDRESS, 
                            aquinas::mmu_mem_opts::MEMORY_SIZE SIZE, U32 VALUE) const;

                void VERBOSE_TRACE(const std::string& MSG) const;
        };
    }
}

#endif
