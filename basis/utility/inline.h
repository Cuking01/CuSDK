#pragma once

#if defined(_MSC_VER)
    // MSVC Compiler
    #define ALWAYS_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    // GCC or Clang Compiler
    #define ALWAYS_INLINE __attribute__((always_inline)) inline
#else
    // Other compilers
    #error "unknown compiler."
#endif
