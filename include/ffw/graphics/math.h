/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_FUNCTIONS
#define FFW_GRAPHICS_FUNCTIONS

#include "config.h"
#include <algorithm>
#include "constants.h"

namespace ffw {
    /**
    * @ingroup graphics
    */
    template<class T>
    inline T clamp(const T val, const T min, const T max) {
        return std::max(min, std::min(val, max));
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline T lerp(const T& a, const T& b, float w) {
        return T(a*(1 - w) + b*w);
    }
    /**
    * @ingroup graphics
    */
    template<class T>
    inline T radians(const T val) {
        return static_cast<T>(val * DEG_TO_RAD);
    }
    /**
    * @ingroup graphics
    */
    template<class T>
    inline T degrees(const T val) {
        return static_cast<T>(val * RAD_TO_DEG);
    }
    /**
    * @ingroup graphics
    */
    template<typename T>
    inline T remap(const T value, const T inMin, const T inMax, const T outMin, const T outMax) {
        return (value - inMin)*(outMax - outMin) / (inMax - inMin) + outMin;
    }
    /**
    * @ingroup graphics
    */
    inline unsigned long nextPowOfTwo(const unsigned long value) {
        unsigned long p = 1;
        while (p < value) {
            p *= 2;
        }
        return p;
    }

#ifdef FFW_WINDOWS_MSVC
    /**
    * @ingroup graphics
    */
    inline unsigned short byteSwap16(const unsigned short value) {
        return _byteswap_ushort(value);
    }
    /**
    * @ingroup graphics
    */
    inline unsigned long byteSwap32(const unsigned long value) {
        return _byteswap_ulong(value);
    }
    /**
    * @ingroup graphics
    */
    inline unsigned long long byteSwap64(const unsigned long long value) {
        return _byteswap_uint64(value);
    }
#else
    /**
    * @ingroup graphics
    */
    inline unsigned short byteSwap16(const unsigned short value) {
        return __builtin_bswap16(value);
    }
    /**
    * @ingroup graphics
    */
    inline unsigned long byteSwap32(const unsigned long value) {
        return __builtin_bswap32(value);
    }
    /**
    * @ingroup graphics
    */
    inline unsigned long long byteSwap64(const unsigned long long value) {
        return __builtin_bswap64(value);
    }
#endif
};
#endif
