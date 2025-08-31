// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE MODULARISATION OF THE OPCODE TABLE 
// AND THE RESPECTIVE DEFINTIONS ENCOMPASSING THAT

// THIS AIMS TO TAKE A SIMILAR APPROACH THAT OF LIB68K AND IT'S OPCODE
// HANDLER SCHEME - WHICH HAS PROVED TO BE FRUITFUL IN PROVIDING THE FASTEST SOLUTION

// NESTED INCLUDES

#include <mmu.hh>
#include <mmu_def.hh>
#include <mmu_mem.hh>

using namespace aquinas;
using namespace aquinas::mmu;
using namespace aquinas::mmu::opcode;

/////////////////////////////////////////////////////////////////
//                 MMU MAIN INITIALISATION
/////////////////////////////////////////////////////////////////

MMU_BASE::MMU_BASE(mmu_mem::MEMORY_MANAGER* MEM)
    : CRP(0), SRP(0), TC(0), SR(0), TRANS(0), MEM(MEM)
{
        TLB.clear();
}

/////////////////////////////////////////////////////////////////
//                 MMU MAIN OPCODE DEFINTIONS
/////////////////////////////////////////////////////////////////

MMU_MAKE_OPCODE(PFLUSHA, 
{
    MMU->FLUSH_TLB();
})

// GENERATE THE HANDLER TABLE FOR ALL RESPECTIVE OPCODE ENTRIES
static const MMU_OPCODE MMU_OPCODE_HANDLER_TLB[] = 
{
    { PFLUSHA_HANDLER, 0xFFFF, 0xF518, 4, "PFLUSHA "},
};

// TACKLES THE SAME SORT OF PRINCIPLE IN BEING ABLE TO UTILISE
// A FUNCTION POINTER TO ACCESS THE CONCURRENT OPCODE DEF 

void MMU_BUILD_OPCODE_TABLE(std::array<MMU_HANDLER, 0x10000>& MMU_OPCODE_TLB,
                                    std::array<U8, 0x10000>& CYCLE_RANGE)
{
    int INDEX = 0;
    const MMU_OPCODE* OPCODE;

    // INITIALISE ALL OF THE ENTIRES
    for(INDEX = 0; INDEX < 0x10000; INDEX++)
    {
        MMU_OPCODE_TLB[INDEX] = nullptr;
        CYCLE_RANGE[INDEX] = 0;
    }

    // MAP THE CORRESPONDING OPCODE TO THE HANDLER
    OPCODE = MMU_OPCODE_HANDLER_TLB; 
    while(OPCODE->HANDLER != nullptr)
    {
        printf("PROCESSING MMU OPCODE: MASK = 0x%04X, MATCH = 0x%04X, HANDLER ADDRESS = %p, NAME = %s\n",
               OPCODE->MASK, OPCODE->MATCH, (void*)OPCODE->HANDLER, OPCODE->NAME);

        for(INDEX = 0; INDEX < 0x10000; INDEX++)
        {
            // PRESUPPOSE THAT WE NOW HAVE A MATCH
            if((INDEX & OPCODE->MASK) == OPCODE->MATCH)
            {
                MMU_OPCODE_TLB[INDEX] = OPCODE->HANDLER;
                CYCLE_RANGE[INDEX] = OPCODE->CYCLES;
            }
        }

        OPCODE++;
    }
}
