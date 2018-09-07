/* This file is part of FineFramework project */
#ifndef FFW_VEC_X
#define FFW_VEC_X

#include <ostream>
#include <array>
#include <cmath>
#include "config.h"

namespace ffw{
    template<class T, size_t S>
    class Vec {
    public:
        Vec() {
            for(size_t i = 0; i < S; i++) {
                arr[i] = (T)0;
            }
        }

        Vec(T val) {
            for (size_t i = 0; i < S; i++) {
                arr[i] = val;
            }
        }

        Vec(const std::initializer_list<T>& list) {
            if (S == list.size()) {
                for (size_t i = 0; i < S; i++) {
                    arr[i] = *(list.begin() + i);
                }
            } else {
                for (size_t i = 0; i < S; i++) {
                    arr[i] = (T)0;
                }
            }
        }

        Vec(const Vec<T, S>& other):arr(other.arr) {
        }

        Vec(Vec<T, S>&& other) NOEXCEPT :arr(std::move(other.arr)) {
        }

        void set(T val) {
            for (size_t i = 0; i < S; i++) {
                arr[i] = val;
            }
        }

        void set(const std::initializer_list<T>& list) {
            if (S == list.size()) {
                for (size_t i = 0; i < S; i++) {
                    arr[i] = *(list.begin() + i);
                }
            }
        }

        void set(const Vec<T, S>& other) {
            arr = other.arr;
        }

        ffw::Vec<T, S>  operator - () const {
            auto copy = *this;
            for(size_t i = 0; i < S; i++) {
                copy.arr[i] = -arr[i];
            }
            return copy;
        }

        ffw::Vec<T, S>& operator =  (const Vec<T, S>& vec) {
            for (size_t i = 0; i < S; i++) {
                arr[i] = vec.arr[i];
            }
            return *this;
        }

        ffw::Vec<T, S>  operator +  (const Vec<T, S>& vec) const {
            auto copy = *this;
            for (size_t i = 0; i < S; i++) {
                copy.arr[i] += vec.arr[i];
            }
            return copy;
        }

        ffw::Vec<T, S>& operator += (const Vec<T, S>& vec) {
            for (size_t i = 0; i < S; i++) {
                arr[i] += vec.arr[i];
            }
            return *this;
        }

        ffw::Vec<T, S>  operator -  (const Vec<T, S>& vec) const {
            auto copy = *this;
            for (size_t i = 0; i < S; i++) {
                copy.arr[i] -= vec.arr[i];
            }
            return copy;
        }

        ffw::Vec<T, S>& operator -= (const Vec<T, S>& vec) {
            for (size_t i = 0; i < S; i++) {
                arr[i] -= vec.arr[i];
            }
            return *this;
        }

        ffw::Vec<T, S>  operator /  (const Vec<T, S>& vec) const {
            auto copy = *this;
            for (size_t i = 0; i < S; i++) {
                copy.arr[i] /= vec.arr[i];
            }
            return copy;
        }

        ffw::Vec<T, S>& operator /= (const Vec<T, S>& vec) {
            for (size_t i = 0; i < S; i++) {
                arr[i] /= vec.arr[i];
            }
            return *this;
        }

        ffw::Vec<T, S>  operator *  (const Vec<T, S>& vec) const {
            auto copy = *this;
            for (size_t i = 0; i < S; i++) {
                copy.arr[i] *= vec.arr[i];
            }
            return copy;
        }

        ffw::Vec<T, S>& operator *= (const Vec<T, S>& vec) {
            for (size_t i = 0; i < S; i++) {
                arr[i] *= vec.arr[i];
            }
            return *this;
        }

        ffw::Vec<T, S>& operator =  (const T& val) {
            for (size_t i = 0; i < S; i++) {
                arr[i] = val;
            }
            return *this;
        }

        ffw::Vec<T, S>  operator +  (const T& val) const {
            auto copy = *this;
            for (size_t i = 0; i < S; i++) {
                copy.arr[i] += val;
            }
            return copy;
        }

        ffw::Vec<T, S>& operator += (const T& val) {
            for (size_t i = 0; i < S; i++) {
                arr[i] += val;
            }
            return *this;
        }

        ffw::Vec<T, S>  operator -  (const T& val) const {
            auto copy = *this;
            for (size_t i = 0; i < S; i++) {
                copy.arr[i] -= val;
            }
            return copy;
        }

