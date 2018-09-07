/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/gltexture2darrayms.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLTexture2DArrayMS::GLTexture2DArrayMS() {
    textureformat = GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
}

///=============================================================================
ffw::GLTexture2DArrayMS::GLTexture2DArrayMS(GLTexture2DArrayMS&& other) NOEXCEPT : GLTexture2DArrayMS() {
    GLTexture::swap(other);
}

///=============================================================================
ffw::GLTexture2DArrayMS& ffw::GLTexture2DArrayMS::operator = (ffw::GLTexture2DArrayMS&& other) NOEXCEPT {
    if (this != &other) {
        GLTexture::swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLTexture2DArrayMS::GLTexture2DArrayMS(const GLsizei width, const GLsizei height, const GLsizei layers,
    const GLenum internalformat, const GLint samples){

    textureformat = GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
    loaded = true;

    this->width           = width;
    this->height          = height;
    this->layers          = layers;
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
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, buffer);

    glTexImage3DMultisample(
        GL_TEXTURE_2D_MULTISAMPLE_ARRAY, samples, internalformat, 
        width, height, layers, GL_FALSE
    );

    int test;
    glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0, GL_TEXTURE_WIDTH, &test);
    if (test != width) {
        destroy();
        throw GLException("Failed to allocate texture");
    }

    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
}

///=============================================================================
void ffw::GLTexture2DArrayMS::resize(const GLsizei width, const GLsizei height,
    const GLsizei layers, const GLint samples){

    if (!loaded)throw GLException("Texture is not allocated");
    if (width <= 0 || height <= 0 || layers <= 0)throw GLException("Invalid texture size");
    this->width = width;
    this->height = height;
    this->layers = layers;
    this->samples = samples;
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, buffer);
    glTexImage3DMultisample(
        GL_TEXTURE_2D_MULTISAMPLE_ARRAY, samples, internalformat, 
        width, height, layers, GL_FALSE
    );
}
