#include "ffw/graphics/glrenderextensions.h"
#include "ffw/graphics/glprogram.h"
#include "ffw/graphics/exceptions.h"
#include "ffw/graphics/color.h"

///=============================================================================
ffw::GLProgram::GLProgram() :loaded(false), handle(0) {

}

///=============================================================================
ffw::GLProgram::GLProgram(const std::initializer_list<GLShader*>& shaders) : loaded(true) {
    handle = glCreateProgram();
    if (handle == 0) throw GLException("Failed to create program object");
    glUseProgram(handle);

    for (const auto& shdr : shaders) {
        if (shdr != nullptr)
            glAttachShader(handle, shdr->getHandle());
    }

    glLinkProgram(handle);
    std::string err;
    if(!checkForProgramErrors(err)) {
        destroy();
        throw GLException("Failed to link program, error: " + err);
    }
}

///=============================================================================
bool ffw::GLProgram::checkForProgramErrors(std::string& errorstr) const {
    // Check Shader compilation status
    GLint result;
    glGetProgramiv(handle, GL_LINK_STATUS, &result);
    // Shader failed to compile
    if (result == GL_FALSE) {
        // get length of log
        GLint length;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
        // allocate memory for log
        errorstr.resize(length, ' ');
        // get log
        glGetShaderInfoLog(handle, length, &result, &errorstr[0]);
        return false;
    }
    // Shader compiled
    return true;
}

///=============================================================================
ffw::GLProgram::GLProgram(GLProgram&& other) NOEXCEPT : loaded(false), handle(0) {
    swap(other);
}

///=============================================================================
ffw::GLProgram::~GLProgram() {
    destroy();
}

///=============================================================================
ffw::GLProgram& ffw::GLProgram::operator = (GLProgram&& other) NOEXCEPT {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
void ffw::GLProgram::swap(GLProgram& other) NOEXCEPT {
    using std::swap;
    swap(handle, other.handle);
    swap(loaded, other.loaded);
}

///=============================================================================
void ffw::GLProgram::destroy() {
    if (loaded)glDeleteShader(handle);
    handle = 0;
    loaded = false;
}

///=============================================================================
void ffw::GLProgram::bind() const {
    if (loaded)glUseProgram(handle);
}

///=============================================================================
void ffw::GLProgram::unbind() const {
    if (loaded) {
        // We need to disable attrib array
        // Otherwise this will mess up any old pipeline draw calls 
        glDisableVertexAttribArray(0);
        glUseProgram(0);
    }
}

///=============================================================================
void ffw::GLProgram::setAttributePointerf(GLint location, GLint size, GLsizei stride, const GLvoid* offset) const {
    // Enable attribute
    glEnableVertexAttribArray(location);
    // set the pointer of the attribute
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, offset);
}

///=============================================================================
void ffw::GLProgram::setAttributeDivisor(GLuint index, GLuint divisor) const {
    glVertexAttribDivisor(index, divisor);
}

///=============================================================================
void ffw::GLProgram::drawArrays(GLenum mode, GLint first, GLsizei count) const {
    // draw quad compositing of two triangles drawElements(GL_TRIANGLES, 6, 0);
    // drawElements(type to render, first vertice, number of vertices);
    glDrawArrays(mode, first, count);
}

///=============================================================================
void ffw::GLProgram::drawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) const {
    glDrawArraysInstanced(mode, first, count, instancecount);
}

///=============================================================================
void ffw::GLProgram::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) const {
    // draw quad compositing of two triangles myShader.drawElements(GL_TRIANGLES, 6, 0);
    // draw second triangle of quad drawElements(GL_TRIANGLES, 3, (GLvoid*) (sizeof(GLuint) * 3));
    // drawElements(type to render, number of vertices, (GLvoid*) (sizeof(GLuint) * vertice offset));
    glDrawElements(mode, count, type, indices);
}

///=============================================================================
void ffw::GLProgram::drawElementsRange(GLenum mode, GLuint Start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices) const {
    // draw second triangle of quad drawElementsRange(GL_TRIANGLES, 0, 3, 3, (GLvoid*) (sizeof(GLuint) * 3));
    // drawElementsRange(type to render, min index, max index, number of vertices, (GLvoid*) (sizeof(GLuint) * vertice offset));
    glDrawRangeElements(mode, Start, end, count, type, indices);
}

///=============================================================================
void ffw::GLProgram::drawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount) const {
    glDrawElementsInstanced(mode, count, type, indices, instancecount);
}

///=============================================================================
int ffw::GLProgram::getUniformLocation(const GLchar* name) const {
    if (!loaded)return -1;
    return glGetUniformLocation(handle, name);
}

///=============================================================================
int ffw::GLProgram::getAttributeLocation(const GLchar* name) const {
    if (!loaded)return -1;
    return glGetAttribLocation(handle, name);
}
///=============================================================================
// set 1D uniforms
void ffw::GLProgram::setUniform1f(GLint location, GLfloat value) const {
    glUniform1f(location, value);
}

///=============================================================================
void ffw::GLProgram::setUniform1fv(GLint location, const GLfloat* array, GLsizei length) const {
    glUniform1fv(location, length, array);
}

///=============================================================================
void ffw::GLProgram::setUniform1i(GLint location, GLint value) const {
    glUniform1i(location, value);
}

///=============================================================================
void ffw::GLProgram::setUniform1iv(GLint location, const GLint* array, GLsizei length) const {
    glUniform1iv(location, length, array);
}

///=============================================================================
// set 2D uniforms
void ffw::GLProgram::setUniform2f(GLint location, GLfloat x, GLfloat y) const {
    glUniform2f(location, x, y);
}

