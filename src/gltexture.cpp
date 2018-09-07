/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/gltexture.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLTexture::GLTexture() {
    loaded = false;
    textureformat = 0;
    internalformat = 0;
    format = 0;
    pixelformat = 0;
    buffer = 0;
    width = 0;
    height = 0;
    depth = 0;
    layers = 0;
    mipmaps = false;
    initialized = false;
    samples = 0;
    compressed = false;
}

///=============================================================================
ffw::GLTexture::GLTexture(GLTexture&& other) NOEXCEPT {
    loaded = false;
    textureformat = 0;
    internalformat = 0;
    format = 0;
    pixelformat = 0;
    buffer = 0;
    width = 0;
    height = 0;
    depth = 0;
    layers = 0;
    mipmaps = false;
    initialized = false;
    samples = 0;
    compressed = false;
    swap(other);
}

///=============================================================================
void ffw::GLTexture::swap(GLTexture& other) NOEXCEPT {
    if (this != &other) {
        using std::swap;
        swap(loaded, other.loaded);
        swap(textureformat, other.textureformat);
        swap(internalformat, other.internalformat);
        swap(format, other.format);
        swap(pixelformat, other.pixelformat);
        swap(buffer, other.buffer);
        swap(width, other.width);
        swap(height, other.height);
        swap(depth, other.depth);
        swap(layers, other.layers);
        swap(mipmaps, other.mipmaps);
        swap(initialized, other.initialized);
        swap(samples, other.samples);
        swap(compressed, other.compressed);
    }
}

///=============================================================================
ffw::GLTexture& ffw::GLTexture::operator = (GLTexture&& other) NOEXCEPT {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLTexture::~GLTexture(){
    destroy();
}

///=============================================================================
void ffw::GLTexture::destroy() {
    // Delete texture
    if (loaded)glDeleteTextures(1, &buffer);
    // reset variables
    loaded = false;
    //textureformat = 0;
    internalformat = 0;
    format = 0;
    pixelformat = 0;
    buffer = 0;
    width = 0;
    height = 0;
    depth = 0;
    layers = 0;
    mipmaps = false;
    initialized = false;
    samples = 0;
    compressed = false;
}

///=============================================================================
void ffw::GLTexture::generateMipmaps(){
    if (!loaded)throw GLException("Texture is not allocated");
    bind();
    glGenerateMipmap(textureformat);
    mipmaps = true;
}

///=============================================================================
void ffw::GLTexture::setEnvParami(const GLenum target, const GLenum name, const GLint value) const {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(textureformat, buffer);
    glTexEnvi(target, name, value);
}

///=============================================================================
void ffw::GLTexture::setEnvParamf(const GLenum target, const GLenum name, const GLfloat value) const {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(textureformat, buffer);
    glTexEnvf(target, name, value);
}

///=============================================================================
void ffw::GLTexture::setTexParami(const GLenum name, const GLint value) const {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(textureformat, buffer);
    glTexParameteri(textureformat, name, value);
}

///=============================================================================
void ffw::GLTexture::setTexParamf(const GLenum name, const GLfloat value) const {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(textureformat, buffer);
    glTexParameterf(textureformat, name, value);
}

///=============================================================================
void ffw::GLTexture::setTexParamiv(const GLenum name, const GLint* value) const {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(textureformat, buffer);
    glTexParameteriv(textureformat, name, value);
}

///=============================================================================
void ffw::GLTexture::setTexParamfv(const GLenum name, const GLfloat* value) const {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(textureformat, buffer);
    glTexParameterfv(textureformat, name, value);
}

///=============================================================================
void ffw::GLTexture::setFiltering(const GLTexture::Filtering filtering) const {
    switch (filtering) {
        case GLTexture::Filtering::NEAREST: {
            setTexParami(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            setTexParami(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;
        }
        case GLTexture::Filtering::LINEAR: {
            setTexParami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            setTexParami(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            break;
        }
        case GLTexture::Filtering::MIPMAP_NEAREST: {
            setTexParami(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            setTexParami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            break;
        }
        case GLTexture::Filtering::MIPMAP_LINEAR: {
            setTexParami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            setTexParami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            break;
        }
        default: {
            break;
        }
    }
}

///=============================================================================
void ffw::GLTexture::setWrapping(const GLTexture::Wrapping wrapping) const {
    if (!loaded)throw GLException("Texture is not allocated");
    switch (wrapping) {
        case GLTexture::Wrapping::REPEAT: {
            setTexParami(GL_TEXTURE_WRAP_S, GL_REPEAT);
            setTexParami(GL_TEXTURE_WRAP_T, GL_REPEAT);
            setTexParami(GL_TEXTURE_WRAP_R, GL_REPEAT);
            break;
        }
        case GLTexture::Wrapping::MIRRORED_REPEAT: {
            setTexParami(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            setTexParami(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            setTexParami(GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
            break;
        }
        case GLTexture::Wrapping::CLAMP_TO_EDGE: {
            setTexParami(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            setTexParami(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            setTexParami(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            break;
        }
        default: {
            break;
        }
    }
}

///=============================================================================
void ffw::GLTexture::bind() const{
    if(loaded)glBindTexture(textureformat, buffer);
}

///=============================================================================
void ffw::GLTexture::unbind() const{
    if(loaded)glBindTexture(textureformat, 0);
}
