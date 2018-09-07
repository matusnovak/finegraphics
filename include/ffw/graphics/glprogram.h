/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_PROGRAM
#define FFW_GRAPHICS_PROGRAM

#include "glshader.h"
#include "color.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

namespace ffw {
    /**
    * @ingroup graphics
    */
    class FFW_API GLProgram {
    public:
        GLProgram();
        GLProgram(const std::initializer_list<GLShader*>& shaders);
        GLProgram(const GLProgram& other) = delete;
        GLProgram(GLProgram&& other) NOEXCEPT;
        virtual ~GLProgram();
        GLProgram& operator = (const GLProgram& other) = delete;
        GLProgram& operator = (GLProgram&& other) NOEXCEPT;
        void swap(GLProgram& other) NOEXCEPT;

        void destroy();
        inline GLint getHandle() const {
            return handle;
        }
        inline bool isCreated() const {
            return loaded;
        }

        void setAttributePointerf(int location, int size, int stride, const GLvoid* offset) const;
        void setAttributeDivisor(unsigned int index, unsigned int divisor) const;
        void drawArrays(unsigned int mode, int first, int count) const;
        void drawArraysInstanced(unsigned int mode, int first, int count, int instancecount) const;
        void drawElements(unsigned int mode, int count, unsigned int type, const void* indices) const;
        void drawElementsRange(unsigned int mode, unsigned int start, unsigned int end, int count, unsigned int type, const void* indices) const;
        void drawElementsInstanced(unsigned int mode, int count, unsigned int type, const void* indices, int instancecount) const;
        void bind() const;
        void unbind() const;
        int getUniformLocation(const char* name) const;
        int getAttributeLocation(const char* name) const;
        void setUniform1f(int location, float value) const;
        void setUniform1fv(int location, const float* array, int length) const;
        void setUniform1i(int location, int value) const;
        void setUniform1iv(int location, const int* array, int length) const;
        void setUniform2f(int location, float x, float y) const;
        void setUniform2fv(int location, const float* array, int length) const;
        void setUniform2i(int location, int x, int y) const;
        void setUniform2iv(int location, const int* array, int length) const;
        void setUniform3f(int location, float x, float y, float z) const;
        void setUniform3fv(int location, const float* array, int length) const;
        void setUniform3i(int location, int x, int y, int z) const;
        void setUniform3iv(int location, const int* array, int length) const;
        void setUniform4f(int location, float x, float y, float z, float w) const;
        void setUniform4fv(int location, const float* array, int length) const;
        void setUniform4i(int location, int x, int y, int z, int w) const;
        void setUniform4iv(int location, const int* array, int length) const;
        void setUniformMatrix2fv(int location, const float* mat, int length) const;
        void setUniformMatrix3fv(int location, const float* mat, int length) const;
        void setUniformMatrix4fv(int location, const float* mat, int length) const;
        void setUniform2f(int location, const ffw::Vec2f& vec) const;
        void setUniform2fv(int location, const ffw::Vec2f* array, int length) const;
        void setUniform2i(int location, const ffw::Vec2i& vec) const;
        void setUniform2iv(int location, const ffw::Vec2i* array, int length) const;
        void setUniform3f(int location, const ffw::Vec3f& vec) const;
        void setUniform3fv(int location, const ffw::Vec3f* array, int length) const;
        void setUniform3i(int location, const ffw::Vec3i& vec) const;
        void setUniform3iv(int location, const  ffw::Vec3i* array, int length) const;
        void setUniform4f(int location, const  ffw::Vec4f& vec) const;
        void setUniform4fv(int location, const ffw::Vec4f* array, int length) const;
        void setUniform4i(int location, const  ffw::Vec4i& vec) const;
        void setUniform4iv(int location, const ffw::Vec4i*  array, int length) const;
        void setUniform4f(int location, const  Color& color) const;
        void setUniform4fv(int location, const Color* colors, int length) const;
        void setUniformMatrix3fv(int location, const Mat3x3f* mat, int length) const;
        void setUniformMatrix4fv(int location, const Mat4x4f* mat, int length) const;
    private:
        bool checkForProgramErrors(std::string& errorstr) const;

        bool loaded;
        GLuint handle;
    };
};

inline void swap(ffw::GLProgram& first, ffw::GLProgram& second) NOEXCEPT {
    first.swap(second);
}
#endif
