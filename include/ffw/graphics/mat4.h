/* This file is part of FineFramework project */
#ifndef FFW_MAT4X4
#define FFW_MAT4X4

#include "vec4.h"
#include "vec3.h"
#include "quaternion.h"

namespace ffw {
    /**
     * @ingroup graphics
     */
    template <class T> struct Mat4x4 {
    public:
        T ptr[16];

        inline Mat4x4() {
            ptr[0] = 1.0f;  ptr[4] = 0.0f;  ptr[8] = 0.0f; ptr[12] = 0.0f;
            ptr[1] = 0.0f;  ptr[5] = 1.0f;  ptr[9] = 0.0f; ptr[13] = 0.0f;
            ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = 1.0f; ptr[14] = 0.0f;
            ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = 1.0f;
        }

        inline Mat4x4(T xx, T yx, T zx, T wx,
            T xy, T yy, T zy, T wy,
            T xz, T yz, T zz, T wz,
            T xw, T yw, T zw, T ww) {
            ptr[0] = xx;    ptr[4] = yx;    ptr[8] = zx;   ptr[12] = wx;
            ptr[1] = xy;    ptr[5] = yy;    ptr[9] = zy;   ptr[13] = wy;
            ptr[2] = xz;    ptr[6] = yz;    ptr[10] = zz;   ptr[14] = wz;
            ptr[3] = xw;    ptr[7] = yw;    ptr[11] = zw;   ptr[15] = ww;
        }

        inline Mat4x4(T val) {
            ptr[0] = val;   ptr[4] = 0.0f;  ptr[8] = 0.0f; ptr[12] = 0.0f;
            ptr[1] = 0.0f;  ptr[5] = val;   ptr[9] = 0.0f; ptr[13] = 0.0f;
            ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = val;  ptr[14] = 0.0f;
            ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = val;
        }

        inline Mat4x4(std::initializer_list<T> list) {
            if (list.size() != 16) {
                ptr[0] = 1.0f;  ptr[4] = 0.0f;  ptr[8] = 0.0f; ptr[12] = 0.0f;
                ptr[1] = 0.0f;  ptr[5] = 1.0f;  ptr[9] = 0.0f; ptr[13] = 0.0f;
                ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = 1.0f; ptr[14] = 0.0f;
                ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = 1.0f;
                return;
            }
            for (int i = 0; i < 16; i++) {
                ptr[i] = *(list.begin() + i);
            }
        }

        inline void set(T xx, T yx, T zx, T wx,
            T xy, T yy, T zy, T wy,
            T xz, T yz, T zz, T wz,
            T xw, T yw, T zw, T ww) {
            ptr[0] = xx;    ptr[4] = yx;    ptr[8] = zx;   ptr[12] = wx;
            ptr[1] = xy;    ptr[5] = yy;    ptr[9] = zy;   ptr[13] = wy;
            ptr[2] = xz;    ptr[6] = yz;    ptr[10] = zz;   ptr[14] = wz;
            ptr[3] = xw;    ptr[7] = yw;    ptr[11] = zw;   ptr[15] = ww;
        }

        inline void set(T val) {
            ptr[0] = val;   ptr[4] = 0.0f;  ptr[8] = 0.0f; ptr[12] = 0.0f;
            ptr[1] = 0.0f;  ptr[5] = val;   ptr[9] = 0.0f; ptr[13] = 0.0f;
            ptr[2] = 0.0f;  ptr[6] = 0.0f;  ptr[10] = val;  ptr[14] = 0.0f;
            ptr[3] = 0.0f;  ptr[7] = 0.0f;  ptr[11] = 0.0f; ptr[15] = val;
        }

        inline void set(T m[16]) {
            ptr[0] = m[0];    ptr[4] = m[4];    ptr[8] = m[8];   ptr[12] = m[12];
            ptr[1] = m[1];    ptr[5] = m[5];    ptr[9] = m[9];   ptr[13] = m[13];
            ptr[2] = m[2];    ptr[6] = m[6];    ptr[10] = m[10];  ptr[14] = m[14];
            ptr[3] = m[3];    ptr[7] = m[7];    ptr[11] = m[11];  ptr[15] = m[15];
        }

        inline void set(std::initializer_list<T> list) {
            if (list.size() != 16) {
                return;
            }
            for (int i = 0; i < 16; i++) {
                ptr[i] = *(list.begin() + i);
            }
        }

        inline T* getPtr() {
            return &ptr[0];
        }

        inline const T* getPtr() const {
            return &ptr[0];
        }

        inline ffw::Mat4x4<T>& operator = (const ffw::Mat4x4<T> &m) {
            ptr[0] = m.ptr[0];  ptr[4] = m.ptr[4];  ptr[8] = m.ptr[8];     ptr[12] = m.ptr[12];
            ptr[1] = m.ptr[1];  ptr[5] = m.ptr[5];  ptr[9] = m.ptr[9];     ptr[13] = m.ptr[13];
            ptr[2] = m.ptr[2];  ptr[6] = m.ptr[6];  ptr[10] = m.ptr[10];    ptr[14] = m.ptr[14];
            ptr[3] = m.ptr[3];  ptr[7] = m.ptr[7];  ptr[11] = m.ptr[11];    ptr[15] = m.ptr[15];
            return *this;
        }

        inline ffw::Mat4x4<T> operator + (const ffw::Mat4x4<T> &m) const {
            Mat4x4 r;
            r.ptr[0] = ptr[0] + m.ptr[0];
            r.ptr[1] = ptr[1] + m.ptr[1];
            r.ptr[2] = ptr[2] + m.ptr[2];
            r.ptr[3] = ptr[3] + m.ptr[3];

            r.ptr[4] = ptr[4] + m.ptr[4];
            r.ptr[5] = ptr[5] + m.ptr[5];
            r.ptr[6] = ptr[6] + m.ptr[6];
            r.ptr[7] = ptr[7] + m.ptr[7];

            r.ptr[8] = ptr[8] + m.ptr[8];
            r.ptr[9] = ptr[9] + m.ptr[9];
            r.ptr[10] = ptr[10] + m.ptr[10];
            r.ptr[11] = ptr[11] + m.ptr[11];

            r.ptr[12] = ptr[12] + m.ptr[12];
            r.ptr[13] = ptr[13] + m.ptr[13];
            r.ptr[14] = ptr[14] + m.ptr[14];
            r.ptr[15] = ptr[15] + m.ptr[15];
            return r;
        }

        inline ffw::Mat4x4<T>&  operator += (const ffw::Mat4x4<T> &m) {
            ptr[0] += m.ptr[0];
            ptr[1] += m.ptr[1];
            ptr[2] += m.ptr[2];
            ptr[3] += m.ptr[3];

            ptr[4] += m.ptr[4];
            ptr[5] += m.ptr[5];
            ptr[6] += m.ptr[6];
            ptr[7] += m.ptr[7];

            ptr[8] += m.ptr[8];
            ptr[9] += m.ptr[9];
            ptr[10] += m.ptr[10];
            ptr[11] += m.ptr[11];

            ptr[12] += m.ptr[12];
            ptr[13] += m.ptr[13];
            ptr[14] += m.ptr[14];
            ptr[15] += m.ptr[15];
            return *this;
        }

        inline ffw::Mat4x4<T> operator - (const ffw::Mat4x4<T> &m) const {
            Mat4x4 r;
            r.ptr[0] = ptr[0] - m.ptr[0];
            r.ptr[1] = ptr[1] - m.ptr[1];
            r.ptr[2] = ptr[2] - m.ptr[2];
            r.ptr[3] = ptr[3] - m.ptr[3];

            r.ptr[4] = ptr[4] - m.ptr[4];
            r.ptr[5] = ptr[5] - m.ptr[5];
            r.ptr[6] = ptr[6] - m.ptr[6];
            r.ptr[7] = ptr[7] - m.ptr[7];

            r.ptr[8] = ptr[8] - m.ptr[8];
            r.ptr[9] = ptr[9] - m.ptr[9];
            r.ptr[10] = ptr[10] - m.ptr[10];
            r.ptr[11] = ptr[11] - m.ptr[11];

            r.ptr[12] = ptr[12] - m.ptr[12];
            r.ptr[13] = ptr[13] - m.ptr[13];
            r.ptr[14] = ptr[14] - m.ptr[14];
            r.ptr[15] = ptr[15] - m.ptr[15];
            return r;
        }

        inline ffw::Mat4x4<T>&  operator -= (const ffw::Mat4x4<T> &m) {
            ptr[0] -= m.ptr[0];
            ptr[1] -= m.ptr[1];
            ptr[2] -= m.ptr[2];
            ptr[3] -= m.ptr[3];

            ptr[4] -= m.ptr[4];
            ptr[5] -= m.ptr[5];
            ptr[6] -= m.ptr[6];
            ptr[7] -= m.ptr[7];

            ptr[8] -= m.ptr[8];
            ptr[9] -= m.ptr[9];
            ptr[10] -= m.ptr[10];
            ptr[11] -= m.ptr[11];

            ptr[12] -= m.ptr[12];
            ptr[13] -= m.ptr[13];
            ptr[14] -= m.ptr[14];
            ptr[15] -= m.ptr[15];
            return *this;
        }

        inline ffw::Mat4x4<T>  operator * (const ffw::Mat4x4<T> &m) const {
            Mat4x4 r;
            r.ptr[0] = ptr[0] * m.ptr[0] + ptr[4] * m.ptr[1] + ptr[8] * m.ptr[2] + ptr[12] * m.ptr[3];  r.ptr[4] = ptr[0] * m.ptr[4] + ptr[4] * m.ptr[5] + ptr[8] * m.ptr[6] + ptr[12] * m.ptr[7];  r.ptr[8] = ptr[0] * m.ptr[8] + ptr[4] * m.ptr[9] + ptr[8] * m.ptr[10] + ptr[12] * m.ptr[11];  r.ptr[12] = ptr[0] * m.ptr[12] + ptr[4] * m.ptr[13] + ptr[8] * m.ptr[14] + ptr[12] * m.ptr[15];
            r.ptr[1] = ptr[1] * m.ptr[0] + ptr[5] * m.ptr[1] + ptr[9] * m.ptr[2] + ptr[13] * m.ptr[3];  r.ptr[5] = ptr[1] * m.ptr[4] + ptr[5] * m.ptr[5] + ptr[9] * m.ptr[6] + ptr[13] * m.ptr[7];  r.ptr[9] = ptr[1] * m.ptr[8] + ptr[5] * m.ptr[9] + ptr[9] * m.ptr[10] + ptr[13] * m.ptr[11];  r.ptr[13] = ptr[1] * m.ptr[12] + ptr[5] * m.ptr[13] + ptr[9] * m.ptr[14] + ptr[13] * m.ptr[15];
            r.ptr[2] = ptr[2] * m.ptr[0] + ptr[6] * m.ptr[1] + ptr[10] * m.ptr[2] + ptr[14] * m.ptr[3];  r.ptr[6] = ptr[2] * m.ptr[4] + ptr[6] * m.ptr[5] + ptr[10] * m.ptr[6] + ptr[14] * m.ptr[7];  r.ptr[10] = ptr[2] * m.ptr[8] + ptr[6] * m.ptr[9] + ptr[10] * m.ptr[10] + ptr[14] * m.ptr[11];  r.ptr[14] = ptr[2] * m.ptr[12] + ptr[6] * m.ptr[13] + ptr[10] * m.ptr[14] + ptr[14] * m.ptr[15];
            r.ptr[3] = ptr[3] * m.ptr[0] + ptr[7] * m.ptr[1] + ptr[11] * m.ptr[2] + ptr[15] * m.ptr[3];  r.ptr[7] = ptr[3] * m.ptr[4] + ptr[7] * m.ptr[5] + ptr[11] * m.ptr[6] + ptr[15] * m.ptr[7];  r.ptr[11] = ptr[3] * m.ptr[8] + ptr[7] * m.ptr[9] + ptr[11] * m.ptr[10] + ptr[15] * m.ptr[11];  r.ptr[15] = ptr[3] * m.ptr[12] + ptr[7] * m.ptr[13] + ptr[11] * m.ptr[14] + ptr[15] * m.ptr[15];
            return r;
        }

        inline ffw::Mat4x4<T>&  operator *= (const ffw::Mat4x4<T> &m) {
            Mat4x4 r;
            r.ptr[0] = ptr[0] * m.ptr[0] + ptr[4] * m.ptr[1] + ptr[8] * m.ptr[2] + ptr[12] * m.ptr[3];  r.ptr[4] = ptr[0] * m.ptr[4] + ptr[4] * m.ptr[5] + ptr[8] * m.ptr[6] + ptr[12] * m.ptr[7];  r.ptr[8] = ptr[0] * m.ptr[8] + ptr[4] * m.ptr[9] + ptr[8] * m.ptr[10] + ptr[12] * m.ptr[11];  r.ptr[12] = ptr[0] * m.ptr[12] + ptr[4] * m.ptr[13] + ptr[8] * m.ptr[14] + ptr[12] * m.ptr[15];
            r.ptr[1] = ptr[1] * m.ptr[0] + ptr[5] * m.ptr[1] + ptr[9] * m.ptr[2] + ptr[13] * m.ptr[3];  r.ptr[5] = ptr[1] * m.ptr[4] + ptr[5] * m.ptr[5] + ptr[9] * m.ptr[6] + ptr[13] * m.ptr[7];  r.ptr[9] = ptr[1] * m.ptr[8] + ptr[5] * m.ptr[9] + ptr[9] * m.ptr[10] + ptr[13] * m.ptr[11];  r.ptr[13] = ptr[1] * m.ptr[12] + ptr[5] * m.ptr[13] + ptr[9] * m.ptr[14] + ptr[13] * m.ptr[15];
            r.ptr[2] = ptr[2] * m.ptr[0] + ptr[6] * m.ptr[1] + ptr[10] * m.ptr[2] + ptr[14] * m.ptr[3];  r.ptr[6] = ptr[2] * m.ptr[4] + ptr[6] * m.ptr[5] + ptr[10] * m.ptr[6] + ptr[14] * m.ptr[7];  r.ptr[10] = ptr[2] * m.ptr[8] + ptr[6] * m.ptr[9] + ptr[10] * m.ptr[10] + ptr[14] * m.ptr[11];  r.ptr[14] = ptr[2] * m.ptr[12] + ptr[6] * m.ptr[13] + ptr[10] * m.ptr[14] + ptr[14] * m.ptr[15];
            r.ptr[3] = ptr[3] * m.ptr[0] + ptr[7] * m.ptr[1] + ptr[11] * m.ptr[2] + ptr[15] * m.ptr[3];  r.ptr[7] = ptr[3] * m.ptr[4] + ptr[7] * m.ptr[5] + ptr[11] * m.ptr[6] + ptr[15] * m.ptr[7];  r.ptr[11] = ptr[3] * m.ptr[8] + ptr[7] * m.ptr[9] + ptr[11] * m.ptr[10] + ptr[15] * m.ptr[11];  r.ptr[15] = ptr[3] * m.ptr[12] + ptr[7] * m.ptr[13] + ptr[11] * m.ptr[14] + ptr[15] * m.ptr[15];
            *this = r;
            return *this;
        }

        template <class S>
        inline ffw::Vec4<S> operator * (const ffw::Vec4<S>& v) const {
            ffw::Vec4f r;
            r.x = v.x*ptr[0] + v.y*ptr[4] + v.z*ptr[8] + v.w*ptr[12];
            r.y = v.x*ptr[1] + v.y*ptr[5] + v.z*ptr[9] + v.w*ptr[13];
            r.z = v.x*ptr[2] + v.y*ptr[6] + v.z*ptr[10] + v.w*ptr[14];
            r.w = v.x*ptr[3] + v.y*ptr[7] + v.z*ptr[11] + v.w*ptr[15];
            return r;
        }

        template <class S>
        inline ffw::Vec3<S> operator * (const ffw::Vec3<S>& v) const {
            ffw::Vec3f r;
            r.x = v.x*ptr[0] + v.y*ptr[4] + v.z*ptr[8] + ptr[12];
            r.y = v.x*ptr[1] + v.y*ptr[5] + v.z*ptr[9] + ptr[13];
            r.z = v.x*ptr[2] + v.y*ptr[6] + v.z*ptr[10] + ptr[14];
            //r.w = v.x*ptr[3] + v.y*ptr[7] + v.z*ptr[11] + v.w*ptr[15];
            return r;
        }

        inline T& operator [] (int x) {
            return ptr[x];
        }

        inline const T& operator [] (int x) const {
            return ptr[x];
        }

        inline ffw::Mat4x4<T>& rotate(const ffw::Quaternion<T>& q) {
            // Taken from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
            auto sqw = q.w*q.w;
            auto sqx = q.x*q.x;
            auto sqy = q.y*q.y;
            auto sqz = q.z*q.z;

            // invs (inverse square length) is only required if quaternion is not already normalised
            auto invs = T(1) / (sqx + sqy + sqz + sqw);
            ptr[0] = (sqx - sqy - sqz + sqw)*invs; // since sqw + sqx + sqy + sqz =1/invs*invs
            ptr[5] = (-sqx + sqy - sqz + sqw)*invs;
            ptr[10] = (-sqx - sqy + sqz + sqw)*invs;

            auto tmp1 = q.x*q.y;
            auto tmp2 = q.z*q.w;
            ptr[1] = T(2.0) * (tmp1 + tmp2)*invs;
            ptr[4] = T(2.0) * (tmp1 - tmp2)*invs;

            tmp1 = q.x*q.z;
            tmp2 = q.y*q.w;
            ptr[2] = T(2.0) * (tmp1 - tmp2)*invs;
            ptr[8] = T(2.0) * (tmp1 + tmp2)*invs;
            tmp1 = q.y*q.z;
            tmp2 = q.x*q.w;
            ptr[6] = T(2.0) * (tmp1 + tmp2)*invs;
            ptr[9] = T(2.0) * (tmp1 - tmp2)*invs;

            return *this;
        }

        inline ffw::Mat4x4<T>& translate(T x, T y, T z) {
            ptr[12] += x;
            ptr[13] += y;
            ptr[14] += z;
            return *this;
        }

        inline ffw::Mat4x4<T>& scale(T x, T y, T z) {
            Mat4x4 m;
            m[0] = x;
            m[5] = y;
            m[10] = z;
            (*this) *= m;
            return *this;
        }

        inline ffw::Mat4x4<T>& transpose() {
            T m04 = ptr[4];
            T m08 = ptr[8];
            T m09 = ptr[9];
            T m12 = ptr[12];
            T m13 = ptr[13];
            T m14 = ptr[14];
            ptr[4] = ptr[1];
            ptr[8] = ptr[2];
            ptr[9] = ptr[6];
            ptr[12] = ptr[3];
            ptr[13] = ptr[7];
            ptr[14] = ptr[11];
            ptr[1] = m04;
            ptr[2] = m08;
            ptr[6] = m09;
            ptr[3] = m12;
            ptr[7] = m13;
            ptr[11] = m14;
            return *this;
        }

        inline T determinant() const {
            // Taken from http://www.euclideanspace.com/maths/algebra/matrix/functions/determinant/fourD/index.htm
            const auto det = 
                ptr[12] * ptr[9] * ptr[6] * ptr[3] - ptr[8] * ptr[13] * ptr[6] * ptr[3] -
                ptr[12] * ptr[5] * ptr[10] * ptr[3] + ptr[4] * ptr[13] * ptr[10] * ptr[3] +
                ptr[8] * ptr[5] * ptr[14] * ptr[3] - ptr[4] * ptr[9] * ptr[14] * ptr[3] -
                ptr[12] * ptr[9] * ptr[2] * ptr[7] + ptr[8] * ptr[13] * ptr[2] * ptr[7] +
                ptr[12] * ptr[1] * ptr[10] * ptr[7] - ptr[0] * ptr[13] * ptr[10] * ptr[7] -
                ptr[8] * ptr[1] * ptr[14] * ptr[7] + ptr[0] * ptr[9] * ptr[14] * ptr[7] +
                ptr[12] * ptr[5] * ptr[2] * ptr[11] - ptr[4] * ptr[13] * ptr[2] * ptr[11] -
                ptr[12] * ptr[1] * ptr[6] * ptr[11] + ptr[0] * ptr[13] * ptr[6] * ptr[11] +
                ptr[4] * ptr[1] * ptr[14] * ptr[11] - ptr[0] * ptr[5] * ptr[14] * ptr[11] -
                ptr[8] * ptr[5] * ptr[2] * ptr[15] + ptr[4] * ptr[9] * ptr[2] * ptr[15] +
                ptr[8] * ptr[1] * ptr[6] * ptr[15] - ptr[0] * ptr[9] * ptr[6] * ptr[15] -
                ptr[4] * ptr[1] * ptr[10] * ptr[15] + ptr[0] * ptr[5] * ptr[10] * ptr[15];
            return det;
        }

        inline ffw::Mat4x4<T>& inverse() {
            ffw::Mat4x4<T> m;
            m.ptr[0] = ptr[6]*ptr[11]*ptr[13] - ptr[7]*ptr[10]*ptr[13] + ptr[7]*ptr[9]*ptr[14] - ptr[5]*ptr[11]*ptr[14] - ptr[6]*ptr[9]*ptr[15] + ptr[5]*ptr[10]*ptr[15];
            m.ptr[1] = ptr[3]*ptr[10]*ptr[13] - ptr[2]*ptr[11]*ptr[13] - ptr[3]*ptr[9]*ptr[14] + ptr[1]*ptr[11]*ptr[14] + ptr[2]*ptr[9]*ptr[15] - ptr[1]*ptr[10]*ptr[15];
            m.ptr[2] = ptr[2]*ptr[7]*ptr[13] - ptr[3]*ptr[6]*ptr[13] + ptr[3]*ptr[5]*ptr[14] - ptr[1]*ptr[7]*ptr[14] - ptr[2]*ptr[5]*ptr[15] + ptr[1]*ptr[6]*ptr[15];
            m.ptr[3] = ptr[3]*ptr[6]*ptr[9] - ptr[2]*ptr[7]*ptr[9] - ptr[3]*ptr[5]*ptr[10] + ptr[1]*ptr[7]*ptr[10] + ptr[2]*ptr[5]*ptr[11] - ptr[1]*ptr[6]*ptr[11];
            m.ptr[4] = ptr[7]*ptr[10]*ptr[12] - ptr[6]*ptr[11]*ptr[12] - ptr[7]*ptr[8]*ptr[14] + ptr[4]*ptr[11]*ptr[14] + ptr[6]*ptr[8]*ptr[15] - ptr[4]*ptr[10]*ptr[15];
            m.ptr[5] = ptr[2]*ptr[11]*ptr[12] - ptr[3]*ptr[10]*ptr[12] + ptr[3]*ptr[8]*ptr[14] - ptr[0]*ptr[11]*ptr[14] - ptr[2]*ptr[8]*ptr[15] + ptr[0]*ptr[10]*ptr[15];
            m.ptr[6] = ptr[3]*ptr[6]*ptr[12] - ptr[2]*ptr[7]*ptr[12] - ptr[3]*ptr[4]*ptr[14] + ptr[0]*ptr[7]*ptr[14] + ptr[2]*ptr[4]*ptr[15] - ptr[0]*ptr[6]*ptr[15];
            m.ptr[7] = ptr[2]*ptr[7]*ptr[8] - ptr[3]*ptr[6]*ptr[8] + ptr[3]*ptr[4]*ptr[10] - ptr[0]*ptr[7]*ptr[10] - ptr[2]*ptr[4]*ptr[11] + ptr[0]*ptr[6]*ptr[11];
            m.ptr[8] = ptr[5]*ptr[11]*ptr[12] - ptr[7]*ptr[9]*ptr[12] + ptr[7]*ptr[8]*ptr[13] - ptr[4]*ptr[11]*ptr[13] - ptr[5]*ptr[8]*ptr[15] + ptr[4]*ptr[9]*ptr[15];
            m.ptr[9] = ptr[3]*ptr[9]*ptr[12] - ptr[1]*ptr[11]*ptr[12] - ptr[3]*ptr[8]*ptr[13] + ptr[0]*ptr[11]*ptr[13] + ptr[1]*ptr[8]*ptr[15] - ptr[0]*ptr[9]*ptr[15];
            m.ptr[10] = ptr[1]*ptr[7]*ptr[12] - ptr[3]*ptr[5]*ptr[12] + ptr[3]*ptr[4]*ptr[13] - ptr[0]*ptr[7]*ptr[13] - ptr[1]*ptr[4]*ptr[15] + ptr[0]*ptr[5]*ptr[15];
            m.ptr[11] = ptr[3]*ptr[5]*ptr[8] - ptr[1]*ptr[7]*ptr[8] - ptr[3]*ptr[4]*ptr[9] + ptr[0]*ptr[7]*ptr[9] + ptr[1]*ptr[4]*ptr[11] - ptr[0]*ptr[5]*ptr[11];
            m.ptr[12] = ptr[6]*ptr[9]*ptr[12] - ptr[5]*ptr[10]*ptr[12] - ptr[6]*ptr[8]*ptr[13] + ptr[4]*ptr[10]*ptr[13] + ptr[5]*ptr[8]*ptr[14] - ptr[4]*ptr[9]*ptr[14];
            m.ptr[13] = ptr[1]*ptr[10]*ptr[12] - ptr[2]*ptr[9]*ptr[12] + ptr[2]*ptr[8]*ptr[13] - ptr[0]*ptr[10]*ptr[13] - ptr[1]*ptr[8]*ptr[14] + ptr[0]*ptr[9]*ptr[14];
            m.ptr[14] = ptr[2]*ptr[5]*ptr[12] - ptr[1]*ptr[6]*ptr[12] - ptr[2]*ptr[4]*ptr[13] + ptr[0]*ptr[6]*ptr[13] + ptr[1]*ptr[4]*ptr[14] - ptr[0]*ptr[5]*ptr[14];
            m.ptr[15] = ptr[1]*ptr[6]*ptr[8] - ptr[2]*ptr[5]*ptr[8] + ptr[2]*ptr[4]*ptr[9] - ptr[0]*ptr[6]*ptr[9] - ptr[1]*ptr[4]*ptr[10] + ptr[0]*ptr[5]*ptr[10];
            const auto det = T(1) / determinant();
            for (int i = 0; i < 16; i++)ptr[i] = m.ptr[i] * det;
            return *this;
        }
    };
    /**
     * @ingroup graphics
     */
    typedef Mat4x4<float> Mat4x4f;
    /**
     * @ingroup graphics
     */
    typedef Mat4x4<double> Mat4x4d;
    /**
     * @ingroup graphics
     */
    typedef Mat4x4<int> Mat4x4i;
};
#endif
