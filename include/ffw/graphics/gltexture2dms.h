/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_TEXTURE_2D_MS
#define FFW_GRAPHICS_TEXTURE_2D_MS

#include "gltexture.h"

namespace ffw {
    /**
     * @ingroup graphics
     * @brief OpenGL texture of type GL_TEXTURE_2D_MULTISAMPLE
     */
    class FFW_API GLTexture2DMS: public GLTexture {
    public:
        GLTexture2DMS();
        GLTexture2DMS(const GLTexture2DMS& other) = delete;
        GLTexture2DMS(GLTexture2DMS&& other) NOEXCEPT;
        virtual ~GLTexture2DMS() = default;
        /**
         * @brief Allocates the texture
         * @param width Specifies the width of the texture image.
         * @param height Specifies the height of the texture image.
         * @param internalformat The internal format to be used to store the multisample texture's 
         * image. internalformat must specify a color-renderable, depth-renderable, 
         * or stencil-renderable format. 
         * @param samples The number of samples in the multisample texture's image. 
         * @throws GLException if something went wrong
         * @details The following compressed internalformats are allowed: 
         * GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 
         * GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 
         * GL_COMPRESSED_RED_RGTC1, GL_COMPRESSED_RG_RGTC2, GL_COMPRESSED_SIGNED_RED_RGTC1,
         * GL_COMPRESSED_SIGNED_RG_RGTC2
         * @note The texture is automatically destroyed once destroy() is called, or the instance 
         * of this texture class is freed. The format and pixelformat is not used and therefore
         * set to zero (getPixelFormat and getInternalFormat will return value of zero).
         */
        GLTexture2DMS(GLsizei width, GLsizei height, GLenum internalformat, GLint samples);
        /**
         * @brief Resizes the texture
         * @param width Specifies the width of the texture image.
         * @param height Specifies the height of the texture image.
         * @param samples The number of samples in the multisample texture's image. 
         * @note The internalformat is unchanged.
         * @throws GLException if the texture has not been allocated
         */
        void resize(GLsizei width, GLsizei height, GLint samples);
        GLTexture2DMS& operator = (const GLTexture2DMS& other) = delete;
        GLTexture2DMS& operator = (GLTexture2DMS&& other) NOEXCEPT;
    };
};

inline void swap(ffw::GLTexture2DMS& first, ffw::GLTexture2DMS& second) NOEXCEPT {
    first.swap(second);
}
#endif
