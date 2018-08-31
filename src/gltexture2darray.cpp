/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/gltexture2darray.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLTexture2DArray::GLTexture2DArray() {
    textureformat = GL_TEXTURE_2D_ARRAY;
}

///=============================================================================
ffw::GLTexture2DArray::GLTexture2DArray(GLTexture2DArray&& other) NOEXCEPT {
    GLTexture::swap(other);
}

///=============================================================================
ffw::GLTexture2DArray& ffw::GLTexture2DArray::operator = (ffw::GLTexture2DArray&& other) NOEXCEPT {
    if (this != &other) {
        GLTexture::swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLTexture2DArray::GLTexture2DArray(const GLsizei width, const GLsizei height, const GLsizei layers,
    const GLenum internalformat, const GLenum format, const GLenum pixelformat, 
    const GLvoid* pixels){

    textureformat = GL_TEXTURE_2D_ARRAY;
    loaded = true;

    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_2D_ARRAY, buffer);

    this->width           = width;
    this->height          = height;
    this->layers          = layers;
    this->depth           = 0;
    this->internalformat  = internalformat;
    this->format          = format;
    this->pixelformat     = pixelformat;
    this->samples         = 0;

    if (isCompressed()) {
        if (glCompressedTexImage3D == nullptr) {
            destroy();
            throw GLException("glCompressedTexImage1D is not supported on this GL context");
        }

        glCompressedTexImage3D(
            GL_TEXTURE_2D_ARRAY, 0, internalformat, width, height, layers, 0,
            getBlockSize(width, height, layers), pixels
        );
    } else {
        glTexImage3D(
            GL_TEXTURE_2D_ARRAY, 0, internalformat, width, height, layers, 0, 
            format, pixelformat, pixels
        );
    }

    int test;
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &test);
    if (test != width) {
        destroy();
        throw GLException("Failed to allocate texture");
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
}

///=============================================================================
void ffw::GLTexture2DArray::resize(const GLsizei width, const GLsizei height,
    const GLsizei layers, const GLvoid* pixels){

    if (!loaded)throw GLException("Texture is not allocated");
    if (width <= 0 || height <= 0 || layers <= 0)throw GLException("Invalid texture size");
    this->width = width;
    this->height = height;
    this->layers = layers;
    glBindTexture(GL_TEXTURE_2D_ARRAY, buffer);

    if(isCompressed()) {
        glCompressedTexImage3D(
            GL_TEXTURE_2D_ARRAY, 0, internalformat, width, height, layers, 0, 
            getBlockSize(width, height, layers), pixels
        );
    } else {
        glTexImage3D(
            GL_TEXTURE_2D_ARRAY, 0, internalformat, width, height, layers, 0,
            format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture2DArray::setPixels(const GLint level, const GLint xoffset, const GLint yoffset,
    const GLint loffset, const GLsizei width, const GLsizei height, const GLvoid* pixels){

    if (!loaded)throw GLException("Texture is not allocated");

    glBindTexture(GL_TEXTURE_2D_ARRAY, buffer);

    if(isCompressed()) {
        glCompressedTexSubImage3D(
            GL_TEXTURE_2D_ARRAY, level, xoffset, yoffset, loffset, width, height, 
            1, internalformat, getBlockSize(width, height, 1), pixels
        );
    } else {
        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY, level, xoffset, yoffset, loffset, width, height, 
            1, format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture2DArray::setPixelsInternal(const GLint level, const GLint xoffset,
    const GLint yoffset, const GLint loffset, const GLsizei width, 
    const GLsizei height, const GLvoid* pixels) {

    if (isCompressed()) {
        glCompressedTexSubImage3D(
            GL_TEXTURE_2D_ARRAY, level, xoffset, yoffset, loffset, width, height,
            1, internalformat, getBlockSize(width, height, 1), pixels
        );
    }
    else {
        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY, level, xoffset, yoffset, loffset, width, height,
            1, format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture2DArray::setPixels(const GLint level, const GLvoid* pixels) {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_2D_ARRAY, buffer);

    const auto w = width >> level;
    const auto h = height >> level;

    if (isCompressed()) {
        glCompressedTexImage3D(
            GL_TEXTURE_2D_ARRAY, level, internalformat, w, h, layers, 0,
            getBlockSize(w, h, layers), pixels
        );
    }
    else {
        glTexImage3D(
            GL_TEXTURE_2D_ARRAY, level, internalformat, w, h, layers, 0,
            format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture2DArray::setPixelsInternal(const GLint level, const GLvoid* pixels) {
    const auto w = width >> level;
    const auto h = height >> level;

    if (isCompressed()) {
        glCompressedTexImage3D(
            GL_TEXTURE_2D_ARRAY, level, internalformat, w, h, layers, 0,
            getBlockSize(w, h, layers), pixels
        );
    }
    else {
        glTexImage3D(
            GL_TEXTURE_2D_ARRAY, level, internalformat, w, h, layers, 0,
            format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture2DArray::getPixels(GLvoid* pixels) const {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_2D_ARRAY, buffer);
    glGetTexImage(GL_TEXTURE_2D_ARRAY, 0, format, pixelformat, pixels);
}
