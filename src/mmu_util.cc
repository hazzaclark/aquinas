// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

// THIS FILE PERTAINS TOWARDS THE FUNCTIONALITY ENCOMPASSING MEMORY READ AND WRITES
// UTILISING INTRINSIC C++ FEATURES TO DYNAMICALLY HELP WITH MEMORY OPERATIONS

// MORE SPECIFICALLY, THIS FILE AIMS TO PROVIDE MODULARISATION FOR WORKING WITH
// SOME OF THE CORE UTILITY OF THE MMU - WITHOUT CLUTTERING UP OTHER SOURCE FILES

// NESTED INCLUDES  

#include <mmu_mem.hh>
#include <mmu_def.hh>
#include <util.hh>

// SYSTEM INCLUDES

#include <cstdarg>
#include <iostream>

using namespace aquinas;
using namespace aquinas::mmu_mem;
using namespace aquinas::mmu_mem_opts;
using namespace aquinas::util;

constexpr std::array<const char*, 11> MEMORY_MANAGER::ERROR_MSG;

void MEMORY_MANAGER::MEM_TRACE(MEMORY_OPTION OP, U32 ADDRESS, 
                            MEMORY_SIZE SIZE, U32 VALUE, ...)
{
    if(IS_TRACE_ENABLED(MEMORY_OPT_FLAG::BASIC))
    {
        std::printf("[TRACE] %c ADDR:0x%08X SIZE:%d VALUE:0x%08X\n", 
                   static_cast<char>(OP), 
                   ADDRESS, 
                   static_cast<int>(SIZE), 
                   VALUE);
    }
}

void MEMORY_MANAGER::MEM_MAP_TRACE(MEMORY_OPTION OP, U32 BASE, 
                                    U32 END, MEMORY_SIZE SIZE, ...)
{
    if(IS_TRACE_ENABLED(MEMORY_OPT_FLAG::BASIC))
    {
        std::printf("[TRACE] %c -> START:0x%08X END:0x%08X SIZE:%d%s\n",
                   static_cast<char>(OP),
                   BASE,
                   END,
                   FORMAT_SIZE(static_cast<size_t>(SIZE)),
                   FORMAT_UNIT(static_cast<size_t>(SIZE)).c_str());
    }
}

void MEMORY_MANAGER::MEM_ERROR(MEMORY_OPTION OP, MEMORY_ERROR ERROR,
                                MEMORY_SIZE SIZE, const char* MSG, ...)
{
    if(IS_TRACE_ENABLED(MEMORY_OPT_FLAG::BASIC))
    {
        std::printf("[ERROR] %c -> %-18s [SIZE: %d]: ", 
                   static_cast<char>(OP), 
                   ERROR_MSG[static_cast<std::size_t>(ERROR)],
                   static_cast<int>(SIZE));
        
        va_list ARGS;
        va_start(ARGS, MSG);
        std::vprintf(MSG, ARGS);
        va_end(ARGS);
        
        std::printf("\n");
    }
}

// THIS IS THE BEST WAY I HAVE BEEN ABLE TO REPLICATE THE __VA_ARGS__ FROM C
// USING C++17 

// IT DOES LOOK REALLY MESSY, SURE - BUT IT WAS BETTER THAN WHAT I HAD BEFOREHAND
// WHEREBY I WAS CONVERTING EVERY ARG INTO TO_STRING

void MEMORY_MANAGER::VERBOSE_TRACE(const char* FMT, ...) const
{
    if(IS_TRACE_ENABLED(MEMORY_OPT_FLAG::VERBOSE))
    {
        va_list ARGS;
        va_start(ARGS, FMT);
        
        std::printf("[VERBOSE] ");
        std::vprintf(FMT, ARGS);
        std::printf("\n");
        
        va_end(ARGS);
    }
}
