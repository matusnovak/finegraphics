/* This file is part of FineFramework project */
#ifndef FFW_Quat
#define FFW_Quat

#include <ostream>
#include <cmath>
#include "constants.h"

namespace ffw {
    /**
     * @ingroup graphics
     */
    template <class T> struct Quaternion {
    public:
        T x;
        T y;
        T z;
        T w;
        inline Quaternion() {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            w = 1.0f;
        }

        inline Quaternion(T x, T y, T z, T w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        inline Quaternion(const Quaternion& q) {
            x = q.x;
            y = q.y;
            z = q.z;
            w = q.w;
        }

        inline void set(T x, T y, T z, T w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        inline void set(const Quaternion& q) {
            x = q.x;
            y = q.y;
            z = q.z;
            w = q.w;
        }

        inline ffw::Quaternion<T>& rotate(T deg, T X, T Y, T Z) {
            const auto angle = deg*DEG_TO_RAD;
            const auto result = std::sin(angle / 2.0);
            x = float(X * result);
            y = float(Y * result);
            z = float(Z * result);
            w = float(std::cos(angle / 2.0));
            normalize();
            return *this;
        }

        inline ffw::Quaternion<T>& rotateRad(T rad, T X, T Y, T Z) {
            const auto result = std::sin(rad / 2.0);
            x = float(X * result);
            y = float(Y * result);
            z = float(Z * result);
            w = float(std::cos(rad / 2.0));
            normalize();
            return *this;
        }

        inline ffw::Quaternion<T> operator - () const {
            Quaternion<T> result;
            result.x = -x;
            result.y = -y;
            result.z = -z;
            result.w = -w;
            return result;
        }

        inline ffw::Quaternion<T> operator * (const Quaternion& q) const {
            Quaternion<T> result;
            result.w = w*q.w - x*q.x - y*q.y - z*q.z;
            result.x = w*q.x + x*q.w + y*q.z - z*q.y;
            result.y = w*q.y + y*q.w + z*q.x - x*q.z;
            result.z = w*q.z + z*q.w + x*q.y - y*q.x;
            return result;
        }

        inline ffw::Quaternion<T>& operator *= (const Quaternion& q) {
            const auto rw = w*q.w - x*q.x - y*q.y - z*q.z;
            const auto rx = w*q.x + x*q.w + y*q.z - z*q.y;
            const auto ry = w*q.y + y*q.w + z*q.x - x*q.z;
            const auto rz = w*q.z + z*q.w + x*q.y - y*q.x;
            x = rx;
            y = ry;
            z = rz;
            w = rw;
            return *this;
        }

        inline ffw::Quaternion<T> operator + (T val) const {
            Quaternion result;
            result.x = x+val;
            result.y = y+val;
            result.z = z+val;
            result.w = w+val;
            return result;
        }

        inline ffw::Quaternion<T>& operator += (T val) {
            x += val;
            y += val;
            z += val;
            w += val;
            return +this;
        }

        inline ffw::Quaternion<T> operator - (T val) const {
            Quaternion result;
            result.x = x-val;
            result.y = y-val;
            result.z = z-val;
            result.w = w-val;
            return result;
        }

        inline ffw::Quaternion<T>& operator -= (T val) {
            x -= val;
            y -= val;
            z -= val;
            w -= val;
            return -this;
        }

        inline ffw::Quaternion<T> operator * (T val) const {
            Quaternion result;
            result.x = x*val;
            result.y = y*val;
            result.z = z*val;
            result.w = w*val;
            return result;
        }

        inline ffw::Quaternion<T>& operator *= (T val) {
            x *= val;
            y *= val;
            z *= val;
            w *= val;
            return *this;
        }

        inline ffw::Quaternion<T> operator / (T val) const {
            Quaternion result;
            result.x = x/val;
            result.y = y/val;
            result.z = z/val;
            result.w = w/val;
            return result;
        }

        inline ffw::Quaternion<T>& operator /= (T val) {
            x /= val;
            y /= val;
            z /= val;
            w /= val;
            return *this;
        }

        inline ffw::Quaternion<T> operator + (const Quaternion& q) const {
            Quaternion<T> result;
            result.x = x + q.x;
            result.y = y + q.y;
            result.z = z + q.z;
            result.w = w + q.w;
            return result;
        }

        inline ffw::Quaternion<T>& operator += (const Quaternion& q) {
            x += q.x;
            y += q.y;
            z += q.z;
            w += q.w;
            return *this;
        }

        inline ffw::Quaternion<T> operator - (const Quaternion& q) const {
            Quaternion<T> result;
            result.x = x - q.x;
            result.y = y - q.y;
            result.z = z - q.z;
            result.w = w - q.w;
            return result;
        }

        inline ffw::Quaternion<T>& operator -= (const Quaternion& q) {
            x -= q.x;
            y -= q.y;
            z -= q.z;
            w -= q.w;
            return *this;
        }

        inline void normalize() {
            const auto n = 1.0f / std::sqrt(x*x + y*y + z*z + w*w);
            x = x * n;
            y = y * n;
            z = z * n;
            w = w * n;
        }

        inline void getEuler(T* roll, T* pitch, T* yaw) const {
            // http://www.euclideanspace.com/maths/geometry/rotations/conversions/QuatToEuler/
            T test = x*y + z*w;
            double heading;
            double attitude;
            double bank;
            if (test > 0.499) { // singularity at north pole
                heading = 2.0f * std::atan2(x, w);
                attitude = M_PI_2;
                bank = 0;
            }
            else if (test < -0.499) { // singularity at south pole
                heading = -2.0f * std::atan2(x, w);
                attitude = -M_PI_2;
                bank = 0;
            }
            else {
                const auto sqx = x * x;
                const auto sqy = y * y;
                const auto sqz = z * z;
                heading = std::atan2(2.0f * y * w - 2.0f * x * z, 1.0f - 2.0f*sqy - 2.0f*sqz);
                attitude = std::asin(2 * test);
                bank = std::atan2(2.0f*x * w - 2.0f * y * z, 1.0f - 2.0f*sqx - 2.0f*sqz);
            }
            if (roll != nullptr)*roll = T(attitude*DEG_TO_RAD);
            if (pitch != nullptr)*pitch = T(heading*DEG_TO_RAD);
            if (yaw != nullptr)*yaw = T(bank*DEG_TO_RAD);
        }

        inline float length() const {
            return std::sqrt(x*x + y*y + z*z + w*w);
        }

        inline float lengthSqrd() const {
            return x*x + y*y + z*z + w*w;
        }

        inline ffw::Quaternion<T> getConjugate() const {
            Quaternion result;
            result.x = -x;
            result.y = -y;
            result.z = -z;
            result.w = w;
            return result;
        }

        inline ffw::Quaternion<T> getInversed() const {
            return getConjugate() / lengthSqrd();
        }

        inline ffw::Quaternion<T>& inverse() {
            *this = getConjugate() / lengthSqrd();
            return *this;
        }
    };
    /**
     * @ingroup graphics
     */
    typedef Quaternion<float> Quaternionf;
    /**
     * @ingroup graphics
     */
    typedef Quaternion<double> Quaterniond;
    /**
    * @ingroup graphics
    */
    template <class T>
    inline ffw::Quaternion<T> normalize(const Quaternion<T>& q) {
        ffw::Quaternion<T> result;
        const auto n = 1.0f / std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
        result.x = q.x * n;
        result.y = q.y * n;
        result.z = q.z * n;
        result.w = q.w * n;
        return result;
    }
    /**
    * @ingroup graphics
    */
    template <class T>
    inline std::ostream& operator << (std::ostream& os, const ffw::Quaternion<T>& quat) {
        os << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w;
        return os;
    }
};
#endif
