/* This file is part of FineFramework project */
#ifndef FFW_VEC4
#define FFW_VEC4

#include <ostream>
#include <limits>
#include <cmath>

namespace ffw {
    /**
     * @ingroup graphics
     */
    template <class T> struct Vec4 {
    public:
        T x;
        T y;
        T z;
        T w;

        inline Vec4() {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }

        inline Vec4(T compx, T compy, T compz, T compw) {
            x = compx;
            y = compy;
            z = compz;
            w = compw;
        }

        inline Vec4(T val) {
            x = val;
            y = val;
            z = val;
            w = val;
        }

        inline Vec4(const Vec4<T>& vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
        }

        inline Vec4(const std::initializer_list<T>& list) {
            if (list.size() != 4) {
                x = 0;
                y = 0;
                z = 0;
                w = 0;
                return;
            }
            x = *(list.begin());
            y = *(list.begin() + 1);
            z = *(list.begin() + 2);
            w = *(list.begin() + 3);
        }

        inline void set(T compx, T compy, T compz, T compw) {
            x = compx;
            y = compy;
            z = compz;
            w = compw;
        }

        inline void set(T val) {
            x = val;
            y = val;
            z = val;
            w = val;
        }

        inline void set(const Vec4<T>& vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
        }

        inline void set(const std::initializer_list<T>& list) {
            if (list.size() != 4)return;
            x = *(list.begin());
            y = *(list.begin() + 1);
            z = *(list.begin() + 2);
            w = *(list.begin() + 3);
        }

        inline ffw::Vec4<T>  operator - () const {
            return Vec4<T>(-x, -y, -z, -w);
        }

        inline ffw::Vec4<T>& operator =  (const Vec4<T>& vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
            return *this;
        }

        inline ffw::Vec4<T>  operator +  (const Vec4<T>& vec) const {
            return Vec4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
        }

        inline ffw::Vec4<T>& operator += (const Vec4<T>& vec) {
            x += vec.x;
            y += vec.y;
            z += vec.z;
            w += vec.w;
            return *this;
        }

        inline ffw::Vec4<T>  operator -  (const Vec4<T>& vec) const {
            return Vec4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
        }

        inline ffw::Vec4<T>& operator -= (const Vec4<T>& vec) {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
            w -= vec.w;
            return *this;
        }

        inline ffw::Vec4<T>  operator /  (const Vec4<T>& vec) const {
            return Vec4<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
        }

        inline ffw::Vec4<T>& operator /= (const Vec4<T>& vec) {
            x /= vec.x;
            y /= vec.y;
            z /= vec.z;
            w /= vec.w;
            return *this;
        }

        inline ffw::Vec4<T>  operator *  (const Vec4<T>& vec) const {
            return Vec4<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
        }

        inline ffw::Vec4<T>& operator *= (const Vec4<T>& vec) {
            x *= vec.x;
            y *= vec.y;
            z *= vec.z;
            w *= vec.w;
            return *this;
        }

        inline ffw::Vec4<T>& operator =  (const T& val) {
            x = val;
            y = val;
            z = val;
            w = val;
            return *this;
        }

        inline ffw::Vec4<T>  operator +  (const T& val) const {
            return Vec4<T>(x + val, y + val, z + val, w + val);
        }

        inline ffw::Vec4<T>& operator += (const T& val) {
            x += val;
            y += val;
            z += val;
            w += val;
            return *this;
        }

        inline ffw::Vec4<T>  operator -  (const T& val) const {
            return Vec4<T>(x - val, y - val, z - val, w - val);
        }

        inline ffw::Vec4<T>& operator -= (const T& val) {
            x -= val;
            y -= val;
            z -= val;
            w -= val;
            return *this;
        }

        inline ffw::Vec4<T>  operator /  (const T& val) const {
            return Vec4<T>(x / val, y / val, z / val, w / val);
        }

        inline ffw::Vec4<T>& operator /= (const T& val) {
            x /= val;
            y /= val;
            z /= val;
            w /= val;
            return *this;
        }

        inline ffw::Vec4<T>  operator *  (const T& val) const {
            return Vec4<T>(x * val, y * val, z * val, w * val);
        }

        inline ffw::Vec4<T>& operator *= (const T& val) {
            x *= val;
            y *= val;
            z *= val;
            w *= val;
            return *this;
        }

        inline bool operator != (const Vec4<T>& vec) const {
            return !(*this == vec);
        }

        inline bool operator == (const Vec4<T>& vec) const {
            return (x == vec.x && y == vec.y && z == vec.z && w == vec.w);
        }

        inline ffw::Vec4<T>& normalize() {
            float l = sqrtf(x*x + y*y + z*z + w*w);
            if (l > 0) {
                x = x / l;
                y = y / l;
                z = z / l;
                w = w / l;
            }
            return *this;
        }

        inline ffw::Vec4<T>& scale(const T val) {
            x = x*val;
            y = y*val;
            z = z*val;
            w = w*val;
            return *this;
        }

        inline double length() const {
            return sqrt(static_cast<double>(x*x + y*y + z*z + w*w));
        }

        inline float lengthf() const {
            return sqrtf(static_cast<float>(x*x + y*y + z*z + w*w));
        }

        inline T lengthSqrd() const {
            return (x*x + y*y + z*z + w*w);
        }
        
        T& operator [] (size_t i){
            return ((T*)&x)[i];
        }

        const T& operator [] (size_t i) const  {
            return ((T*)&x)[i];
        }

        template <class S>
        inline operator ffw::Vec4<S>() const {
            return ffw::Vec4<S>((S)x, (S)y, (S)z, (S)w);
        }

        inline Vec4<T> round() const {
            return Vec4<T>(std::round(x), std::round(y), std::round(z), std::round(w));
        }

        inline Vec4<T> floor() const {
            return Vec4<T>(std::floor(x), std::floor(y), std::floor(z), std::floor(w));
        }

        inline Vec4<T> ceil() const {
            return Vec4<T>(std::ceil(x), std::ceil(y), std::ceil(z), std::ceil(w));
        }
    };
    /**
     * @ingroup graphics
     */
    typedef Vec4<float> Vec4f;
    /**
     * @ingroup graphics
     */
    typedef Vec4<int> Vec4i;
    /**
    * @ingroup graphics
    */
    typedef Vec4<short> Vec4s;
    /**
    * @ingroup graphics
    */
    typedef Vec4<long long> Vec4ll;
    /**
     * @ingroup graphics
     */
    typedef Vec4<double> Vec4d;
    /**
    * @ingroup graphics
    */
    template <class T>
    inline T dot(const ffw::Vec4<T>& V1, const ffw::Vec4<T>& V2) {
        return (V1.x*V2.x + V1.y*V2.y + V1.z*V2.z + V1.w*V2.w);
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline T distance(const Vec4<T>& v1, const Vec4<T>& v2) {
        auto v = v2 - v1;
        return static_cast<T>(v.length());
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline Vec4<T> middle(const Vec4<T>& v1, const Vec4<T>& v2) {
        auto v = (v2 - v1) / 2.0;
        return v1 + v;
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline ffw::Vec4<T> normalize(const Vec4<T>& vec) {
        auto copy = vec;
        copy.normalize();
        return copy;
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline std::ostream& operator << (std::ostream& os, const ffw::Vec4<T>& vec) {
        os << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
        return os;
    }
};
namespace ffw {
    template <>
    inline bool ffw::Vec4<float>::operator == (const Vec4<float>& vec) const {
        if (fabs(x - vec.x) > std::numeric_limits<float>::epsilon())return false;
        if (fabs(y - vec.y) > std::numeric_limits<float>::epsilon())return false;
        if (fabs(z - vec.z) > std::numeric_limits<float>::epsilon())return false;
        if (fabs(w - vec.w) > std::numeric_limits<float>::epsilon())return false;
        return true;
    }

    template <>
    inline bool ffw::Vec4<double>::operator == (const Vec4<double>& vec) const {
        if (fabs(x - vec.x) > std::numeric_limits<double>::epsilon())return false;
        if (fabs(y - vec.y) > std::numeric_limits<double>::epsilon())return false;
        if (fabs(z - vec.z) > std::numeric_limits<double>::epsilon())return false;
        if (fabs(w - vec.w) > std::numeric_limits<double>::epsilon())return false;
        return true;
    }
};
#endif
