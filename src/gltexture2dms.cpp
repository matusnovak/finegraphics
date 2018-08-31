/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/gltexture2dms.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLTexture2DMS::GLTexture2DMS(){
    textureformat = GL_TEXTURE_2D_MULTISAMPLE;
}

///=============================================================================
ffw::GLTexture2DMS::GLTexture2DMS(GLTexture2DMS&& other) NOEXCEPT : GLTexture2DMS() {
    GLTexture::swap(other);
}

///=============================================================================
ffw::GLTexture2DMS& ffw::GLTexture2DMS::operator = (ffw::GLTexture2DMS&& other) NOEXCEPT {
    if (this != &other) {
        GLTexture::swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLTexture2DMS::GLTexture2DMS(const GLsizei width, const GLsizei height,
    const GLenum internalformat, const GLint samples){

    textureformat = GL_TEXTURE_2D_MULTISAMPLE;
    loaded = true;

    this->width           = width;
    this->height          = height;
    this->layers          = 0;
    this->depth           = 0;
    this->internalformat  = internalformat;
    this->format          = 0;
    this->pixelformat     = 0;
    this->samples         = samples;

    if (isCompressed()) {
        destroy();
        throw GLException("Can not create multisampled compressed texture");
    }

    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, buffer);

    glTexImage2DMultisample(
        GL_TEXTURE_2D_MULTISAMPLE, samples, internalformat,
        width, height, GL_FALSE
    );

    int test;
    glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_WIDTH, &test);
    if (test != width) {
        destroy();
        throw GLException("Failed to allocate texture");
    }

    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
}

///=============================================================================
void ffw::GLTexture2DMS::resize(const GLsizei width, const GLsizei height, const GLint samples){
    if (!loaded)throw GLException("Texture is not allocated");
    if (width <= 0 || height <= 0)throw GLException("Invalid texture size");
    this->width = width;
    this->height = height;
    this->samples = samples;
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, buffer);
    glTexImage2DMultisample(
        GL_TEXTURE_2D_MULTISAMPLE, samples, internalformat, 
        width, height, GL_FALSE
    );
}
