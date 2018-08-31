/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/glrenderbuffer2dms.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLRenderbuffer2DMS::GLRenderbuffer2DMS(GLRenderbuffer2DMS&& other) NOEXCEPT :GLRenderbuffer(std::move(other)) {
}

///=============================================================================
ffw::GLRenderbuffer2DMS& ffw::GLRenderbuffer2DMS::operator=(GLRenderbuffer2DMS&& other) noexcept {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLRenderbuffer2DMS::GLRenderbuffer2DMS(const GLsizei width, const GLsizei height, const GLenum internalformat, const GLint samples){
    loaded = true;

    glGenRenderbuffers(1, &buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, buffer);

    this->width = width;
    this->height = height;
    this->samples = samples;
    this->internalformat = internalformat;

    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);

    int test;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &test);
    if(test != int(internalformat)) {
        destroy();
        throw GLException("Failed to allocate renderbuffer");
    }
}

///=============================================================================
void ffw::GLRenderbuffer2DMS::resize(const GLsizei width, const GLsizei height, const GLint samples){
    if (!loaded)throw GLException("Renderbuffer is not allocated");
    this->width = width;
    this->height = height;
    this->samples = samples;
    glBindRenderbuffer(GL_RENDERBUFFER, buffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);
}