// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE MAIN FUNCTIONALITY OF THE PROGRAM

// NESTED INCLUDES

#include <mmu_mem.hh>
#include <mmu_def.hh>
#include <mmu.hh>

// SYSTEM INCLUDES

#include <cstdio>
#include <array>

using namespace aquinas::mmu_mem_opts;
using namespace aquinas::mmu_mem;
using namespace aquinas::mmu;
using namespace aquinas::mmu::opcode;

int main(void)
{
    printf("===================================\n");
    printf("HARRY CLARK - M68851 MMU SIMULATOR\n");
    printf("===================================\n");

    MEMORY_MANAGER MEM_MANAGER;
    MMU_BASE MMU(&MEM_MANAGER);

    MEM_MANAGER.MAP_MEMORY(0x00000, 0x7FFFF, true);
    MEM_MANAGER.MAP_MEMORY(0x80000, 0xFFFFF, false);

    MEM_MANAGER.SHOW_MEMORY_MAPS();
    
    aquinas::mmu::opcode::MMU_BUILD_OPCODE_TABLE();
    
    printf("\nMANUALLY LOAD MMU OPCODES INTO MEMORY \n");
    MEM_MANAGER.MEM_WRITE_16(0x0000, 0xF518);
    MEM_MANAGER.MEM_WRITE_16(0x0002, 0xF510);
    MEM_MANAGER.MEM_WRITE_16(0x0004, 0xF000);

    aquinas::mmu::opcode::MMU_EXEC(&MEM_MANAGER);

    printf("\nTESTING TLB LOOKUP\n");

    U32 PHYS_ADDR;
    U32 LOG_ADDR = 0x1000;

    MMU.INSERT_TLB(LOG_ADDR, 0x10000);
    bool RESULT = MMU.LOOKUP_TLB(LOG_ADDR, PHYS_ADDR);
    printf("[L]: 0x%08X -> [R]: %s\n", LOG_ADDR, RESULT ? "HIT" : "MISS");

    MEM_MANAGER.SET_STOPPED(true);
    MEM_MANAGER.SHOW_MEMORY_MAPS();
    return 0;
}
