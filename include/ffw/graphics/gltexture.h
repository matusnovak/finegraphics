/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_TEXTURE_BASE
#define FFW_GRAPHICS_TEXTURE_BASE

#include "glrenderextensions.h"

namespace ffw {
    /**
     * @ingroup graphics
     * @brief Base class for all texture types
     */
    class FFW_API GLTexture {
    public:
        enum Filtering {
            NEAREST,
            LINEAR,
            MIPMAP_NEAREST,
            MIPMAP_LINEAR
        };
        enum Wrapping {
            REPEAT,
            MIRRORED_REPEAT,
            CLAMP_TO_EDGE,
        };
        GLTexture();
        GLTexture(const GLTexture& other) = delete;
        GLTexture(GLTexture&& other) NOEXCEPT;
        void swap(GLTexture& other) NOEXCEPT;
        virtual ~GLTexture();
        inline bool isCreated() const {
            return loaded;
        }
        /**
        * @brief Releases the resources
        */
        void destroy();
        /**
         * @brief Binds the texture
         */
        void bind() const;
        /**
         * @brief Unbinds the texture
         * @note After the unbind the active texture will be set to no handle (zero)
         */
        void unbind() const;
        /**
         * @brief Returns the OpenGL pointer, a handle to the texture
         */
        inline GLuint getHandle() const {
            return buffer;
        }
        /**
         * @brief Returns the width of the texture
         */
        inline GLsizei getWidth() const {
            return width;
        }
        /**
         * @brief Returns the height of the texture
         * @brief If the texture is 1D texture, the returned
         * type is always 1.
         */
        inline GLsizei getHeight() const {
            return height;
        }
        /**
         * @brief Returns the number of layers
         * @details If the texture is not an array, the returned
         * value is always 1.
         */
        inline GLsizei getLayers() const {
            return layers;
        }
        /**
         * @brief Returns the depth of the texture
         * @brief This only applies to 3D texture, otherwise
         * returns 1.
         */
        inline GLsizei getDepth() const {
            return depth;
        }
        /***
         * @brief Returns the number of samples
         * @details This only applies to multi-samples textures,
         * otherwise returns 1.
         */
        inline GLsizei getSamples() const {
            return samples;
        }
        /**
         * @brief Returns the number of color components in the texture
         * @details The internal format can be GL_RGB8, GL_RGBA8, GL_RGB32F, etc...
         */
        inline GLenum getInternalFormat() const {
            return internalformat;
        }
        /**
         * @brief Returns the format of the pixel data
         * @details The format can be GL_RGB, GL_RED, GL_RGBA, etc...
         */
        inline GLenum getFormat() const {
            return format;
        }
        /**
         * @brief Returns the data type of the pixel data
         * @details The pixel format can be GL_UNSIGNED_BYTE, GL_FLOAT, etc...
         */
        inline GLenum getPixelFormat() const {
            return pixelformat;
        }
        /**
         * @brief Returns the type of the texture
         * @details The texture format can be GL_TEXTURE_1D, GL_TEXTURE_2D, etc...
         */
        inline GLenum getTextureFormat() const {
            return textureformat;
        }
        inline bool isCompressed() const {
            switch (internalformat) {
                case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
                case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
                case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
                case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
                case GL_COMPRESSED_RED_RGTC1:
                case GL_COMPRESSED_RG_RGTC2:
                case GL_COMPRESSED_SIGNED_RED_RGTC1:
                case GL_COMPRESSED_SIGNED_RG_RGTC2:
                    return true;
                default:
                    return false;
            }
        }
        /**
         * @throws GLException if the texture is not allocated
         */
        void setEnvParami(GLenum target, GLenum name, GLint value) const;
        /**
         * @throws GLException if the texture is not allocated
         */
        void setEnvParamf(GLenum target, GLenum name, GLfloat value) const;
        /**
         * @throws GLException if the texture is not allocated
         */
        void setTexParami(GLenum name, GLint value) const;
        /**
         * @throws GLException if the texture is not allocated
         */
        void setTexParamiv(GLenum name, const GLint* value) const;
        /**
         * @throws GLException if the texture is not allocated
         */
        void setTexParamf(GLenum name, GLfloat value) const;
        /**
         * @throws GLException if the texture is not allocated
         */
        void setTexParamfv(GLenum name, const GLfloat* value) const;
        /**
         * @brief Generates mip maps
         * @throws GLException if the texture is not allocated
         */
        void generateMipmaps();
        /**
         * @throws GLException if the texture is not allocated
         */
        void setFiltering(GLTexture::Filtering filtering) const;
        /**
         * @throws GLException if the texture is not allocated
         */
        void setWrapping(GLTexture::Wrapping wrapping) const;
        GLTexture& operator = (const GLTexture& other) = delete;
        GLTexture& operator = (GLTexture&& other) NOEXCEPT;
    protected:
        inline GLsizei getBlockSize(const GLsizei width, const GLsizei height = 1, const GLsizei depth = 1) const {
            //if (width < 4 || height < 4)return width * height * depth;
            switch(internalformat) {
                case GL_COMPRESSED_RED_RGTC1:
                case GL_COMPRESSED_SIGNED_RED_RGTC1:
                case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
                case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
                    return ((width+3)/4) * ((height+3)/4) * depth * 8;   
                case GL_COMPRESSED_RG_RGTC2:
                case GL_COMPRESSED_SIGNED_RG_RGTC2:
                case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
                case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
                    return ((width+3)/4) * ((height+3)/4) * depth * 16;
                default:
                    return 0;
            }
        }
        bool loaded;
        GLenum textureformat;
        GLenum internalformat;
        GLenum format;
        GLenum pixelformat;
        GLuint buffer;
        GLsizei width;
        GLsizei height;
        GLsizei depth;
        GLsizei layers;
        bool mipmaps;
        bool initialized;
        GLsizei samples;
        bool compressed;
    };
};

inline void swap(ffw::GLTexture& first, ffw::GLTexture& second) NOEXCEPT {
    first.swap(second);
}
#endif
