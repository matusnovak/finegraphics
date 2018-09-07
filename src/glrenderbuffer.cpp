/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/glrenderbuffer.h"

///=============================================================================
ffw::GLRenderbuffer::GLRenderbuffer() {
    loaded = false;
    width = 0;
    height = 0;
    samples = 0;
    buffer = 0;
    internalformat = 0;
}

///=============================================================================
ffw::GLRenderbuffer::GLRenderbuffer(GLRenderbuffer&& other) NOEXCEPT {
    loaded = false;
    width= 0;
    height = 0;
    samples = 0;
    buffer = 0;
    internalformat = 0;
    swap(other);
}

///=============================================================================
void ffw::GLRenderbuffer::swap(GLRenderbuffer& other) NOEXCEPT {
    if (this != &other) {
        using std::swap;
        swap(loaded, other.loaded);
        swap(width, other.width);
        swap(height, other.height);
        swap(samples, other.samples);
        swap(buffer, other.buffer);
        swap(internalformat, other.internalformat);
    }
}

///=============================================================================
ffw::GLRenderbuffer& ffw::GLRenderbuffer::operator = (GLRenderbuffer&& other) NOEXCEPT {
    if(this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLRenderbuffer::~GLRenderbuffer(){
    destroy();
}

///=============================================================================
void ffw::GLRenderbuffer::bind() const{
    if(!loaded)glBindRenderbuffer(GL_RENDERBUFFER, buffer);
}

///=============================================================================
void ffw::GLRenderbuffer::unbind() const{
    if(loaded)glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

///=============================================================================
void ffw::GLRenderbuffer::destroy(){
    // Delete texture
    if(loaded)glDeleteRenderbuffers(1, &buffer);
    // reset variables
    buffer = 0;
    loaded = false;
    width = 0;
    height = 0;
    samples = 0;
    internalformat = 0;
}