        ffw::Vec<T, S>& operator -= (const T& val) {
            for (size_t i = 0; i < S; i++) {
                arr[i] -= val;
            }
            return *this;
        }

        ffw::Vec<T, S>  operator /  (const T& val) const {
            auto copy = *this;
            for (size_t i = 0; i < S; i++) {
                copy.arr[i] /= val;
            }
            return copy;
        }

        ffw::Vec<T, S>& operator /= (const T& val) {
            for (size_t i = 0; i < S; i++) {
                arr[i] /= val;
            }
            return *this;
        }

        ffw::Vec<T, S>  operator *  (const T& val) const {
            auto copy = *this;
            for (size_t i = 0; i < S; i++) {
                copy.arr[i] *= val;
            }
            return copy;
        }

        ffw::Vec<T, S>& operator *= (const T& val) {
            for (size_t i = 0; i < S; i++) {
                arr[i] *= val;
            }
            return *this;
        }

        bool operator != (const Vec<T, S>& vec) const {
            return !(*this == vec);
        }

        bool operator == (const Vec<T, S>& vec) const {
            for(size_t i = 0; i < S; i++) {
                if (arr[i] != vec.arr[i])return false;
            }
            return true;
        }

        ffw::Vec<T, S>& normalize() {
            double l = 0.0;
            for(size_t i = 0; i < S; i++) {
                l += arr[i] * arr[i];
            }
            l = sqrt(l);
            for(size_t i = 0; i < S; i++) {
                arr[i] = T(arr[i] / l);
            }
            return *this;
        }

        ffw::Vec<T, S>& scale(T factor) {
            for (size_t i = 0; i < S; i++) {
                arr[i] = arr[i] * factor;
            }
            return *this;
        }

        float lengthf() const {
            return sqrtf(lengthSqrd());
        }

        double length() const {
            return sqrt(lengthSqrd());
        }

        T lengthSqrd() const {
            T val = (T)0;
            for (size_t i = 0; i < S; i++) {
                val += arr[i] * arr[i];
            }
            return val;
        }

        T& operator [] (size_t i){
            return arr[i];
        }

        const T& operator [] (size_t i) const  {
            return arr[i];
        }

        template <class X>
        operator ffw::Vec<X, S>() const {
            Vec<X, S> copy;
            for(size_t i = 0; i < S; i++) {
                copy.arr[i] = static_cast<X>(arr[i]);
            }
            return copy;
        }

        inline Vec<T, S> round() const {
            Vec<T, S> ret;
            for (size_t i = 0; i < S; i++) {
                ret[i] = std::round(arr[i]);
            }
            return ret;
        }

        inline Vec<T, S> floor() const {
            Vec<T, S> ret;
            for (size_t i = 0; i < S; i++) {
                ret[i] = std::floor(arr[i]);
            }
            return ret;
        }

        inline Vec<T, S> ceil() const {
            Vec<T, S> ret;
            for (size_t i = 0; i < S; i++) {
                ret[i] = std::ceil(arr[i]);
            }
            return ret;
        }

        std::array<T, S> arr;
    };
    /**
    * @ingroup graphics
    */
    template <class T, size_t S>
    inline T dot(const ffw::Vec<T, S>& V1, const ffw::Vec<T, S>& V2) {
        T ret = 0;
        for(size_t i = 0; i < S; i++){
            ret += V1[i] * V2[i];
        }
        return ret;
    }
    /**
    * @ingroup graphics
    */
    template <class T, size_t S>
    inline T distance(const Vec<T, S>& v1, const Vec<T, S>& v2) {
        return static_cast<T>(ffw::Vec<T, S>(v2 - v1).length());
    }
    /**
    * @ingroup graphics
    */
    template <class T, size_t S>
    inline Vec<T, S> middle(const Vec<T, S>& v1, const Vec<T, S>& v2) {
        return ffw::Vec<T, S>((v1 + v2) / 2);
    }
    /**
    * @ingroup graphics
    */
    template <class T, size_t S>
    inline ffw::Vec<T, S> normalize(const Vec<T, S>& vec) {
        return ffw::Vec<T, S>(vec).normalize();
    }
    /**
    * @ingroup graphics
    */
    template <class T, size_t S>
    inline std::ostream& operator << (std::ostream& os, const ffw::Vec<T, S>& vec) {
        os << vec[0];
        for(size_t i = 1; i < S; i++){
            os << ", " << vec[i];
        }
        return os;
    }
};
#endif
