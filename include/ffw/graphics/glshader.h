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
    * @brief An OpenGL shader
    * @details An example code below:
    * @code
    * // Somewhere in your chode
    * ffw::GLProgram program;
    * ffw::GLShader vertShader;
    * ffw::GLShader fragShader;
    * 
    * // Initialization (run this only once)
    * try {
    *     // Compiles the shaders
    *     vertShader = ffw::GLShader(GL_VERTEX_SHADER, ...shader code here as string...);
    *     fragShader = ffw::GLShader(GL_FRAGMENT_SHADER, ...shader code here as string...);
    * 
    *     // Links the two shaders into one program
    *     program = ffw::GLProgram({ &vertShader, &fragShader });
    * } catch (ffw::GLException& e) {
    *     std::cerr << "Something went wrong: " << e.what() << std::endl;
    * }
    * 
    * // Rendering
    * while(true) {
    *     // Begin our shader program
    *     program.bind();
    * 
    *     // Bind VBOs, VAos, etc...
    *     // Bind uniforms, attributes...
    *     program.setUniformMatrix4fv(
    *         boxProgram.getUniformLocation("model"), &matrix[0], 1);
    *     
    *     // Draw the vertices using VBO
    *     program.drawArrays(GL_TRIANGLES, 0, 24);
    * 
    *     // Stops the shader program
    *     program.unbind();
    * }
    * @endcode
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
