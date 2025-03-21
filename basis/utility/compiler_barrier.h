#pragma once

#if defined(_MSC_VER)
    // MSVC Compiler
    #define Compler_Barrier asm volatile("" ::: "memory");
#elif defined(__GNUC__) || defined(__clang__)
    // GCC or Clang Compiler
    #include<intrin.h>
    #define Compler_Barrier _ReadWriteBarrier();
#else
    // Other compilers
    #error "unknown compiler."
#endif


