#pragma once

#ifdef __AVX__
static constexpr bool avx=true;
#else
static constexpr bool avx=false;
#endif

// Check for AVX2 support
#ifdef __AVX2__
static constexpr bool avx2=true;
#else
static constexpr bool avx2=false;
#endif

// Check for AVX-512 Foundation support
#ifdef __AVX512F__
static constexpr bool avx512f=true;
#else
static constexpr bool avx512f=false;
#endif

// Check for AVX-512 Conflict Detection support
#ifdef __AVX512CD__
static constexpr bool avx512cd=true;
#else
static constexpr bool avx512cd=false;
#endif

// Check for AVX-512 Prefetch support
#ifdef __AVX512PF__
static constexpr bool avx512pf=true;
#else
static constexpr bool avx512pf=false;
#endif

// Check for AVX-512 Exponential and Reciprocal support
#ifdef __AVX512ER__
static constexpr bool avx512er=true;
#else
static constexpr bool avx512er=false;
#endif

// Check for AVX-512 Vector Length Extensions support
#ifdef __AVX512VL__
static constexpr bool avx512vl=true;
#else
static constexpr bool avx512vl=false;
#endif

// Check for AVX-512 Byte and Word Instructions support
#ifdef __AVX512BW__
static constexpr bool avx512bw=true;
#else
static constexpr bool avx512bw=false;
#endif

// Check for AVX-512 Doubleword and Quadword Instructions support
#ifdef __AVX512DQ__
static constexpr bool avx512dq=true;
#else
static constexpr bool avx512dq=false;
#endif

// Check for AVX-512 Integer Fused Multiply-Add Instructions support
#ifdef __AVX512IFMA__
static constexpr bool avx512ifma=true;
#else
static constexpr bool avx512ifma=false;
#endif

// Check for AVX-512 Vector Byte Manipulation Instructions support
#ifdef __AVX512VBMI__
static constexpr bool avx512vbmi=true;
#else
static constexpr bool avx512vbmi=false;
#endif
