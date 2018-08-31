/*** This file is part of FineFramework project ***/

#include <utility>
#include <iostream>
#include "ffw/graphics/glbuffer.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLBuffer::GLBuffer() :accesstype(GL_FALSE), buffertype(GL_FALSE), loaded(false), buffer(0), size(0) {
}

///=============================================================================
ffw::GLBuffer::GLBuffer(const GLenum buffertype, const GLvoid* data, const GLsizei size, 
    const GLenum type):accesstype(type), buffertype(buffertype), loaded(true), buffer(0), size(size) {

    // Generate buffer
    glGenBuffers(1, &buffer);
    if (buffer == 0) throw GLException("Failed to create buffer");
    // bind buffer
    glBindBuffer(buffertype, buffer);
    // set buffer initial data
    glBufferData(buffertype, size, data, type);
}

///=============================================================================
ffw::GLBuffer::GLBuffer(GLBuffer&& other) NOEXCEPT :buffertype(other.buffertype) {
    loaded = false;
    accesstype = GL_FALSE;
    size = 0;
    buffer = 0;
    swap(other);
}

///=============================================================================
void ffw::GLBuffer::swap(GLBuffer& other) NOEXCEPT {
    using std::swap;
    if(this != &other) {
        swap(buffertype, other.buffertype);
        swap(loaded, other.loaded);
        swap(accesstype, other.accesstype);
        swap(size, other.size);
        swap(buffer, other.buffer);
    }
}

///=============================================================================
ffw::GLBuffer& ffw::GLBuffer::operator = (GLBuffer&& other) NOEXCEPT {
    if(this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLBuffer::~GLBuffer(){
    destroy();
}

///=============================================================================
void ffw::GLBuffer::destroy() {
    // Delete buffer
    if (loaded) glDeleteBuffers(1, &buffer);
    loaded = false;
    buffer = 0;
    size = 0;
    accesstype = GL_FALSE;
}

///=============================================================================
void ffw::GLBuffer::resize(const GLvoid* data, const GLsizei size) {
    if (loaded) glDeleteBuffers(1, &buffer);

    // bind buffer
    glBindBuffer(buffertype, buffer);
    // set buffer initial data
    glBufferData(buffertype, size, data, accesstype);
    // Check size
    GLint actualSize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &actualSize);
    if (actualSize != size) throw GLException("Failed to reallocate buffer");
}

///=============================================================================
void ffw::GLBuffer::setData(const GLvoid* data, const GLsizei offset, const GLsizei size) {
    if (!loaded) throw GLException("Buffer is not allocated");
    // Upload new data
    glBindBuffer(buffertype, buffer);
    glBufferSubData(buffertype, offset, size, data);
}

///=============================================================================
void ffw::GLBuffer::getData(GLvoid* data, const GLsizei offset, const GLsizei size) {
    if (!loaded) throw GLException("Buffer is not allocated");
    glBindBuffer(buffertype, buffer);
    glGetBufferSubData(buffertype, offset, size, data);
}

///=============================================================================
std::vector<uint8_t> ffw::GLBuffer::getData(const GLsizei offset, const GLsizei size) {
    std::vector<uint8_t> ret;
    ret.resize(size);
    getData(&ret[0], offset, size);
    return ret;
}

///=============================================================================
void ffw::GLBuffer::copyFrom(const GLBuffer* other, const GLintptr readoffset, 
    const GLintptr writeoffset, const GLsizeiptr size){

    if(!loaded)throw GLException("Buffer is not allocated");
    if(other == nullptr || !other->isCreated())throw GLException("Invalid buffer");

    glBindBuffer(GL_COPY_READ_BUFFER, other->getHandle());
    glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);

    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, readoffset, writeoffset, size);
}

///=============================================================================
void ffw::GLBuffer::mapBuffer(GLvoid** pointer, const GLenum access) const {
    if(!loaded || pointer == nullptr)throw GLException("Buffer is not allocated");
    *pointer = glMapBuffer(buffertype, access);
}

///=============================================================================
void ffw::GLBuffer::unMapBuffer() const {
    if(!loaded)throw GLException("Buffer is not allocated");
    glUnmapBuffer(buffertype);
}

///=============================================================================
void ffw::GLBuffer::mapBufferRange(GLvoid** pointer, const GLsizei offset,
    const GLsizei size, const GLenum access) const {

    if (!loaded || pointer == nullptr)throw GLException("Buffer is not allocated");
    *pointer = glMapBufferRange(buffertype, offset, size, access);
}

///=============================================================================
void ffw::GLBuffer::flushMappedBufferRange(const GLsizei offset, const GLsizei size) const {
    if (!loaded)throw GLException("Buffer is not allocated");
    glFlushMappedBufferRange(buffertype, offset, size);
}

///=============================================================================
void ffw::GLBuffer::bind() const {
    // bind buffer
    if(loaded)glBindBuffer(buffertype, buffer);
}

///=============================================================================
void ffw::GLBuffer::unbind() const {
    // UnBind buffer
    glBindBuffer(buffertype, 0);
}


