// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY ENCOMPASSING MEMORY READ AND WRITES
// UTILISING INTRINSIC C++ FEATURES TO DYNAMICALLY HELP WITH MEMORY OPERATIONS

// MOREOVER, THIS IS ESSENTIALLY A C++ PORT OF LIB68K_MEM - WHICH IS BEING REPURPOSED
// FOR THE SOLE BENEFIT OF REPRODUCING THE SAME EFFICIENT READ AND WRITES AS PER THE 68K BUS
// ALBEIT WITH SLIGHT ALTERATIONS TO ACCOMMODATE FOR THE INTRINSIC'S OF THE MMU

// NESTED INCLUDES

#include <mmu_mem.hh>
#include <mmu_def.hh>

// SYSTEM INCLUDES

#include <cstdio>

using namespace aquinas::mmu_mem_opts;
using namespace aquinas::mmu_mem;

// CONSTRUCT THE BASE OBJECT OF THE MEMORY MANAGER
// THE INITIALISATION WILL PRESUPPOSE WHICH FLAGS ARE ENABLED

MEMORY_MANAGER::MEMORY_MANAGER()
{
    ENABLED_FLAGS[static_cast<size_t>(MEMORY_OPT_FLAG::BASIC)] = true;
    ENABLED_FLAGS[static_cast<size_t>(MEMORY_OPT_FLAG::VERBOSE)] = true;
}

// DETERMINE WHAT PARAMETERS/VALUES THE CURRENT BUFFER CONTAINS
bool MEMORY_BUFFER::MEM_CONTAINS(U32 ADDRESS) const noexcept
{
    return ADDRESS >= BASE && ADDRESS <= END;
}

// RETURNS AN ITERATOR CLAUSE FROM THE FIRST ELEMENT IN A SPECIFIED RANGE
// IN THIS INSTANCE, WE WANT TO BE ABLE TO DETERMINE IF THERE IS A VALID
// BUFFER FOUND IN RELATION TO THE BASE AND END OF THE MAP

MEMORY_BUFFER* MEMORY_MANAGER::MEM_FIND(U32 ADDRESS)
{
    VERBOSE_TRACE("FOUND MEMORY: 0x%08X", ADDRESS);
    auto FOUND = std::find_if(BUFFERS.begin(), BUFFERS.end(), 
                                [ADDRESS](const auto& BUFFER)
                                {
                                    return BUFFER && BUFFER->MEM_CONTAINS(ADDRESS);
                                });

    // DETERMINE WHEN WE HAVE REACHED THE END OF A DESIGNATED BUFFER
    if(FOUND != BUFFERS.end())
    {
        // PRESUPPOSE THE CURRENT BUFFER THAT IS FOUND
        const auto& BUFFER = *FOUND;

        // CALCULATE THE BUFFER INDEX BASED ON THE SIZE AND WHAT IS FOUND
        size_t BUFFER_INDEX = std::distance(BUFFERS.begin(), FOUND);

        VERBOSE_TRACE("ACCESSED: 0x%08X [%s] IN BUFFER %u 0x%08X - 0x%08X\n", 
                        ADDRESS, 
                        BUFFER->MEM_WRITEABLE() ? "RW" : "RO",
                        BUFFER_INDEX,
                        BUFFER->MEM_BASE(),
                        BUFFER->MEM_END());

        return FOUND->get();
    }
    
    return nullptr;
}

bool MEMORY_MANAGER::MAP_MEMORY(U32 BASE, U32 END, bool WRITEABLE)
{
    auto BUFFER = std::make_unique<MEMORY_BUFFER>(BASE, END, WRITEABLE);
    BUFFERS.push_back(std::move(BUFFER));

    return true;
}

void MEMORY_MANAGER::SHOW_MEMORY_MAPS() const
{
    printf("\n%s MEMORY MAP(S):\n", STOPPED ? "AFTER EXEC" : "BEFORE EXEC");
    printf("-------------------------------\n");
    printf("START        END         ACCESS\n");
    printf("-------------------------------\n");
    
    for (const auto& BUFFER : BUFFERS)
    {
        if (BUFFER)
        {
            std::printf("0x%08X  0x%08X    (%s)\n", 
                       BUFFER->MEM_BASE(), 
                       BUFFER->MEM_END(),
                       BUFFER->MEM_WRITEABLE() ? "RW" : "RO");
        }
    }
}

