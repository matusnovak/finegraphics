/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_GL_VERTEX_ARRAY
#define FFW_GRAPHICS_GL_VERTEX_ARRAY

#include <vector>
#include <cstdint>
#include "glrenderextensions.h"

namespace ffw {
    class RenderContext;
    /**
     * @ingroup graphics
     * @brief A Vertex Array Object (VAO)
     * @details This is a vertex array object to be used with vertex buffer
     * object (VBO). An example code below:
     * @code
     * // Somewhere in your code
     * ffw::GLVertexBuffer vbo;
     * ffw::GLVertexArray vao;
     * ffw::GLProgram program;
     * 
     * // Initialization (only once)
     * try {
     *     // Create our shader (optional).
     *     program = ffw::GLProgram(...);
     *     
     *     // This will create the VAO object.
     *     // Once this line is completed, VAO is bound, so no need to
     *     // manually bind it.
     *     vao = ffw::GLVertexArray(true);
     * 
     *     // This will create the VBO object using some random "vertices" data.
     *     // Similarly as the VAO, this VBO is automatically bound after creation
     *     // (after the constructor is called)
     *     vbo = ffw::GLVertexBuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
     * 
     *     // Because both VAO and VBO are bound (during creation), we can
     *     // set the properties of the VAO by setting attribute pointers
     *     vao.setAttributePointerf(program.getAttributeLocation("position"), 3, 6 * sizeof(float), (void*)(0 * sizeof(float)));
     *     
     *     // Once we are done, we need to unbind the VAO so we won't
     *     // accidentally modify it.
     *     vao.unbind();
     * } catch (ffw::GLException& e) {
     *     std::cerr << "Failed to initialize shaders: " << e.what() << std::endl;
     *     return EXIT_FAILURE;
     * }
     * 
     * // Rendering (in a loop)
     * while (true) {
     *     // Bind the shader program and the VAO.
     *     // You do not need to bind the VBO! The VAO handles that for you!
     *     program.bind();
     *     vao.bind();
     *     
     *     // Set the uniforms (if any) and draw the arrays
     *     // Note that calling any functions that modify attribute values or pointers
     *     // will also modify the VAO, therefore invaliding what we have done
     *     // in the initialization. This includes "setAttributePointerf" and so on.
     *     program.drawArrays(GL_TRIANGLES, 0, ...);
     * 
     *     // Stop the program and unbind the VAO
     *     program.unbind();
     *     vao.unbind();
     * }
     * @endcode
     */
    class FFW_API GLVertexArray {
    public:
        /**
         * @brief Creates an empty OpenGL buffer object
         */
        GLVertexArray();
        /**
         * @brief Creates an OpenGL vertex array buffer
         * @throws GLException if something went wrong
         */
        GLVertexArray(bool create);
        GLVertexArray(const GLVertexArray& other) = delete;
        GLVertexArray(GLVertexArray&& other) NOEXCEPT;
        void swap(GLVertexArray& other) NOEXCEPT;

        virtual ~GLVertexArray();
        /**
         * @brief Returns true if the object has been allocated
         */
        inline bool isCreated() const {
            return buffer != 0;
        }
        /**
         * @brief Releases the resources
         */
        void destroy();
        /**
         * @brief Binds the buffer object
         */
        void bind() const;
        /**
         * @brief Unbinds the buffer object and sets the current buffer object to zero
         */
        void unbind() const;
        /**
         * @brief Returns the OpenGL named object (the handle)
         */
        inline GLuint getHandle() const {
            return buffer;
        }
        /**
         * @brief Enables a vertex attrib array at a specific location
         * @note This method is being called by setAttributePointerf
         */
        void enableVertexAttribArray(GLint location) const;
        /**
         * @brief Disables a vertex attrib array at a specific location
         */
        void disableVertexAttribArray(GLint location) const;
        /**
         * @brief Specify the location and data format of the array of generic 
         * vertex attributes at a specific index
         * @note This automatically calls enableVertexAttribArray with the location
         */
        void setAttributePointerf(GLint location, GLint size, GLsizei stride, const GLvoid* offset) const;
        /**
         * @brief Modify the rate at which generic vertex attributes advance during instanced rendering
         */
        void setAttributeDivisor(GLuint index, GLuint divisor) const;
        
        GLVertexArray& operator = (const GLVertexArray& other) = delete;
        GLVertexArray& operator = (GLVertexArray&& other) NOEXCEPT;
    protected:
        GLuint buffer;
    };
};

inline void swap(ffw::GLVertexArray& first, ffw::GLVertexArray& second) NOEXCEPT {
    first.swap(second);
}
#endif
