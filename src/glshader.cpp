/*** This file is part of FineFramework project ***/

#include <utility>
#include <fstream>
#include "ffw/graphics/glshader.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLShader::GLShader():loaded(false),handle(0),type(GL_FALSE) {
 
}

///=============================================================================
ffw::GLShader::GLShader(const GLenum type, const std::string& code):loaded(true), type(type) {
    const GLchar* data = code.c_str();
    // Create shader object
    handle = glCreateShader(type);
    if (handle == 0)throw GLException("Failed to create shader object");
    // set the source data
    glShaderSource(handle, 1, &data, nullptr);
    // Compile
    glCompileShader(handle);

    std::string err;
    if (!checkForShaderErrors(err)) {
        destroy();
        throw GLException("Failed to compile shader, error: " + err);
    }
}

///=============================================================================
bool ffw::GLShader::checkForShaderErrors(std::string& errorstr) const {
    // Check Shader compilation status
    GLint result;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &result);
    // Shader failed to compile
    if (result == GL_FALSE) {
        // get length of log
        GLint length;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
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
ffw::GLShader::GLShader(GLShader&& other) NOEXCEPT : loaded(false), handle(0), type(GL_FALSE) {
    swap(other);
}

///=============================================================================
ffw::GLShader::~GLShader() {
    destroy();
}

///=============================================================================
ffw::GLShader& ffw::GLShader::operator = (GLShader&& other) NOEXCEPT {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
void ffw::GLShader::swap(GLShader& other) NOEXCEPT {
    using std::swap;
    swap(handle, other.handle);
    swap(loaded, other.loaded);
    swap(type, other.type);
}

///=============================================================================
void ffw::GLShader::destroy() {
    if (loaded)glDeleteShader(handle);
    handle = 0;
    loaded = false;
    type = GL_FALSE;
}
