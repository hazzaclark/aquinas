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

// SIMILAR EXECUTION LOOP AKIN TO THE LIKENESS OF LIB68K
// UTILISES A FUNCTION POINTER IN ORDER TO DYNAMICALLY DETERMINE 
// OPCODE DECLARATIVES, PC ADVANCEMENTS, ETC

void mmu::opcode::MMU_EXEC(void)
{
    
}
