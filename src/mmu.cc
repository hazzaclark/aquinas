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

MMU_BASE::MMU_BASE(mmu_mem::MEMORY_MANAGER* MEM)
    : CRP(0), SRP(0), TC(0), SR(0), TRANS(0), MEM(MEM)
{
        TLB.clear();
}

// AN EXECUTION LOOP THAT IS VERY SIMILAR TO LIB68K
// IN THE SENSE BY WHICH WE ARE ABLE TO UTILISE THE FUNCTION POINTER FOR THE
// OPCODE TABLE TO DYNAMICALLY EXECUTE INSTRUCTIONS

void mmu::opcode::MMU_EXEC(MMU_BASE* INST, U32& PC, int MAX_CYCLES)
{
    int CURRENT_CYCLES = 0;
    bool STOPPED = false;

    // BUILD OPCODE TABLE (PRESUPPOSES A FUNCTION PTR)
    static std::array<MMU_HANDLER, 0x10000> MMU_OPCODE_TLB;
    static std::array<U8, 0x10000> CYCLE_RANGE;

    MMU_BUILD_OPCODE_TABLE(MMU_OPCODE_TLB, CYCLE_RANGE);

    while(!STOPPED && CURRENT_CYCLES < MAX_CYCLES)
    {
        U16 MMU_IR = INST->MEM->MEM_READ_16(PC);

        // GET CURRENT CYCLE COUINT FOR CURRENT INSTR
        int INSTR_CYCLES = CYCLE_RANGE[MMU_IR];

        printf("[PC -> %08X]  [IR -> %04X]  ", PC, MMU_IR);

        // MAP THE FUNCTION POINTER TO THE CURRENT OPCODE TABLE
        MMU_HANDLER HANDLER = MMU_OPCODE_TLB[MMU_IR];
        HANDLER(INST, PC);

        PC += 2;
        CURRENT_CYCLES += INSTR_CYCLES;
        printf("CYCLES: %d, TOTAL ELAPSED: %d\n", INSTR_CYCLES, CURRENT_CYCLES);
        printf("-------------------------------------------------------------\n");
    }
}
