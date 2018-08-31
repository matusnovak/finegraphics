/* This file is part of FineFramework project */
#ifndef FFW_MAT3X3
#define FFW_MAT3X3

#include "vec3.h"
#include "quaternion.h"

namespace ffw {
    /**
     * @ingroup graphics
     */
    template <class T> struct Mat3x3 {
    public:
        T ptr[9];

        inline Mat3x3() {
            ptr[0] = 1.0f;  ptr[3] = 0.0f;  ptr[6] = 0.0f;
            ptr[1] = 0.0f;  ptr[4] = 1.0f;  ptr[7] = 0.0f;
            ptr[2] = 0.0f;  ptr[5] = 0.0f;  ptr[8] = 1.0f;
        }

        inline Mat3x3(T xx, T yx, T zx,
            T xy, T yy, T zy,
            T xz, T yz, T zz) {
            ptr[0] = xx;    ptr[3] = yx;    ptr[6] = zx;
            ptr[1] = xy;    ptr[4] = yy;    ptr[7] = zy;
            ptr[2] = xz;    ptr[5] = yz;    ptr[8] = zz;
        }

        inline Mat3x3(T val) {
            ptr[0] = val;   ptr[3] = 0.0f;  ptr[6] = 0.0f;
            ptr[1] = 0.0f;  ptr[4] = val;   ptr[7] = 0.0f;
            ptr[2] = 0.0f;  ptr[5] = 0.0f;  ptr[8] = val;
        }

        inline Mat3x3(std::initializer_list<T> list) {
            if (list.size() != 9) {
                ptr[0] = 1.0f;  ptr[3] = 0.0f;  ptr[6] = 0.0f;
                ptr[1] = 0.0f;  ptr[4] = 1.0f;  ptr[7] = 0.0f;
                ptr[2] = 0.0f;  ptr[5] = 0.0f;  ptr[8] = 1.0f;
                return;
            }
            for (int i = 0; i < 9; i++) {
                ptr[i] = *(list.begin() + i);
            }
        }

        inline void set(T xx, T yx, T zx,
            T xy, T yy, T zy,
            T xz, T yz, T zz) {
            ptr[0] = xx;    ptr[3] = yx;    ptr[6] = zx;
            ptr[1] = xy;    ptr[4] = yy;    ptr[7] = zy;
            ptr[2] = xz;    ptr[5] = yz;    ptr[8] = zz;
        }

        inline void set(T val) {
            ptr[0] = val;   ptr[3] = 0.0f;  ptr[6] = 0.0f;
            ptr[1] = 0.0f;  ptr[4] = val;   ptr[7] = 0.0f;
            ptr[2] = 0.0f;  ptr[5] = 0.0f;  ptr[8] = val;
        }

        inline void set(T m[9]) {
            std::memcpy(ptr, m, sizeof(T) * 9);
        }

        inline void set(std::initializer_list<T> list) {
            if (list.size() != 9) {
                return;
            }
            for (int i = 0; i < 9; i++) {
                ptr[i] = *(list.begin() + i);
            }
        }

        inline T* getPtr() {
            return &ptr[0];
        }

        inline const T* getPtr() const {
            return &ptr[0];
        }

        inline ffw::Mat3x3<T>& operator = (const ffw::Mat3x3<T> &m) {
            ptr[0] = m.ptr[0];  ptr[3] = m.ptr[3];  ptr[6] = m.ptr[6];
            ptr[1] = m.ptr[1];  ptr[4] = m.ptr[4];  ptr[7] = m.ptr[7];
            ptr[2] = m.ptr[2];  ptr[5] = m.ptr[5];  ptr[8] = m.ptr[8];
            return *this;
        }

        inline ffw::Mat3x3<T> operator + (const ffw::Mat3x3<T> &m) const {
            Mat3x3 r;
            r.ptr[0] = ptr[0] + m.ptr[0];
            r.ptr[1] = ptr[1] + m.ptr[1];
            r.ptr[2] = ptr[2] + m.ptr[2];

            r.ptr[3] = ptr[3] + m.ptr[3];
            r.ptr[4] = ptr[4] + m.ptr[4];
            r.ptr[5] = ptr[5] + m.ptr[5];

            r.ptr[6] = ptr[6] + m.ptr[6];
            r.ptr[7] = ptr[7] + m.ptr[7];
            r.ptr[8] = ptr[8] + m.ptr[8];
            return r;
        }

        inline ffw::Mat3x3<T>&  operator += (const ffw::Mat3x3<T> &m) {
            ptr[0] += m.ptr[0];
            ptr[1] += m.ptr[1];
            ptr[2] += m.ptr[2];

            ptr[3] += m.ptr[3];
            ptr[4] += m.ptr[4];
            ptr[5] += m.ptr[5];

            ptr[6] += m.ptr[6];
            ptr[7] += m.ptr[7];
            ptr[8] += m.ptr[8];
            return *this;
        }

        inline ffw::Mat3x3<T> operator - (const ffw::Mat3x3<T> &m) const {
            Mat3x3 r;
            r.ptr[0] = ptr[0] - m.ptr[0];
            r.ptr[1] = ptr[1] - m.ptr[1];
            r.ptr[2] = ptr[2] - m.ptr[2];

            r.ptr[3] = ptr[3] - m.ptr[3];
            r.ptr[4] = ptr[4] - m.ptr[4];
            r.ptr[5] = ptr[5] - m.ptr[5];

            r.ptr[6] = ptr[6] - m.ptr[6];
            r.ptr[7] = ptr[7] - m.ptr[7];
            r.ptr[8] = ptr[8] - m.ptr[8];
            return r;
        }

        inline ffw::Mat3x3<T>&  operator -= (const ffw::Mat3x3<T> &m) {
            ptr[0] -= m.ptr[0];
            ptr[1] -= m.ptr[1];
            ptr[2] -= m.ptr[2];

            ptr[3] -= m.ptr[3];
            ptr[4] -= m.ptr[4];
            ptr[5] -= m.ptr[5];

            ptr[6] -= m.ptr[6];
            ptr[7] -= m.ptr[7];
            ptr[8] -= m.ptr[8];
            return *this;
        }

        inline ffw::Mat3x3<T> operator * (const ffw::Mat3x3<T> &m) const {
            Mat3x3 r;
            r.ptr[0] = ptr[0] * m.ptr[0] + ptr[3] * m.ptr[1] + ptr[6] * m.ptr[2];
            r.ptr[1] = ptr[1] * m.ptr[0] + ptr[4] * m.ptr[1] + ptr[7] * m.ptr[2];
            r.ptr[2] = ptr[2] * m.ptr[0] + ptr[5] * m.ptr[1] + ptr[8] * m.ptr[2];

            r.ptr[3] = ptr[0] * m.ptr[3] + ptr[3] * m.ptr[4] + ptr[6] * m.ptr[5];
            r.ptr[4] = ptr[1] * m.ptr[3] + ptr[4] * m.ptr[4] + ptr[7] * m.ptr[5];
            r.ptr[5] = ptr[2] * m.ptr[3] + ptr[5] * m.ptr[4] + ptr[8] * m.ptr[5];

            r.ptr[6] = ptr[0] * m.ptr[6] + ptr[3] * m.ptr[7] + ptr[6] * m.ptr[8];
            r.ptr[7] = ptr[1] * m.ptr[6] + ptr[4] * m.ptr[7] + ptr[7] * m.ptr[8];
            r.ptr[8] = ptr[2] * m.ptr[6] + ptr[5] * m.ptr[7] + ptr[8] * m.ptr[8];
            return r;
        }

        inline ffw::Mat3x3<T>&  operator *= (const ffw::Mat3x3<T> &m) {
            *this = *this * m;
            return *this;
        }

        template <class S>
        inline ffw::Vec3<S> operator * (const ffw::Vec3<S>& v) const {
            ffw::Vec3f r;
            r.x = v.x*ptr[0] + v.y*ptr[3] + v.z*ptr[6];
            r.y = v.x*ptr[1] + v.y*ptr[4] + v.z*ptr[7];
            r.z = v.x*ptr[2] + v.y*ptr[5] + v.z*ptr[8];
            return r;
        }

        inline T& operator [] (int x) {
            return ptr[x];
        }

        inline const T& operator [] (int x) const {
            return ptr[x];
        }

        inline ffw::Mat3x3<T>& rotate(const ffw::Quaternion<T>& q) {
            // Taken from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
            auto sqw = q.w*q.w;
            auto sqx = q.x*q.x;
            auto sqy = q.y*q.y;
            auto sqz = q.z*q.z;

            // invs (inverse square length) is only required if quaternion is not already normalised
            auto invs = T(1) / (sqx + sqy + sqz + sqw);
            ptr[0] = (sqx - sqy - sqz + sqw)*invs; // since sqw + sqx + sqy + sqz =1/invs*invs
            ptr[4] = (-sqx + sqy - sqz + sqw)*invs;
            ptr[8] = (-sqx - sqy + sqz + sqw)*invs;

            auto tmp1 = q.x*q.y;
            auto tmp2 = q.z*q.w;
            ptr[1] = T(2.0) * (tmp1 + tmp2)*invs;
            ptr[3] = T(2.0) * (tmp1 - tmp2)*invs;

            tmp1 = q.x*q.z;
            tmp2 = q.y*q.w;
            ptr[2] = T(2.0) * (tmp1 - tmp2)*invs;
            ptr[6] = T(2.0) * (tmp1 + tmp2)*invs;
            tmp1 = q.y*q.z;
            tmp2 = q.x*q.w;
            ptr[5] = T(2.0) * (tmp1 + tmp2)*invs;
            ptr[7] = T(2.0) * (tmp1 - tmp2)*invs;

            return *this;
        }

        inline ffw::Mat3x3<T>& scale(T x, T y, T z) {
            Mat3x3 m;
            m[0] = x;
            m[5] = y;
            m[10] = z;
            (*this) *= m;
            return *this;
        }

        inline ffw::Mat3x3<T>& transpose() {
            std::swap(ptr[1], ptr[3]);
            std::swap(ptr[2], ptr[6]);
            std::swap(ptr[5], ptr[7]);
            return *this;
        }

        inline T determinant() const {
            T det =
                ptr[0] * (ptr[4] * ptr[8] - ptr[5] * ptr[7]) -
                ptr[3] * (ptr[1] * ptr[8] - ptr[7] * ptr[2]) +
                ptr[6] * (ptr[1] * ptr[5] - ptr[4] * ptr[2]);
            return det;
        }

        inline ffw::Mat3x3<T>& inverse() {
            T det = 1 / determinant();

            T inv[9];
            inv[0] = ptr[4] * ptr[8] - ptr[5] * ptr[7];
            inv[3] = ptr[6] * ptr[5] - ptr[3] * ptr[8];
            inv[6] = ptr[3] * ptr[7] - ptr[6] * ptr[4];
            inv[1] = ptr[7] * ptr[2] - ptr[1] * ptr[8];
            inv[4] = ptr[0] * ptr[8] - ptr[6] * ptr[2];
            inv[7] = ptr[1] * ptr[6] - ptr[0] * ptr[7];
            inv[2] = ptr[1] * ptr[5] - ptr[2] * ptr[4];
            inv[5] = ptr[2] * ptr[3] - ptr[0] * ptr[5];
            inv[8] = ptr[0] * ptr[4] - ptr[1] * ptr[3];
            for (int i = 0; i < 9; i++)ptr[i] = inv[i] * det;
            return *this;
        }
    };
    /**
     * @ingroup graphics
     */
    typedef Mat3x3<float> Mat3x3f;
    /**
     * @ingroup graphics
     */
    typedef Mat3x3<double> Mat3x3d;
    /**
     * @ingroup graphics
     */
    typedef Mat3x3<int> Mat3x3i;
};
#endif
