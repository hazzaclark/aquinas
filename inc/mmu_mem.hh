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
#include <memory>

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

                // MOVE CONSTRUCTOR AND ASSIGNMENT
                MEMORY_BUFFER(MEMORY_BUFFER&&) = default;
                MEMORY_BUFFER& operator=(MEMORY_BUFFER&&) = default;
        };
    }
}

#endif
