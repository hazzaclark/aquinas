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

// SIMILAR EXECUTION LOOP AKIN TO THE LIKENESS OF LIB68K
// UTILISES A FUNCTION POINTER IN ORDER TO DYNAMICALLY DETERMINE 
// OPCODE DECLARATIVES, PC ADVANCEMENTS, ETC

void mmu::opcode::MMU_EXEC(MEMORY_MANAGER* MEM)
{
    // 31/08/25
    // A LOT OF THESE ARE HERE SIMPLY BECAUSE THAT UNLIKE LIB68K
    // WE ARENT REALLY TOO CONCERNED WITH HAVING AN OVERARCHING
    // CYCLE COUNT - AS WE ARE EMULATING THE CPU CYCLE ACCURATELY

    MMU_BASE* INST = new MMU_BASE(MEM);
    int STOPPED = 0;
    int OPCODE_CYCLES = 0;
    int CYCLES_USED = 0;
    unsigned MMU_PC = 0;

    while(!STOPPED)
    {
        // READ THE CURRENT INSTRUCTION INTO A MOCK IR
        // DISCERN HOW MANY CYCLES IT TAKES
        U16 MMU_IR = INST->MEM->MEM_READ_16(MMU_PC);

        printf("[PC -> %04X]  [IR -> %04X]  ", 
               MMU_PC, MMU_IR);
               
        OPCODE_CYCLES = MMU_CYCLE_RANGE[MMU_IR];

        // PASS THE INDEXXED OPCODE INTO THE FUNCTION POINTER
        MMU_OPCODE_HANDLER[MMU_IR](INST);

        MMU_PC += 2;
        CYCLES_USED += OPCODE_CYCLES;
    }
    
    printf("TOTAL CYCLES USED: %d\n", CYCLES_USED);
    delete INST;
}
