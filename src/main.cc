// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE MAIN FUNCTIONALITY OF THE PROGRAM

// NESTED INCLUDES

#include <mmu_mem.hh>
#include <mmu_def.hh>

// SYSTEM INCLUDES

#include <cstdio>

using namespace aquinas::mmu_mem_opts;
using namespace aquinas::mmu_mem;

int main(void)
{
    printf("==================================\n");
    printf("HARRY CLARK - M68851 MMU SIMULATOR\n");
    printf("===================================\n");

    MEMORY_MANAGER MEM_MANAGER;

    MEM_MANAGER.MAP_MEMORY(0x00000, 0x7FFFF, true);
    MEM_MANAGER.MAP_MEMORY(0x80000, 0xFFFFF, false);

    MEM_MANAGER.SHOW_MEMORY_MAPS();

    printf("\nTESTING BASIC READ AND WRITES\n");

    U8 TEST_8 = 0xAA;
    MEM_MANAGER.MEM_WRITE_8(0x1000, TEST_8);
    U8 READ_8 = MEM_MANAGER.MEM_READ_8(0x1000);
    printf("8 BIT: WROTE: 0x%02X, READ: 0x%02X\n", TEST_8, READ_8);

    MEM_MANAGER.SET_STOPPED(true);
    MEM_MANAGER.SHOW_MEMORY_MAPS();
    return 0;
}
