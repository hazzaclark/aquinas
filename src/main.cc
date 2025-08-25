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

    MEM_MANAGER.SET_STOPPED(true);
    MEM_MANAGER.SHOW_MEMORY_MAPS();
    return 0;
}
