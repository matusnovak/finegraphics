/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/glvertexarray.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLVertexArray::GLVertexArray(): buffer(0) {
}

///=============================================================================
ffw::GLVertexArray::GLVertexArray(const bool create):buffer(0) {
    (void)create;
    // Generate buffer
    glGenVertexArrays(1, &buffer);
    if (buffer == 0) throw GLException("Failed to create buffer");
    // bind buffer
    glBindVertexArray(buffer);
}

///=============================================================================
ffw::GLVertexArray::GLVertexArray(GLVertexArray&& other) NOEXCEPT {
    swap(other);
}

///=============================================================================
void ffw::GLVertexArray::swap(GLVertexArray& other) NOEXCEPT {
    using std::swap;
    if(this != &other) {
        swap(buffer, other.buffer);
    }
}

///=============================================================================
ffw::GLVertexArray& ffw::GLVertexArray::operator = (GLVertexArray&& other) NOEXCEPT {
    if(this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLVertexArray::~GLVertexArray(){
    destroy();
}

///=============================================================================
void ffw::GLVertexArray::destroy() {
    // Delete buffer
    if (buffer != 0) glDeleteVertexArrays(1, &buffer);
    buffer = 0;
}

///=============================================================================
void ffw::GLVertexArray::bind() const {
    // bind buffer
    if(buffer != 0) glBindVertexArray(buffer);
}

///=============================================================================
void ffw::GLVertexArray::unbind() const {
    // UnBind buffer
    glBindVertexArray(0);
}

///=============================================================================
void ffw::GLVertexArray::enableVertexAttribArray(GLint location) const {
    // Enable attribute
    glEnableVertexAttribArray(location);
}

///=============================================================================
void ffw::GLVertexArray::disableVertexAttribArray(GLint location) const {
    // Enable attribute
    glDisableVertexAttribArray(location);
}

///=============================================================================
void ffw::GLVertexArray::setAttributePointerf(GLint location, GLint size, GLsizei stride, const GLvoid* offset) const {
    // set the pointer of the attribute
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, offset);
    // Enable attribute
    enableVertexAttribArray(location);
}

///=============================================================================
void ffw::GLVertexArray::setAttributeDivisor(GLuint index, GLuint divisor) const {
    glVertexAttribDivisor(index, divisor);
}
