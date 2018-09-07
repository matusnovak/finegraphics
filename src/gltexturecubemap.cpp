/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/gltexturecubemap.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLTextureCubemap::GLTextureCubemap(){
    textureformat = GL_TEXTURE_CUBE_MAP;
}

///=============================================================================
ffw::GLTextureCubemap::GLTextureCubemap(GLTextureCubemap&& other) NOEXCEPT : GLTextureCubemap() {
    GLTexture::swap(other);
}

///=============================================================================
ffw::GLTextureCubemap& ffw::GLTextureCubemap::operator = (ffw::GLTextureCubemap&& other) NOEXCEPT {
    if (this != &other) {
        GLTexture::swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLTextureCubemap::GLTextureCubemap(const GLsizei width, const GLsizei height,
    const GLenum internalformat, const GLenum format, const GLenum pixelformat, 
    const GLvoid* pixels){

    textureformat = GL_TEXTURE_CUBE_MAP;
    loaded = true;

    glGenTextures(1, &buffer);
    glBindTexture(GL_TEXTURE_CUBE_MAP, buffer);

    this->width           = width;
    this->height          = height;
    this->layers          = 0;
    this->depth           = 0;
    this->internalformat  = internalformat;
    this->format          = format;
    this->pixelformat     = pixelformat;
    this->samples         = 0;

    for (auto i = 0; i < 6; i++) {
        if(isCompressed()) {
            if (glCompressedTexImage2D == nullptr) {
                destroy();
                throw GLException("glCompressedTexImage2D is not supported on this GL context");
            }

            glCompressedTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalformat, width, 
                height, 0, getBlockSize(width, height), pixels
            );
        } else {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalformat, width, 
                height, 0, format, pixelformat, pixels
            );
        }

        int test;
        glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_TEXTURE_WIDTH, &test);
        if (test != width) {
            destroy();
            throw GLException("Failed to allocate texture");
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
}

///=============================================================================
void ffw::GLTextureCubemap::resize(const GLsizei width, const GLsizei height){
    if (!loaded)throw GLException("Texture is not allocated");
    if(width <= 0 || height <= 0)throw GLException("Invalid texture size");
    this->width = width;
    this->height = height;
    glBindTexture(GL_TEXTURE_CUBE_MAP, buffer);
    for (auto i = 0; i < 6; i++) {
        if(isCompressed()) {
            glCompressedTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalformat, 
                width, height, 0, getBlockSize(width, height), nullptr
            );
        } else {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalformat, 
                width, height, 0, format, pixelformat, nullptr
            );
        }
    }
}

///=============================================================================
void ffw::GLTextureCubemap::setPixels(const GLint level, const GLint side, const GLvoid* pixels) {
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_CUBE_MAP, buffer);

    setPixelsInternal(level, side, pixels);
}

///=============================================================================
void ffw::GLTextureCubemap::setPixelsInternal(const GLint level, const GLint side, 
    const GLvoid* pixels) {

    const auto w = width >> level;
    const auto h = height >> level;

    if (isCompressed()) {
        glCompressedTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, level, internalformat,
            w, h, 0, getBlockSize(w, h), pixels
        );
    }
    else {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, level, internalformat,
            w, h, 0, format, pixelformat, pixels
        );
    }
}

///=============================================================================
void ffw::GLTextureCubemap::setPixels(const GLint level, const GLint xoffset, const GLint yoffset,
    const GLsizei width, const GLsizei height, const GLint side, const GLvoid* pixels){

    if (!loaded)throw GLException("Texture is not allocated");
    if (side < 0 || side >= 6)throw GLException("Incorrect cubemap side");
    glBindTexture(GL_TEXTURE_CUBE_MAP, buffer);

    setPixelsInternal(level, xoffset, yoffset, width, height, side, pixels);
}

///=============================================================================
void ffw::GLTextureCubemap::setPixelsInternal(const GLint level, const GLint xoffset,
    const GLint yoffset, const GLsizei width, const GLsizei height, const GLint side, 
    const GLvoid* pixels) {

    if (isCompressed()) {
        glCompressedTexSubImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, level, xoffset, yoffset, width,
            height, internalformat, getBlockSize(width, height), pixels
        );
    }
    else {
        glTexSubImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, level, xoffset, yoffset, width,
            height, format, pixelformat, pixels
        );
    }
}

/*///=============================================================================
bool ffw::GLTextureCubemap::setFromBuffer(const ImageBuffer& image, const GLint side, 
    const bool inverse) {

    if (!image.isAllocated())return false;
    if (image.getDepth() > 1)return false;

    const auto openglType = ffw::getOpenGLImageType(image.getImageType());
    if (!openglType) {
        return false;
    }

    if (image.isCompressed() && inverse)return false;

    if (isCreated()) {
        for(auto m = 0; m <= image.getNumOfMipMaps()-1; m++) {
            
            if(inverse) {
                if (m != 0)setPixelsInternal(m, side, nullptr); // Create mipmap
                for (auto i = 0; i < image.getHeight(m); i++) {
                    const auto ptr = &image.getMipMapPtr(m)[image.getStrideSize(m) * i];
                    setPixelsInternal(
                        m, 0, image.getHeight(m) - i - 1, 
                        image.getWidth(m), 1, side, ptr
                    );
                }
            }
            else {
                if (m != 0)setPixelsInternal(m, side, nullptr); // Create mipmap
                setPixelsInternal(
                    m, 0, 0, image.getWidth(m), image.getHeight(m), 
                    side, image.getMipMapPtr(m)
                );
            }
        }

        if(image.getNumOfMipMaps() > 0) {
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, image.getNumOfMipMaps()-1);
        }
    } else {
        return false;
    }

    return true;
}*/

///=============================================================================
void ffw::GLTextureCubemap::getPixels(GLvoid* pixels){
    if (!loaded)throw GLException("Texture is not allocated");
    glBindTexture(GL_TEXTURE_CUBE_MAP, buffer);
    glGetTexImage(GL_TEXTURE_CUBE_MAP, 0, format, pixelformat, pixels);
}
