/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_RENDERBUFFER
#define FFW_GRAPHICS_RENDERBUFFER

#include "glrenderextensions.h"

namespace ffw {
    /**
     * @ingroup graphics
     */
    class FFW_API GLRenderbuffer {
    public:
        /**
         * @brief Creates an empty renderbuffer storage
         */
        GLRenderbuffer();
        GLRenderbuffer(const GLRenderbuffer& other) = delete;
        GLRenderbuffer(GLRenderbuffer&& other) NOEXCEPT;
        void swap(GLRenderbuffer& other) NOEXCEPT;
        virtual ~GLRenderbuffer();
        /**
         * @brief Returns true if the renderbuffer has been allocated
         */
        inline bool isCreated() const {
            return loaded;
        }
        /**
         * @brief Destroys the renderbuffer
         * @details Destroys the renderbuffer and the allocated memory to it.
         * Calling this on already deleted texture has no effect.
         */
        void destroy();
        /**
         * @brief Binds the renderbuffer
         */
        void bind() const;
        /**
         * @brief Unbinds the texture
         * @note After the unbind the active texture will be set to no handle (zero)
         */
        void unbind() const;
        /**
         * @brief Returns the OpenGL pointer, a handle to the renderbuffer
         */
        inline GLuint getHandle() const {
            return buffer;
        }
        inline GLsizei getWidth() const {
            return width;
        }
        inline GLsizei getHeight() const {
            return height;
        }
        /**
         * @brief Returns the internal format used by the renderbuffer
         */
        inline GLenum getInternalFormat() const {
            return internalformat;
        }
        /**
         * @brief Returns the number of samples used by the renderbuffer
         * @details When ffw::Renderbuffer2D is used, the returned value is one.
         */
        inline GLsizei getSamples() const {
            return samples;
        }

        GLRenderbuffer& operator = (const GLRenderbuffer& other) = delete;
        GLRenderbuffer& operator = (GLRenderbuffer&& other) NOEXCEPT;
    protected:
        bool loaded;
        GLenum internalformat;
        GLuint buffer;
        GLsizei width;
        GLsizei height;
        GLsizei samples;
    };
};

inline void swap(ffw::GLRenderbuffer& first, ffw::GLRenderbuffer& second) NOEXCEPT {
    first.swap(second);
}
#endif
