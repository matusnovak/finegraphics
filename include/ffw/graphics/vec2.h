/* This file is part of FineFramework project */
#ifndef FFW_VEC2
#define FFW_VEC2

#include <ostream>
#include <limits>
#include <cmath>
#include "constants.h"

namespace ffw {
    /**
     * @ingroup graphics
     */
    template <class T> struct Vec2 {
    public:
        T x;
        T y;

        inline Vec2() {
            x = T(0);
            y = T(0);
        }

        inline Vec2(T compx, T compy) {
            x = compx;
            y = compy;
        }

        inline Vec2(T Value) {
            x = Value;
            y = Value;
        }

        inline Vec2(const Vec2<T>& vec) {
            x = vec.x;
            y = vec.y;
        }

        inline Vec2(std::initializer_list<T> list) {
            if (list.size() != 2) {
                x = T(0);
                y = T(0);
                return;
            }
            x = *(list.begin());
            y = *(list.begin() + 1);
        }

        inline void set(T compx, T compy) {
            x = compx;
            y = compy;
        }

        inline void set(T Value) {
            x = Value;
            y = Value;
        }

        inline void set(const Vec2<T>& vec) {
            x = vec.x;
            y = vec.y;
        }

        inline void set(const std::initializer_list<T>& list) {
            if (list.size() == 2) {
                x = *(list.begin());
                y = *(list.begin() + 1);
            }
        }

        inline ffw::Vec2<T>  operator - () const {
            return Vec2<T>(-x, -y);
        }

        inline ffw::Vec2<T>& operator =  (const Vec2<T>& vec) {
            x = vec.x;
            y = vec.y;
            return *this;
        }

        inline ffw::Vec2<T>  operator +  (const Vec2<T>& vec) const {
            return Vec2<T>(x + vec.x, y + vec.y);
        }

        inline ffw::Vec2<T>& operator += (const Vec2<T>& vec) {
            x += vec.x;
            y += vec.y;
            return *this;
        }

        inline ffw::Vec2<T>  operator -  (const Vec2<T>& vec) const {
            return Vec2<T>(x - vec.x, y - vec.y);
        }

        inline ffw::Vec2<T>& operator -= (const Vec2<T>& vec) {
            x -= vec.x;
            y -= vec.y;
            return *this;
        }

        inline ffw::Vec2<T>  operator /  (const Vec2<T>& vec) const {
            return Vec2<T>(x / vec.x, y / vec.y);
        }

        inline ffw::Vec2<T>& operator /= (const Vec2<T>& vec) {
            x /= vec.x;
            y /= vec.y;
            return *this;
        }

        inline ffw::Vec2<T>  operator *  (const Vec2<T>& vec) const {
            return Vec2<T>(x * vec.x, y * vec.y);
        }

        inline ffw::Vec2<T>& operator *= (const Vec2<T>& vec) {
            x *= vec.x;
            y *= vec.y;
            return *this;
        }

        inline ffw::Vec2<T>& operator =  (const T& val) {
            x = val;
            y = val;
            return *this;
        }

        inline ffw::Vec2<T>  operator +  (const T& val) const {
            return Vec2<T>(x + val, y + val);
        }

        inline ffw::Vec2<T>& operator += (const T& val) {
            x += val;
            y += val;
            return *this;
        }

        inline ffw::Vec2<T>  operator -  (const T& val) const {
            return Vec2<T>(x - val, y - val);
        }

        inline ffw::Vec2<T>& operator -= (const T& val) {
            x -= val;
            y -= val;
            return *this;
        }

        inline ffw::Vec2<T>  operator /  (const T& val) const {
            return Vec2<T>(x / val, y / val);
        }

        inline ffw::Vec2<T>& operator /= (const T& val) {
            x /= val;
            y /= val;
            return *this;
        }

        inline ffw::Vec2<T>  operator *  (const T& val) const {
            return Vec2<T>(x * val, y * val);
        }

        inline ffw::Vec2<T>& operator *= (const T& val) {
            x *= val;
            y *= val;
            return *this;
        }

        inline bool operator != (const Vec2<T>& vec) const {
            return !(*this == vec);
        }

        inline bool operator == (const Vec2<T>& vec) const {
            return (x == vec.x && y == vec.y);
        }

        inline ffw::Vec2<T>& rotate(const double deg) {
            auto v = *this;
            x = T(v.x*std::cos(deg*DEG_TO_RAD) - v.y*std::sin(deg*DEG_TO_RAD));
            y = T(v.x*std::sin(deg*DEG_TO_RAD) + v.y*std::cos(deg*DEG_TO_RAD));
            return *this;
        }

        inline ffw::Vec2<T>& rotateRad(const double rad) {
            auto v = *this;
            x = T(v.x*std::cos(rad) - v.y*std::sin(rad));
            y = T(v.x*std::sin(rad) + v.y*std::cos(rad));
            return *this;
        }

        inline ffw::Vec2<T>& normalize() {
            const auto l = sqrtf(x*x + y*y);
            if (l > 0) {
                x = T(x / l);
                y = T(y / l);
            }
            return *this;
        }

        inline ffw::Vec2<T>& scale(T val) {
            x = x*val;
            y = y*val;
            return *this;
        }

        inline double length() const {
            return sqrt(static_cast<double>(x*x + y*y));
        }

        inline float lengthf() const {
            return sqrtf(static_cast<float>(x*x + y*y));
        }

        inline T lengthSqrd() const {
            return (x*x + y*y);
        }
        
        T& operator [] (size_t i){
            return ((T*)&x)[i];
        }

        const T& operator [] (size_t i) const  {
            return ((T*)&x)[i];
        }

        template <class S>
        inline operator ffw::Vec2<S>() const {
            return ffw::Vec2<S>(S(x), S(y));
        }

        inline Vec2<T> round() const {
            return Vec2<T>(std::round(x), std::round(y));
        }

        inline Vec2<T> floor() const {
            return Vec2<T>(std::floor(x), std::floor(y));
        }

        inline Vec2<T> ceil() const {
            return Vec2<T>(std::ceil(x), std::ceil(y));
        }
    };
    /**
     * @ingroup graphics
     */
    typedef Vec2<float> Vec2f;
    /**
     * @ingroup graphics
     */
    typedef Vec2<int> Vec2i;
    /**
    * @ingroup graphics
    */
    typedef Vec2<short> Vec2s;
    /**
    * @ingroup graphics
    */
    typedef Vec2<long long> Vec2ll;
    /**
     * @ingroup graphics
     */
    typedef Vec2<double> Vec2d;
    /**
    * @ingroup graphics
    */
    template <class T>
    inline T dot(const ffw::Vec2<T>& v1, const ffw::Vec2<T>& v2) {
        return (v1.x*v2.x + v1.y*v2.y);
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline T distance(const Vec2<T>& v1, const Vec2<T>& v2) {
        auto v = v2 - v1;
        return static_cast<T>(v.length());
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline Vec2<T> middle(const Vec2<T>& v1, const Vec2<T>& v2) {
        auto v = (v2 - v1) / 2.0;
        return v1 + v;
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline ffw::Vec2<T> normalize(const Vec2<T>& vec) {
        auto copy = vec;
        copy.normalize();
        return copy;
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline double angle(const ffw::Vec2<T>& v1, const ffw::Vec2<T>& v2) {
        const auto dot = (v1.x*v2.x + v1.y*v2.y);
        const auto v1Length = std::sqrt(v1.x*v1.x + v1.y*v1.y);
        const auto v2Length = std::sqrt(v2.x*v2.x + v2.y*v2.y);
        return static_cast<double>(std::acos(dot / (v1Length*v2Length))*RAD_TO_DEG);
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline double angleRad(const ffw::Vec2<T>& v1, const ffw::Vec2<T>& v2) {
        const auto dot = (v1.x*v2.x + v1.y*v2.y);
        const auto v1Length = std::sqrt(v1.x*v1.x + v1.y*v1.y);
        const auto v2Length = std::sqrt(v2.x*v2.x + v2.y*v2.y);
        return static_cast<double>(std::acos(dot / (v1Length*v2Length)));
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline std::ostream& operator << (std::ostream& os, const ffw::Vec2<T>& vec) {
        os << vec.x << ", " << vec.y;
        return os;
    }
};

namespace ffw {
    template<>
    inline bool ffw::Vec2<float>::operator == (const Vec2<float>& vec) const {
        if (fabs(x - vec.x) > std::numeric_limits<float>::epsilon())return false;
        if (fabs(y - vec.y) > std::numeric_limits<float>::epsilon())return false;
        return true;
    }
    template<>
    inline bool ffw::Vec2<double>::operator == (const Vec2<double>& vec) const {
        if (fabs(x - vec.x) > std::numeric_limits<double>::epsilon())return false;
        if (fabs(y - vec.y) > std::numeric_limits<double>::epsilon())return false;
        return true;
    }
}

#endif