///=============================================================================
void ffw::GLProgram::setUniform2fv(GLint location, const GLfloat* array, GLsizei length) const {
    glUniform2fv(location, length, array);
}

///=============================================================================
void ffw::GLProgram::setUniform2i(GLint location, GLint x, GLint y) const {
    glUniform2i(location, x, y);
}

///=============================================================================
void ffw::GLProgram::setUniform2iv(GLint location, const GLint* array, GLsizei length) const {
    glUniform2iv(location, length, array);
}

///=============================================================================
// set 3D uniforms
void ffw::GLProgram::setUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z) const {
    glUniform3f(location, x, y, z);
}

///=============================================================================
void ffw::GLProgram::setUniform3fv(GLint location, const GLfloat* array, GLsizei length) const {
    glUniform3fv(location, length, array);
}

///=============================================================================
void ffw::GLProgram::setUniform3i(GLint location, GLint x, GLint y, GLint z) const {
    glUniform3i(location, x, y, z);
}

///=============================================================================
void ffw::GLProgram::setUniform3iv(GLint location, const GLint* array, GLsizei length) const {
    glUniform3iv(location, length, array);
}


///=============================================================================
// set 4D uniforms
void ffw::GLProgram::setUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const {
    glUniform4f(location, x, y, z, w);
}

///=============================================================================
void ffw::GLProgram::setUniform4fv(GLint location, const GLfloat* array, GLsizei length) const {
    glUniform4fv(location, length, array);
}

///=============================================================================
void ffw::GLProgram::setUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w) const {
    glUniform4i(location, x, y, z, w);
}

///=============================================================================
void ffw::GLProgram::setUniform4iv(GLint location, const GLint* array, GLsizei length) const {
    glUniform4iv(location, length, array);
}

///=============================================================================
// set 4D uniform from color
void ffw::GLProgram::setUniform4f(GLint location, const ffw::Color& color) const {
    glUniform4f(location, color.r, color.g, color.b, color.a);
}

///=============================================================================
void ffw::GLProgram::setUniform4fv(GLint location, const ffw::Color* colors, GLsizei length) const {
    glUniform4fv(location, length, &colors[0].r);
}

///=============================================================================
// set Matrix uniforms
void ffw::GLProgram::setUniformMatrix2fv(GLint location, const GLfloat* mat, GLsizei length) const {
    glUniformMatrix2fv(location, length, GL_FALSE, mat);
}

///=============================================================================
void ffw::GLProgram::setUniformMatrix3fv(GLint location, const GLfloat* mat, GLsizei length) const {
    glUniformMatrix3fv(location, length, GL_FALSE, mat);
}

///=============================================================================
void ffw::GLProgram::setUniformMatrix4fv(GLint location, const GLfloat* mat, GLsizei length) const {
    glUniformMatrix4fv(location, length, false, mat);
}

///=============================================================================
// set 2D uniforms from vector
void ffw::GLProgram::setUniform2f(GLint location, const ffw::Vec2f& vec) const {
    glUniform2f(location, vec.x, vec.y);
}

///=============================================================================
void ffw::GLProgram::setUniform2fv(GLint location, const ffw::Vec2f* Array, GLsizei length) const {
    glUniform2fv(location, length, &Array[0].x);
}

///=============================================================================
void ffw::GLProgram::setUniform2i(GLint location, const ffw::Vec2i& vec) const {
    glUniform2i(location, vec.x, vec.y);
}

///=============================================================================
void ffw::GLProgram::setUniform2iv(GLint location, const ffw::Vec2i* Array, GLsizei length) const {
    glUniform2iv(location, length, &Array[0].x);
}

///=============================================================================
// set 3D uniforms from vector
void ffw::GLProgram::setUniform3f(GLint location, const ffw::Vec3f& vec) const {
    glUniform3f(location, vec.x, vec.y, vec.z);
}

///=============================================================================
void ffw::GLProgram::setUniform3fv(GLint location, const ffw::Vec3f* Array, GLsizei length) const {
    glUniform3fv(location, length, &Array[0].x);
}

///=============================================================================
void ffw::GLProgram::setUniform3i(GLint location, const ffw::Vec3i& vec) const {
    glUniform3i(location, vec.x, vec.y, vec.z);
}

///=============================================================================
void ffw::GLProgram::setUniform3iv(GLint location, const ffw::Vec3i* Array, GLsizei length) const {
    glUniform3iv(location, length, &Array[0].x);
}

///=============================================================================
// set 4D uniforms from vector
void ffw::GLProgram::setUniform4f(GLint location, const ffw::Vec4f& vec) const {
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

///=============================================================================
void ffw::GLProgram::setUniform4fv(GLint location, const ffw::Vec4f* Array, GLsizei length) const {
    glUniform4fv(location, length, &Array[0].x);
}

///=============================================================================
void ffw::GLProgram::setUniform4i(GLint location, const ffw::Vec4i& vec) const {
    glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
}

///=============================================================================
void ffw::GLProgram::setUniform4iv(GLint location, const ffw::Vec4i* Array, GLsizei length) const {
    glUniform4iv(location, length, &Array[0].x);
}

///=============================================================================
void ffw::GLProgram::setUniformMatrix3fv(GLint location, const Mat3x3f* mat, GLsizei length) const {
    glUniformMatrix4fv(location, length, false, reinterpret_cast<const GLfloat*>(&mat[0]));
}

///=============================================================================
void ffw::GLProgram::setUniformMatrix4fv(GLint location, const Mat4x4f* mat, GLsizei length) const {
    glUniformMatrix4fv(location, length, false, reinterpret_cast<const GLfloat*>(&mat[0]));
}
