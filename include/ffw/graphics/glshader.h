/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_SHADER
#define FFW_GRAPHICS_SHADER

#include "glrenderextensions.h"
#include <string>

namespace ffw {
    class RenderContext;
    class RenderExtensions;
    /**
     * @ingroup graphics
     */
    class FFW_API GLShader {
    public:
        GLShader();
        GLShader(GLenum type, const std::string& code);
        GLShader(const GLShader& other) = delete;
        GLShader(GLShader&& other) NOEXCEPT;
        virtual ~GLShader();
        GLShader& operator = (const GLShader& other) = delete;
        GLShader& operator = (GLShader&& other) NOEXCEPT;
        void swap(GLShader& other) NOEXCEPT;

        void destroy();
        inline GLint getHandle() const {
            return handle;
        }
        inline bool isCreated() const {
            return loaded;
        }
        inline GLenum getType() const {
            return type;
        }
    private:
        bool checkForShaderErrors(std::string& errorstr) const;
        
        bool loaded;
        GLuint handle;
        GLenum type;
    };
};

inline void swap(ffw::GLShader& first, ffw::GLShader& second) NOEXCEPT {
    first.swap(second);
}
#endif
