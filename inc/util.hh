// COPYRIGHT (C) HARRY CLARK 2025
// STANDALONE REFERENCE UTILITY FOR SIMULATING THE MOTOROLA 68851 MMU

#ifndef UTIL_HH
#define UTIL_HH

// NESTED INCLUDES

#include <common.hh>

// SYSTEM INCLUDES

#include <string>

namespace aquinas
{
    namespace util
    {
        constexpr size_t KB_TO_BYTES = 1024;
        constexpr size_t MB_TO_BYTES = 1024 * 1024;

        // C++ REWRITE OF THE COMMON UTILIIES I HAVE PRE-SUPPOSED
        // FOR MEMORY OPERATIONS WHICH REQUIRE A PROPER FORMATTING OF SIZE
        
        inline std::string FORMAT_UNIT(size_t SIZE)
        {
            return SIZE >= MB_TO_BYTES ? "MB" : 
                    SIZE >= KB_TO_BYTES ? "KB" : "B";
        }

        constexpr auto FORMAT_SIZE(size_t SIZE)
        {
            return SIZE >= MB_TO_BYTES ? SIZE / MB_TO_BYTES :
           SIZE >= KB_TO_BYTES ? SIZE / KB_TO_BYTES : SIZE;
        }

        // UTILITY FOR EXTRACING SPECIFIC BITS FOR DYNAMIC BIT MANIPULATION
        // PRESUPPOSES AN INTEGRAL VALUE AS THE BIT MANTISSA BASED ON AN ARBITRARY SIZE
        
        template<typename T> 
        constexpr T EXTRACT_BITS(T VALUE, int START, int NUM)
        {
            static_assert(std::is_integral<T> "[EXTRACT] -> REQUIRES INTEGRAL TYPE ARG\n");
            const T MASK = (T(1) << NUM) - 1;

            return (VALUE >> START) & MASK;
        }
    }
}

#endif
