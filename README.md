# aquinas
Standalone Utility for simulating the Motorola 68851 MMU 

# Motive:

The ambition with this project is to create a seamless means in which I am able to simulate the likeness of the Motorola 68851 Memory Management Unit, dependancy and library-free. 

Created using the C++17 standard, this project aims to provide an understanding into how Memory Management works with a CISC architecture.

Moreover, this project came about as a result of me wanting to be able to learn more about the inner workings and technical nuance surrounding memory management on the level by which processors and co-processors communciate with eachother. All of this aims to cultivate my understanding for the Operating Systems module at my University.

# Features:

One of the many intrinsic features of this simulator is the separation between Memory Buffer and Manager-delegated mewmory regions and space.

Through this choice in design, it aims to mitigate any and all possible overhead and architectural-complications when handling specific exceptions, memory sizes, and overall operations.

Furthermore, this also aims to help with the mdoularisation of code throughout the simulator to be able to handle general Memory operations through the MMU (pre-supposing a master processor such as the 68020+) as well as bus-specific memory handles and operations.

```cpp
// BUFFER MEMORY HANDLER - ACTUALLY HANDLES THE BIT MANIPULATION 
std::unique_ptr<U32> MEMORY_BUFFER::MEM_READ(U32 ADDRESS, MEMORY_SIZE MEM_SIZE)
{
    // CREATE A GENERAL POINTER NOTATION FOR THE BUFFER
    // DISCERNS THE PROVIDED SIZE SUBSEQUENTLY
    const U8* BUFFER_PTR = BUFFER.get() + OFFSET;
    
    switch (MEM_SIZE)
    {
        case MEMORY_SIZE::SIZE_8:
            RESULT =    static_cast<U32>(BUFFER_PTR[0]);
            break;

        case MEMORY_SIZE::SIZE_16:
            RESULT =    static_cast<U32>(BUFFER_PTR[0]) << 8 |
                        static_cast<U32>(BUFFER_PTR[1]);
            break;

        case MEMORY_SIZE::SIZE_32:
            RESULT =    static_cast<U32>(BUFFER_PTR[0]) << 24 |
                        static_cast<U32>(BUFFER_PTR[1]) << 16 |
                        static_cast<U32>(BUFFER_PTR[2]) << 8 |
                        static_cast<U32>(BUFFER_PTR[3]);
            break;
    }

    return std::make_unique<U32>(RESULT);
}

// MEMORY MANAGER HANDLER - MODULARISED TO HELP WITH
// FINDING THE BUFFER, ERROR HANDLING, ETC
U32 MEMORY_MANAGER::MEMORY_READ(U32 ADDRESS, MEMORY_SIZE MEM_SIZE)
{
    // BOUND CHECKS FOR INVALID ADDRESSING
    if(ADDRESS > MAX_ADDR_END)
    {
        MEM_ERROR(MEMORY_OPTION::ERROR, MEMORY_ERROR::RESERVED, MEM_SIZE,
                "ATTEMPT TO READ FROM RESERVED ADDRESS RANGE");

        MEM_TRACE(MEMORY_OPTION::INVALID_READ, ADDRESS, MEM_SIZE, ~0U);
        return 0;
    }

    if(ADDRESS > MAX_MEMORY_SIZE)
    {
        MEM_ERROR(MEMORY_OPTION::ERROR, MEMORY_ERROR::BOUNDS, MEM_SIZE,
                "ATTEMPT TO READ FROM ADDRESS BEYOND ADDRESSABLE SPACE");

        MEM_TRACE(MEMORY_OPTION::INVALID_READ, ADDRESS, MEM_SIZE, ~0U);
        return 0;
    }
}

// HOW THEY ARE BOTH JOINED 
// MEMORY_MANAGER::MEMORY_READ()

if(auto RESULT = BUFFER->MEM_READ(ADDRESS, MEM_SIZE))
{
    MEM_TRACE(MEMORY_OPTION::READ, ADDRESS, MEM_SIZE, *RESULT);
    return *RESULT;
}
```

Another feature that has been proven to be absolutely fruitful in my relevant developments is the unique and seamless integration of auto-disable for Hooks; providing customisation for the relevant information to be displayed in the terminal

Due to the way in which some properties are accessed, it wasn't a simple case of being able to port the likeness from [lib68k_mem](https://github.com/hazzaclark/lib68k_mem/blob/main/) due to the unqiue characteristics of the pre-processor.

Instead, a compile flag has been added to mitigate this issue; see the [build scheme](https://github.com/hazzaclark/aquinas/commit/478e16bc35920b3cd797a8c05fa9a37dd909fc1c) 

Just like lib68k, this project opts to utilise the foundations set by that project to be able to define, build and recognise the Opcode Table and it's respective handlers.

Given the very limited ISA for the 68851 itself, it wasn't REALLY needed to include this abstracted means of defining opcodes but it allows for more versatility when handling respective types

```cpp
// CREATE A HANDLER TYPE FOR BEING ABLE TO DELEGATE THE FORWARD
// DECLARATION OF THE MMU AGAINST COMMON PARAMS

using MMU_HANDLER = void(*)(MMU_BASE*, U32);


// CONCATENATE A TYPE TO _HANDLER WHICH WILL
// BE ACCESSED THROUGH THE ABOVE FUNCTION POINTER
#define MMU_MAKE_OPCODE(OP, IMPL) \
static void OP##_HANDLER(MMU_BASE* MMU, U32 PC)  \
{ \
    IMPL \
}
```

## Building:

To build this project, you will need a C++ compiler which supports CMake 3.20. From there, it is just a case of:

```
mkdir build && cd build

cmake .. && make
```

## Sources:

[Motorola 68851 Programmer Manual](https://radio-hobby.org/uploads/datasheet/38/mc68/mc68851.pdf)

[Another 68851 Manual](https://archive.org/details/bitsavers_motorola68Manual3ed1988_14980771)

[lib68k_mem](https://github.com/hazzaclark/lib68k_mem)


