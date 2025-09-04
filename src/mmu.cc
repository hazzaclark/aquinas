// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE MOUDLARISATION OF THE MMU

// NESTED INCLUDES

#include <mmu.hh>
#include <mmu_mem.hh>
#include <mmu_def.hh>

using namespace aquinas;
using namespace aquinas::mmu;
using namespace aquinas::mmu_mem;
using namespace aquinas::mmu::opcode;
using namespace aquinas::util;

/////////////////////////////////////////////////////////////////
//                 MMU MAIN INITIALISATION
/////////////////////////////////////////////////////////////////

MMU_BASE::MMU_BASE()
    : CRP(0), SRP(0), TC(0), SR(0), TRANS(0), MEM(nullptr)
{
    MEM = new MEMORY_MANAGER();
    TLB.clear();
}

MMU_BASE::MMU_BASE(mmu_mem::MEMORY_MANAGER* MEM)
    : CRP(0), SRP(0), TC(0), SR(0), TRANS(0), MEM(MEM)
{
        TLB.clear();
}

// SIMPLE INSERTION FOR THE PAGING TLB 
// ALL OF THIS JUST PRESUPPOSES A RAW ARRAY WHICH ACCESSES THE 
// LOGICAL PAGE AGAINST THE PHYSICAL PAGE

void MMU_BASE::INSERT_TLB(U32 LOG_ADDRESS, U32 PHYS_ADDRESS) noexcept
{
    U32 LOG_PAGE = LOG_ADDRESS & MMU_PAGE_MAX;
    U32 PHYS_PAGE = PHYS_ADDRESS & MMU_PAGE_MAX;

    // ADD TO THE TLB BUFFER
    TLB[LOG_PAGE] = PHYS_PAGE;
    printf("TLB ENTRY INSERTED: 0x%08X -> 0x%08X\n", LOG_PAGE, PHYS_PAGE);
}

// LOOKUP THE TABLE BASED ON A LOGICAL AND PHYSCIAL ADDRESS
// THIS IS TO DETERMINE THE PAGING BETWEEN MEMORY CHUNKS
// TO DETERMINE WHAT IS A LOGICAL OR PHYSICAL ADDRESS

bool MMU_BASE::LOOKUP_TLB(U32 LOG_ADDRESS, U32& PHYS_ADDRESS) noexcept
{
    U32 PAGE = LOG_ADDRESS & MMU_PAGE_MAX;
    auto INDEX = TLB.find(PAGE);

    // ASSUME WE AREN'T AT THE END
    // PROCEED TO INDEX AGAINST ALL SECONDARY ELEMENTS IN RELATION
    // TO THE OFFSET
    if(INDEX != TLB.end())
    {
        PHYS_ADDRESS = INDEX->second | (LOG_ADDRESS & MMU_PAGE_OFF);
        return true;
    }

    return false;
}

// SIMILAR EXECUTION LOOP AKIN TO THE LIKENESS OF LIB68K
// UTILISES A FUNCTION POINTER IN ORDER TO DYNAMICALLY DETERMINE 
// OPCODE DECLARATIVES, PC ADVANCEMENTS, ETC

void mmu::opcode::MMU_EXEC(MEMORY_MANAGER* MEM)
{
    // 31/08/25
    // A LOT OF THESE ARE HERE SIMPLY BECAUSE THAT UNLIKE LIB68K
    // WE ARENT REALLY TOO CONCERNED WITH HAVING AN OVERARCHING
    // CYCLE COUNT - AS WE ARE EMULATING THE CPU CYCLE ACCURATELY

    std::unique_ptr<MMU_BASE> INST = std::make_unique<MMU_BASE>(MEM);
    int OPCODE_CYCLES = 0;
    int CYCLES_USED = 0;

    while(!INST->MEM->IS_STOPPED())
    {
        // READ THE CURRENT INSTRUCTION INTO A MOCK IR
        // DISCERN HOW MANY CYCLES IT TAKES
        INST->IR = INST->MEM->MEM_READ_16(INST->PC);
            
        OPCODE_CYCLES = MMU_CYCLE_RANGE[INST->IR];

        printf("[PC -> %04X]  [IR -> %04X]  ", 
               INST->PC, INST->IR);

        // PASS THE INDEXXED OPCODE INTO THE FUNCTION POINTER
        MMU_OPCODE_HANDLER[INST->IR](INST.get());

        INST->PC += 2;
        CYCLES_USED += OPCODE_CYCLES;
    }
    
    printf("\nTOTAL CYCLES USED: %d\n", CYCLES_USED);
}
