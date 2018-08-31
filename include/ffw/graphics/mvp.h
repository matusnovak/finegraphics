/* This file is part of FineFramework project */
#ifndef FFW_MODEL_VIEW_PROJECTION
#define FFW_MODEL_VIEW_PROJECTION

#include "mat4.h"
#include "constants.h"

namespace ffw {
    /**
    * @ingroup graphics
    */
    template <class T>
    inline ffw::Mat4x4<T> makeRotationMatrix(const ffw::Quaternion<T>& q) {
        Mat4x4<T> m;
        m[0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);    m[4] = 2.0f * (q.x * q.y + q.z * q.w);         m[8] = 2.0f * (q.x * q.z - q.y * q.w);
        m[1] = 2.0f * (q.x * q.y - q.z * q.w);           m[5] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);  m[9] = 2.0f * (q.y * q.z + q.x * q.w);
        m[2] = 2.0f * (q.x * q.z + q.y * q.w);           m[6] = 2.0f * (q.y * q.z - q.x * q.w);         m[10] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
        return m;
    }
    /**
    * @ingroup graphics
    */
    template<typename T>
    Mat4x4<T> makeProjectionMatrix(T fieldOfView, T aspect, T near, T far) {
        T halfFov = fieldOfView / 2;
        T tanFov = T(std::tan(halfFov*DEG_TO_RAD));
        ffw::Mat4x4<T> mat;
        mat.ptr[0] = 1 / (aspect * tanFov);
        mat.ptr[5] = 1 / tanFov;
        mat.ptr[10] = (near + far) / (near - far);
        mat.ptr[11] = -1;
        mat.ptr[14] = (2 * far * near) / (near - far);
        return mat;
    }
    /**
    * @ingroup graphics
    */
    template<typename T>
    Mat4x4<T> makeLookAtMatrix(const Vec3<T>& eyes, const Vec3<T>& target, const Vec3<T>& upVector) {
        Mat4x4<T> mat;
        Vec3<T> f = ffw::normalize(target - eyes);
        Vec3<T> s = ffw::normalize(ffw::cross(f, upVector));
        Vec3<T> u = ffw::cross(s, f);
        mat[0] = s.x;
        mat[4] = s.y;
        mat[8] = s.z;
        mat[3] = 0;
        mat[1] = u.x;
        mat[5] = u.y;
        mat[9] = u.z;
        mat[7] = 0;
        mat[2] = -f.x;
        mat[6] = -f.y;
        mat[10] = -f.z;
        mat[11] = 0;
        mat[12] = -ffw::dot(s, eyes);
        mat[13] = -ffw::dot(u, eyes);
        mat[14] = ffw::dot(f, eyes);
        mat[15] = 1;
        return mat;
    }
    /**
    * @ingroup graphics
    */
    template<typename T>
    Mat4x4<T> makeFpsCameraMatrix(const Vec3<T>& eyes, float pitch, float yaw) {
        T cPitch = T(std::cos(pitch*DEG_TO_RAD));
        T sPitch = T(std::sin(pitch*DEG_TO_RAD));
        T cYaw = T(std::cos(yaw*DEG_TO_RAD));
        T sYaw = T(std::sin(yaw*DEG_TO_RAD));
        ffw::Mat4x4<T> mat;
        ffw::Vec3<T> s(cYaw, 0, -sYaw);
        ffw::Vec3<T> u(sYaw * sPitch, cPitch, cYaw * sPitch);
        ffw::Vec3<T> f(sYaw * cPitch, -sPitch, cPitch * cYaw);
        mat[0] = s.x;
        mat[4] = s.y;
        mat[8] = s.z;
        mat[3] = 0;
        mat[1] = u.x;
        mat[5] = u.y;
        mat[9] = u.z;
        mat[7] = 0;
        mat[2] = -f.x;
        mat[6] = -f.y;
        mat[10] = -f.z;
        mat[11] = 0;
        mat[12] = -ffw::dot(s, eyes);
        mat[13] = -ffw::dot(u, eyes);
        mat[14] = ffw::dot(f, eyes);
        mat[15] = 1;
        return mat;
    }
    /**
    * @ingroup graphics
    */
    template<typename T>
    Mat4x4<T> makeOrthoMatrix(T left, T right, T bottom, T top, T znear, T zfar) {
        ffw::Mat4x4<T> mat;
        mat[0] = T(2) / (right - left); mat[4] = 0; mat[8] = 0; mat[12] = -(right + left) / (right - left);
        mat[1] = 0; mat[5] = T(2) / (top - bottom); mat[9] = 0; mat[13] = -(top + bottom) / (top - bottom);
        mat[2] = 0; mat[6] = 0; mat[10] = T(1) / (zfar - znear); mat[14] = -znear / (zfar - znear);
        mat[3] = 0; mat[7] = 0; mat[11] = 0;  mat[15] = 1;
        return mat;
    }
};

#endif