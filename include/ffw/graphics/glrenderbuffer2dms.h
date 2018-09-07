/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_RENDERBUFFER_2D_MS
#define FFW_GRAPHICS_RENDERBUFFER_2D_MS

#include "glrenderbuffer.h"

namespace ffw {
    class RenderContext;
    /**
     * @ingroup graphics
     */
    class FFW_API GLRenderbuffer2DMS: public GLRenderbuffer {
    public:
        GLRenderbuffer2DMS() = default;
        virtual ~GLRenderbuffer2DMS() = default;
        GLRenderbuffer2DMS(const GLRenderbuffer2DMS& other) = delete;
        GLRenderbuffer2DMS(GLRenderbuffer2DMS&& other) NOEXCEPT;
        GLRenderbuffer2DMS& operator = (const GLRenderbuffer2DMS& other) = delete;
        GLRenderbuffer2DMS& operator = (GLRenderbuffer2DMS&& other) NOEXCEPT;
        /**
         * @brief Allocates the renderbuffer
         * @throws GLException if allocation has failed
         */
        GLRenderbuffer2DMS(GLsizei width, GLsizei height, GLenum internalformat, GLint samples);
        /**
         * @throws GLException if renderbuffer is not allocated or width or height is invalid
         */
        void resize(GLsizei width, GLsizei height, GLint samples);
    };
};

inline void swap(ffw::GLRenderbuffer2DMS& first, ffw::GLRenderbuffer2DMS& second) NOEXCEPT {
    first.swap(second);
}
#endif
