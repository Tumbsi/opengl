#pragma once
#include <intrin.h>

#ifndef ffs
inline int ffs(int i) {
    if (i == 0) return 0;
    unsigned long idx;
    _BitScanForward(&idx, i);
    return (int)idx + 1;
}
#endif

#ifndef ffsll
inline int ffsll(long long i) {
    if (i == 0) return 0;
    unsigned long idx;
#if defined(_WIN64)
    _BitScanForward64(&idx, i);
#else
    _BitScanForward(&idx, (unsigned long)i);
#endif
    return (int)idx + 1;
}
#endif
