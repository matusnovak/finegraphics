/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/gltexture1d.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLTexture1D::GLTexture1D(){
    textureformat = GL_TEXTURE_1D;
}

///=============================================================================
ffw::GLTexture1D::GLTexture1D(GLTexture1D&& other) NOEXCEPT : GLTexture1D() {
    GLTexture::swap(other);
}

///=============================================================================
ffw::GLTexture1D& ffw::GLTexture1D::operator = (ffw::GLTexture1D&& other) NOEXCEPT {
    if (this != &other) {
        GLTexture::swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLTexture1D::GLTexture1D(const GLsizei width, const GLenum internalformat, const GLenum format,
    const GLenum pixelformat, const GLvoid* pixels){

    if (width <= 0)throw GLException("Invalid texture size");
    textureformat = GL_TEXTURE_1D;
    loaded = true;

    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_1D, buffer);

    this->width           = width;
    this->height          = 1;
    this->layers          = 0;
    this->depth           = 0;
    this->internalformat  = internalformat;
    this->format          = format;
    this->pixelformat     = pixelformat;
    this->samples         = 0;

    if(isCompressed()) {
        if (glCompressedTexImage1D == nullptr) {
            destroy();
            throw GLException("glCompressedTexImage1D is not supported on this GL context");
        }

        glCompressedTexImage1D(
            GL_TEXTURE_2D, 0, internalformat, 
            width, 0, getBlockSize(width), pixels
        );
    } else {
        glTexImage1D(GL_TEXTURE_1D, 0, internalformat, width, 0, format, pixelformat, pixels);
    }

    int test;
    glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &test);
    if (test != width) {
        destroy();
        throw GLException("Failed to allocate texture");
    }

    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
}

///=============================================================================
void ffw::GLTexture1D::resize(const GLsizei width, const GLvoid* pixels){
    if(!loaded)throw GLException("Texture is not allocated");
    if(width <= 0)throw GLException("Invalid texture size");
    this->width = width;
    glBindTexture(GL_TEXTURE_1D, buffer);
    if(isCompressed()) {
        glCompressedTexImage1D(
            GL_TEXTURE_2D, 0, internalformat, 
            width, 0, getBlockSize(width), pixels
        );
    } else {
        glTexImage1D(
            GL_TEXTURE_1D, 0, internalformat, 
            width, 0, format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTexture1D::setPixels(const GLint level, const GLint xoffset, 
    const GLsizei width, const GLvoid* pixels){

    if(!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_1D, buffer);
    if(isCompressed()) {
        glCompressedTexSubImage1D(
            GL_TEXTURE_2D, level, xoffset, width, 
            internalformat, getBlockSize(width), pixels
        );
    } else {
        glTexSubImage1D(GL_TEXTURE_1D, level, xoffset, width, format, pixelformat, pixels);
    }
}

///=============================================================================
void ffw::GLTexture1D::setPixels(const GLint level, const GLvoid* pixels){
    if(!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_1D, buffer);

    const auto w = width >> level;

    if(isCompressed()) {
        glCompressedTexImage1D(GL_TEXTURE_2D, level, internalformat, w, 0, getBlockSize(w), pixels);
    } else {
        glTexImage1D(GL_TEXTURE_1D, level, internalformat, w, 0, format, pixelformat, pixels);
    }
}

///=============================================================================
void ffw::GLTexture1D::getPixels(void* pixels) const {
    if(!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_1D, buffer);
    glGetTexImage(GL_TEXTURE_1D, 0, format, pixelformat, pixels);
}
