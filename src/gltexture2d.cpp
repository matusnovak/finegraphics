/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/gltexture2d.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLTexture2D::GLTexture2D() {
    textureformat = GL_TEXTURE_2D;
}

///=============================================================================
ffw::GLTexture2D::GLTexture2D(GLTexture2D&& other) NOEXCEPT {
    GLTexture::swap(other);
}

///=============================================================================
ffw::GLTexture2D& ffw::GLTexture2D::operator = (ffw::GLTexture2D&& other) NOEXCEPT {
    if(this != &other) {
        GLTexture::swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLTexture2D::GLTexture2D(const GLsizei width, const GLsizei height, 
    const GLenum internalformat, const GLenum format, const GLenum pixelformat, 
    const GLvoid* pixels){

    create(width, height, internalformat, format, pixelformat, pixels);
}

void ffw::GLTexture2D::create(const GLsizei width, const GLsizei height, 
    const GLenum internalformat, const GLenum format, const GLenum pixelformat, 
    const GLvoid* pixels) {

    if (width <= 0 || height <= 0)throw GLException("Invalid texture size");
    textureformat = GL_TEXTURE_2D;
    loaded = true;

    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_2D, buffer);

    this->width = width;
    this->height = height;
    this->layers = 0;
    this->depth = 0;
    this->internalformat = internalformat;
    this->format = format;
    this->pixelformat = pixelformat;
    this->samples = 0;

    if (width % 2 != 0) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
    }

    if (isCompressed()) {
        if (glCompressedTexImage2D == nullptr) {
            destroy();
            throw GLException("glCompressedTexImage1D is not supported on this GL context");
        }

        glCompressedTexImage2D(
            GL_TEXTURE_2D, 0, internalformat, width, height,
            0, getBlockSize(width, height), pixels
        );
    }
    else {
        glTexImage2D(
            GL_TEXTURE_2D, 0, internalformat, width, height,
            0, format, pixelformat, pixels
        );
    }

    int test;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &test);
    if (test != width) {
        destroy();
        throw GLException("Failed to allocate texture");
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


///=============================================================================
void ffw::GLTexture2D::resize(const GLsizei width, const GLsizei height, const GLvoid* pixels){
    if (!loaded)throw GLException("Texture is not allocated");
    if (width <= 0 || height <= 0)throw GLException("Invalid texture size");
    this->width = width;
    this->height = height;
    glBindTexture(GL_TEXTURE_2D, buffer);

    if(isCompressed()) {
        glCompressedTexImage2D(
            GL_TEXTURE_2D, 0, internalformat, width, height, 
            0, getBlockSize(width, height), pixels
        );
    } else {
        glTexImage2D(
            GL_TEXTURE_2D, 0, internalformat, width, height, 
            0, format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture2D::setPixels(const GLint level, const GLvoid* pixels) {
    if(!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_2D, buffer);

    setPixelsInternal(level, pixels);
}

///=============================================================================
void ffw::GLTexture2D::setPixelsInternal(const GLint level, const GLvoid* pixels) const {
    const auto w = width >> level;
    const auto h = height >> level;

    if (isCompressed()) {
        glCompressedTexImage2D(
            GL_TEXTURE_2D, level, internalformat, w, h,
            0, getBlockSize(w, h), pixels
        );
    }
    else {
        glTexImage2D(
            GL_TEXTURE_2D, level, internalformat, w, h,
            0, format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture2D::setPixels(const GLint level, const GLint xoffset, const GLint yoffset,
    const GLsizei width, const GLsizei height, const GLvoid* pixels){

    if(!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_2D, buffer);

    setPixelsInternal(level, xoffset, yoffset, width, height, pixels);
}

///=============================================================================
void ffw::GLTexture2D::setPixelsInternal(const GLint level, const GLint xoffset, const GLint yoffset,
    const GLsizei width, const GLsizei height, const GLvoid* pixels) const {

    if (isCompressed()) {
        glCompressedTexSubImage2D(
            GL_TEXTURE_2D, level, xoffset, yoffset, width, height,
            internalformat, getBlockSize(width, height), pixels
        );
    }
    else {
        glTexSubImage2D(
            GL_TEXTURE_2D, level, xoffset, yoffset, width, height,
            format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture2D::getPixels(void* pixels) const {
    if(!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_2D, buffer);
    glGetTexImage(GL_TEXTURE_2D, 0, format, pixelformat, pixels);
}
