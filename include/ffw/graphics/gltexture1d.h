/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_TEXTURE_1D
#define FFW_GRAPHICS_TEXTURE_1D

#include "gltexture.h"

namespace ffw {
    /**
     * @ingroup graphics
     * @brief OpenGL texture of type GL_TEXTURE_1D
     */
    class FFW_API GLTexture1D: public GLTexture {
    public:
        GLTexture1D();
        GLTexture1D(const GLTexture1D& other) = delete;
        GLTexture1D(GLTexture1D&& other) NOEXCEPT;
        virtual ~GLTexture1D() = default;
        /**
         * @brief Allocates the texture
         * @param width Specifies the width of the texture image.
         * @param internalformat Specifies the number of color components in the texture.
         * @param format Specifies the format of the pixel data. The following symbolic values are 
         * accepted: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER,
         * GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER, GL_STENCIL_INDEX, 
         * GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
         * @param pixelformat Specifies the data type of the pixel data. The following symbolic 
         * values are accepted: GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, 
         * GL_UNSIGNED_INT, GL_INT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, 
         * GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4, 
         * GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV,
         * GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, 
         * and GL_UNSIGNED_INT_2_10_10_10_REV. Compressed formats are also supported. 
         * @param pixels Optional array to the pixels buffer that will be used to initialise the 
         * texture storage. The pixel array must be correct size, otherwise a segmentation fault
         * will occur. If null, the texture storage is not set and initialised with random data.
         * @throws GLException if something went wrong
         * @details The following compressed internalformats are allowed: 
         * GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 
         * GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 
         * GL_COMPRESSED_RED_RGTC1, GL_COMPRESSED_RG_RGTC2, GL_COMPRESSED_SIGNED_RED_RGTC1,
         * GL_COMPRESSED_SIGNED_RG_RGTC2
         * @note The texture is automatically destroyed once destroy() is called, or the instance 
         * of this texture class is freed.
         */
        GLTexture1D(GLsizei width, GLenum internalformat, GLenum format, GLenum pixelformat,
            const GLvoid* pixels = nullptr);
        /**
         * @brief Resizes the texture
         * @param width The new width of the texture
         * @param pixels Optional array to the pixels buffer that will be used to initialise the 
         * texture storage. The pixel array must be correct size, otherwise a segmentation fault
         * will occur. If null, the texture storage is not set and initialised with random data.
         * @throws GLException if the texture has not been allocated
         * @note The format, internalformat, and pixelformat are unchanged.
         */
        void resize(GLsizei width, const GLvoid* pixels = nullptr);
        /**
         * @brief Sets the pixels of the entire texture
         * @param level The mipmap level to set. Zero by default.
         * @param pixels Non null pointer to the array of the pixels to upload.
         * @throws GLException if the texture has not been allocated
         */
        void setPixels(GLint level, const GLvoid* pixels);
        /**
         * @brief Sets the pixels of the texture section
         * @param level The mipmap level to set. Zero by default.
         * @param xoffset The x offset of the target area to set.
         * @param width The width of the area to set.
         * @param pixels Non null pointer to the array of the pixels to upload.
         * @throws GLException if the texture has not been allocated
         */
        void setPixels(GLint level, GLint xoffset, GLsizei width, const GLvoid* pixels);
        /**
         * @brief Returns the pixels of the entire texture
         * @param pixels Non null pointer to an allocated array that will hold the entire
         * texture data. 
         * @throws GLException if the texture has not been allocated
         */
        void getPixels(void* pixels) const;
        GLTexture1D& operator = (const GLTexture1D& other) = delete;
        GLTexture1D& operator = (GLTexture1D&& other) NOEXCEPT;
    };
};

inline void swap(ffw::GLTexture1D& first, ffw::GLTexture1D& second) NOEXCEPT {
    first.swap(second);
}
#endif
