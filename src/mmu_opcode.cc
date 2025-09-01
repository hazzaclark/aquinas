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

U8 aquinas::MMU_CYCLE_RANGE[0x10000];
void(*aquinas::MMU_OPCODE_HANDLER[0x10000])(aquinas::mmu::MMU_BASE* MMU);

/////////////////////////////////////////////////////////////////
//                 MMU MAIN OPCODE DEFINTIONS
/////////////////////////////////////////////////////////////////

MMU_MAKE_OPCODE(PFLUSHA, 
{
    MMU->FLUSH_TLB();
})

// FLUSH OUT ALL NON-GLOBAL ENTRIES FROM THE ATC 
// THIS IS DONE BY DETERMINING THE GLOBAL BIT WITHIN THE MMU ITSELF

MMU_MAKE_OPCODE(PFLUSHAN,
{   
    // ASSUME THE POSITION OF THE GLOBAL BIT
    // FOR THE SAKE OF SIMPLICITY, WE CAN JUST MANUALLY BIT SHIFT ACCORDINGLY
    // AGAINST THE MANUAL GLOBAL POSITION

    const U32 MMU_GLB_MASK = (1 << MMU_ATC_SHIFT);
    U32 FLUSHED = 0;

    for(auto INDEX = MMU->TLB.begin(); INDEX != MMU->TLB.end(); )
    {
        // CHECK IF THE ENTRY IS NON-GLOBAL
        if(!(INDEX->second & MMU_GLB_MASK)) { INDEX = MMU->TLB.erase(INDEX); FLUSHED++; }

        ++INDEX;
    }
})

// IN A REAL CO-PROCESSOR SENSE, HALT WILL NOT BE GOVERNED BY THE MMU
// ADD IT HERE TO PRESUPPOSE THAT FUNCTIONALITY AND TO MITIGATE ILLEGAL INSTRUCTIONS

MMU_MAKE_OPCODE(HALT,
{
    MMU->MEM->SET_STOPPED(true);
})

MMU_MAKE_OPCODE(ILLEGAL,
{
    printf("ILLEGAL INSTRUCTION\n");
    MMU->MEM->SET_STOPPED(true);
})

// GENERATE THE HANDLER TABLE FOR ALL RESPECTIVE OPCODE ENTRIES
static const MMU_OPCODE MMU_OPCODE_HANDLER_TLB[] = 
{
    // HANDLER          // MASK         // MATCH    // CYCLES   // NAME
    { PFLUSHA_HANDLER,  0xFFFF,         0xF518,     4,          "PFLUSHA"           },
    { PFLUSHAN_HANDLER, 0xFFFF,         0xF510,     4,          "PFLUSHAN"          },
    { HALT_HANDLER,     0xFFFF,         0xF000,     4,          "HALT"              },
    { ILLEGAL_HANDLER,  0xFFFF,         0x0000,     4,          "ILLEGAL"           },
    { nullptr,             0,              0,          0,       "NULL"              }
};

// TACKLES THE SAME SORT OF PRINCIPLE IN BEING ABLE TO UTILISE
// A FUNCTION POINTER TO ACCESS THE CONCURRENT OPCODE DEF 

void mmu::opcode::MMU_BUILD_OPCODE_TABLE(void)
{
    int INDEX = 0;
    const MMU_OPCODE* OPCODE;

    // INITIALISE ALL OF THE ENTIRES
    for(INDEX = 0; INDEX < 0x10000; INDEX++)
    {
        MMU_OPCODE_HANDLER[INDEX] = ILLEGAL_HANDLER;
        MMU_CYCLE_RANGE[INDEX] = 0;
    }

    // MAP THE CORRESPONDING OPCODE TO THE HANDLER
    OPCODE = MMU_OPCODE_HANDLER_TLB; 
    while(OPCODE->HANDLER != NULL)
    {
        printf("PROCESSING MMU OPCODE: MASK = 0x%04X, MATCH = 0x%04X, HANDLER ADDRESS = %p, NAME = %s\n",
               OPCODE->MASK, OPCODE->MATCH, (void*)OPCODE->HANDLER, OPCODE->NAME);

        for(INDEX = 0; INDEX < 0x10000; INDEX++)
        {
            // PRESUPPOSE THAT WE NOW HAVE A MATCH
            if((INDEX & OPCODE->MASK) == OPCODE->MATCH)
            {
                MMU_OPCODE_HANDLER[INDEX] = OPCODE->HANDLER;
                MMU_CYCLE_RANGE[INDEX] = OPCODE->CYCLES;
            }
        }

        OPCODE++;
    }
}
