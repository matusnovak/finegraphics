/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_RENDERBUFFER_2D
#define FFW_GRAPHICS_RENDERBUFFER_2D

#include "glrenderbuffer.h"

namespace ffw {
    class RenderContext;
    /**
     * @ingroup graphics
     */
    class FFW_API GLRenderbuffer2D: public GLRenderbuffer {
    public:
        GLRenderbuffer2D() = default;
        virtual ~GLRenderbuffer2D() = default;
        GLRenderbuffer2D(const GLRenderbuffer2D& other) = delete;
        GLRenderbuffer2D(GLRenderbuffer2D&& other) NOEXCEPT;
        GLRenderbuffer2D& operator = (const GLRenderbuffer2D& other) = delete;
        GLRenderbuffer2D& operator = (GLRenderbuffer2D&& other) NOEXCEPT;
        /**
         * @brief Allocates the renderbuffer
         * @throws GLException if allocation has failed
         */
        GLRenderbuffer2D(GLsizei width, GLsizei height, GLenum internalformat);
        /**
         * @throws GLException if renderbuffer is not allocated or width or height is invalid
         */
        void resize(GLsizei width, GLsizei height);
    };
};

inline void swap(ffw::GLRenderbuffer2D& first, ffw::GLRenderbuffer2D& second) NOEXCEPT {
    first.swap(second);
}
#endif
