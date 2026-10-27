
// intel
// each of these includes previous except sse4a
// #include <mmintrin.h>  // MMX
// #include <xmmintrin.h> // SSE
// #include <emmintrin.h> // SSE2
// #include <pmmintrin.h> // SSE3
// #include <tmmintrin.h> // SSSE3
// #include <smmintrin.h> // SSE4.1
// #include <nmmintrin.h> // SSE4.2
// #include <ammintrin.h> // SSE4A
// #include <wmmintrin.h> // AES
#include <immintrin.h> // AVX, AVX2, FMA

// arm wmmx
// #include <mmintrin.h>

// arm neon
// #include <arm_neon.h>

// all, clang, gcc, icc
// #include <x86intrin.h>

// all, msvc
// #include <intrin.h>

//

// #if defined(_MSC_VER)
//      /* Microsoft C/C++-compatible compiler */
//      #include <intrin.h>
// #elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
//      /* GCC-compatible compiler, targeting x86/x86-64 */
//      #include <x86intrin.h>
// #elif defined(__GNUC__) && defined(__ARM_NEON__)
//      /* GCC-compatible compiler, targeting ARM with NEON */
//      #include <arm_neon.h>
// #elif defined(__GNUC__) && defined(__IWMMXT__)
//      /* GCC-compatible compiler, targeting ARM with WMMX */
//      #include <mmintrin.h>
// #elif (defined(__GNUC__) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
//      /* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
//      #include <altivec.h>
// #elif defined(__GNUC__) && defined(__SPE__)
//      /* GCC-compatible compiler, targeting PowerPC with SPE */
//      #include <spe.h>
// #endif

//

// +----------------+------------------------------------------------------------------------------------------+
// |     Header     |                                         Purpose                                          |
// +----------------+------------------------------------------------------------------------------------------+
// | x86intrin.h    | Everything, including non-vector x86 instructions like _rdtsc().                         |
// | mmintrin.h     | MMX (Pentium MMX!)                                                                       |
// | mm3dnow.h      | 3dnow! (K6-2) (deprecated)                                                               |
// | xmmintrin.h    | SSE + MMX (Pentium 3, Athlon XP)                                                         |
// | emmintrin.h    | SSE2 + SSE + MMX (Pentium 4, Athlon 64)                                                  |
// | pmmintrin.h    | SSE3 + SSE2 + SSE + MMX (Pentium 4 Prescott, Athlon 64 San Diego)                        |
// | tmmintrin.h    | SSSE3 + SSE3 + SSE2 + SSE + MMX (Core 2, Bulldozer)                                      |
// | popcntintrin.h | POPCNT (Nehalem (Core i7), Phenom)                                                       |
// | ammintrin.h    | SSE4A + SSE3 + SSE2 + SSE + MMX (AMD-only, starting with Phenom)                         |
// | smmintrin.h    | SSE4_1 + SSSE3 + SSE3 + SSE2 + SSE + MMX (Penryn, Bulldozer)                             |
// | nmmintrin.h    | SSE4_2 + SSE4_1 + SSSE3 + SSE3 + SSE2 + SSE + MMX (Nehalem (aka Core i7), Bulldozer)     |
// | wmmintrin.h    | AES (Core i7 Westmere, Bulldozer)                                                        |
// | immintrin.h    | AVX, AVX2, AVX512, all SSE+MMX (except SSE4A and XOP), popcnt, BMI/BMI2, FMA             |
// +----------------+------------------------------------------------------------------------------------------+

void zed_x64_init() {
	_MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
}
