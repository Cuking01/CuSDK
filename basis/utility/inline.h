#pragma once

#if defined(_MSC_VER)
    // MSVC Compiler
    #define ALWAYS_INLINE __forceinline
    #define ALWAYS_INLINE_LAMBDA __forceinline
    #define NO_INLINE __attribute__((noinline))
#elif defined(__GNUC__) || defined(__clang__)
    // GCC or Clang Compiler
    #define ALWAYS_INLINE __attribute__((always_inline)) inline
    #define ALWAYS_INLINE_LAMBDA __attribute__((always_inline))
    #define NO_INLINE __declspec(noinline)
#else
    // Other compilers
    #error "unknown compiler."
#endif


