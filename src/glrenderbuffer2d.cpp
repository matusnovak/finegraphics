/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/glrenderbuffer2d.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLRenderbuffer2D::GLRenderbuffer2D(GLRenderbuffer2D&& other) NOEXCEPT :GLRenderbuffer(std::move(other)) {
}

///=============================================================================
ffw::GLRenderbuffer2D& ffw::GLRenderbuffer2D::operator=(GLRenderbuffer2D&& other) noexcept {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLRenderbuffer2D::GLRenderbuffer2D(const GLsizei width, const GLsizei height, const GLenum internalformat){
    loaded = true;

    glGenRenderbuffers(1, &buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, buffer);

    this->width = width;
    this->height = height;
    this->samples = 0;
    this->internalformat = internalformat;

    glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);

    int test;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &test);
    if(test != int(internalformat)) {
        destroy();
        throw GLException("Failed to allocate renderbuffer");
    }
}

///=============================================================================
void ffw::GLRenderbuffer2D::resize(const GLsizei width, const GLsizei height){
    if(!loaded)throw GLException("Renderbuffer is not allocated");
    this->width = width;
    this->height = height;
    glBindRenderbuffer(GL_RENDERBUFFER, buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
}