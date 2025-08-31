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

    printf("\nTESTING BASIC READ AND WRITES\n");

    U8 TEST_8 = 0xAA;
    MEM_MANAGER.MEM_WRITE_8(0x1000, TEST_8);
    U8 read_8 = MEM_MANAGER.MEM_READ_8(0x1000);
    printf("8 BIT: WROTE: 0x%02X, read: 0x%02X\n", TEST_8, read_8);

    U16 TEST_16 = 0xBBCC;
    MEM_MANAGER.MEM_WRITE_16(0x1010, TEST_16);
    U16 read_16 = MEM_MANAGER.MEM_READ_16(0x1010);
    printf("16 BIT: WROTE: 0x%04X, read: 0x%04X\n", TEST_16, read_16);

    U32 TEST_32 = 0x134CA000;
    MEM_MANAGER.MEM_WRITE_32(0x1020, TEST_32);
    U32 read_32 = MEM_MANAGER.MEM_READ_32(0x1020);
    printf("32 BIT: WROTE: 0x%08X, read: 0x%08X\n", TEST_32, read_32);

    printf("\nTESTING WRITE PROTECTION\n");
    MEM_MANAGER.MEM_WRITE_8(0x400000, 0x01);
    
    aquinas::mmu::opcode::MMU_BUILD_OPCODE_TABLE();
    
    printf("\nMANUALLY LOAD MMU OPCODES INTO MEMORY \n");
    MEM_MANAGER.MEM_WRITE_16(0x0000, 0xF518); 
    MEM_MANAGER.MEM_WRITE_16(0x0002, 0xF510);
    MEM_MANAGER.MEM_WRITE_16(0x0004, 0xF518);  

    aquinas::mmu::opcode::MMU_EXEC(&MEM_MANAGER);

    MEM_MANAGER.SET_STOPPED(true);
    MEM_MANAGER.SHOW_MEMORY_MAPS();
    return 0;
}
