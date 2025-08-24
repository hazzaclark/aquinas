# aquinas
Standalone Utility for simulating the Motorola 68851 MMU 

# Motive:

The ambition with this project is to create a seamless means in which I am able to simulate the likeness of the Motorola 68851 Memory Management Unit, dependancy and library-free. 

Created using the C++17 standard, this project aims to provide an understanding into how Memory Management works with a CISC architecture.

Moreover, this project came about as a result of me wanting to be able to learn more about the inner workings and technical nuance surrounding memory management on the level by which processors and co-processors communciate with eachother. Furthermore, I wanted to make something to tie in and to cultivate my understanding for the Operating Systems module at my University.

## Building:

To build this project, you will need a C++ compiler which supports CMake 3.20. From there, it is just a case of:

```
mkdir build && cd build

cmake .. && make
```

## Sources:

[Motorola 68851 Programmer Manual](https://radio-hobby.org/uploads/datasheet/38/mc68/mc68851.pdf)


