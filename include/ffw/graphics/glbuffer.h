/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_GL_BUFFER
#define FFW_GRAPHICS_GL_BUFFER

#include <vector>
#include <cstdint>
#include "glrenderextensions.h"

namespace ffw {
    class RenderContext;
    /**
     * @ingroup graphics
     */
    class FFW_API GLBuffer {
    public:
        /**
         * @brief Creates an empty OpenGL buffer object
         */
        GLBuffer();
        /**
         * @brief Creates an OpenGL buffer object with specific target type
         * @param buffertype Allowed values are GL_ARRAY_BUFFER, GL_ATOMIC_COUNTER_BUFFER, 
         *                   GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, GL_DISPATCH_INDIRECT_BUFFER,
         *                   GL_DRAW_INDIRECT_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER,
         *                   GL_PIXEL_UNPACK_BUFFER, GL_QUERY_BUFFER, GL_SHADER_STORAGE_BUFFER,
         *                   GL_TEXTURE_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER, or
         *                   GL_UNIFORM_BUFFER
         * @param data Specifies a pointer to data that will be copied into the data store for
         *             initialization, or NULL if no data is to be copied.
         * @param size Specifies the size in bytes of the buffer object's new data store.
         * @param type Specifies the expected usage pattern of the data store. 
         *             The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, 
         *             GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY,
         *             GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
         * @throws GLException if something went wrong
         */
        GLBuffer(GLenum buffertype, const GLvoid* data, GLsizei size, GLenum type);
        GLBuffer(const GLBuffer& other) = delete;
        GLBuffer(GLBuffer&& other) NOEXCEPT;
        void swap(GLBuffer& other) NOEXCEPT;

        virtual ~GLBuffer();
        /**
         * @brief Returns true if the object has been allocated
         */
        inline bool isCreated() const {
            return loaded;
        }
        /**
         * @brief Resizes the buffer and copies the data
         * @param data Specifies a pointer to data that will be copied into the data store for
         *             initialization, or NULL if no data is to be copied.
         * @param size Specifies the size in bytes of the buffer object's new data store.
         * @throws GLException if buffer is not created or if the buffer re-allocation failed
         */
        void resize(const GLvoid* data, GLsizei size);
        /**
         * @brief Updates a subset of the buffer with data
         * @param data   Specifies a pointer to the new data that will be copied into the
         *               data store. 
         * @param offset Specifies the offset into the buffer object's data store where data 
         *               replacement will begin, measured in bytes. 
         * @param size   Specifies the size in bytes of the data store region being replaced.
         * @throws GLException if buffer is not created
         */
        void setData(const GLvoid* data, GLsizei offset, GLsizei size);
        /**
         * @brief Map all of a buffer object's data store into the client's address space
         * @param pointer Pointer to the client space address. The data can then be directly 
         *                read and/or written relative to the pointer.
         * @param access  Specifies the access policy for glMapBuffer and glMapNamedBuffer, 
         *                indicating whether it will be possible to read from, write to, or both 
         *                read from and write to the buffer object's mapped data store. The 
         *                symbolic constant must be GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE.
         * @throws GLException if buffer is not created
         */
        void mapBuffer(GLvoid** pointer, GLenum access) const;
        /**
         * @brief Map all or part of a buffer object's data store into the client's address space
         * @param pointer Pointer to the client space address. The data can then be directly 
         *                read and/or written relative to the pointer.
         * @param offset  Specifies the starting offset within the buffer of the range to be mapped.
         * @param size    Specifies the length of the range to be mapped.
         * @param access  Specifies the access policy for glMapBuffer and glMapNamedBuffer, 
         *                indicating whether it will be possible to read from, write to, or both 
         *                read from and write to the buffer object's mapped data store. The 
         *                symbolic constant must be GL_READ_ONLY, GL_WRITE_ONLY, or GL_READ_WRITE.
         * @throws GLException if buffer is not created
         */
        void mapBufferRange(GLvoid** pointer, GLsizei offset, GLsizei size, GLenum access) const;
        /**
         * @brief Indicate modifications to a range of a mapped buffer.
         * @param offset  Specifies the start of the buffer subrange, in bytes.
         * @param size    Specifies the length of the buffer subrange, in bytes. 
         * @throws GLException if buffer is not created
         */
        void flushMappedBufferRange(GLsizei offset, GLsizei size) const;
        /**
         * @brief Release the mapping of a buffer object's data store 
         *        into the client's address space
         * @throws GLException if buffer is not created
         */
        void unMapBuffer() const;
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
         * @brief Returns the size of the buffer in bytes
         */
        inline GLsizei getSize() const {
            return size;
        }
        /**
         * @brief Returns the access type of the buffer as GL_READ_ONLY, 
         *        GL_WRITE_ONLY, or GL_READ_WRITE
         */
        inline GLenum getAccessType() const {
            return accesstype;
        }
        /**
         * @brief Returns the object type of the buffer specified during the constructor
         */
        inline GLenum getBufferType() const {
            return buffertype;
        }
        /**
         * @brief Copy all or part of the data store of a buffer object to the data store of 
         *        another buffer object
         * @param other       The other source object to copy data from
         * @param readoffset  Specifies the offset, in bytes, within the data store
         *                    of the source buffer object at which data will be read. 
         * @param writeoffset Specifies the offset, in bytes, within the data store 
         *                    of the destination buffer object at which data will be written.
         * @param size        Specifies the size, in bytes, of the data to be copied 
         *                    from the source buffer object to the destination buffer object.
         * @throws GLException if buffer is not created or if the other buffer is invalid
         */
        void copyFrom(const GLBuffer* other, GLintptr readoffset,
            GLintptr writeoffset, GLsizeiptr size);
        /**
         * @brief Reads a subset of a buffer object's data store
         * @param data   Specifies a pointer to the location where buffer object data is returned.
         * @param offset Specifies the offset into the buffer object's data store from which data 
         *               will be returned, measured in bytes. 
         * @param size   Specifies the size in bytes of the data store region being returned.
         * @throws GLException if buffer is not created
         */
        void getData(GLvoid* data, GLsizei offset, GLsizei size);
        /**
        * @brief Returns a subset of a buffer object's data store
        * @param offset Specifies the offset into the buffer object's data store from which data
        *               will be returned, measured in bytes.
        * @param size   Specifies the size in bytes of the data store region being returned.
        * @returns a vector of uint8_t
        * @throws GLException if buffer is not created
        */
        std::vector<uint8_t> getData(GLsizei offset, GLsizei size);
        GLBuffer& operator = (const GLBuffer& other) = delete;
        GLBuffer& operator = (GLBuffer&& other) NOEXCEPT;
    protected:
        GLenum accesstype;
        GLenum buffertype;
        bool loaded;
        GLuint buffer;
        GLsizei size;
    };
    /**
     * @ingroup graphics
     * @brief GLBuffer of type GL_ARRAY_BUFFER
     * @param data Specifies a pointer to data that will be copied into the data store for
     *             initialization, or NULL if no data is to be copied.
     * @param size Specifies the size in bytes of the buffer object's new data store.
     * @param type Specifies the expected usage pattern of the data store. 
     *             The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, 
     *             GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY,
     *             GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
     */
    class FFW_API GLVertexBuffer: public GLBuffer {
    public:
        GLVertexBuffer() = default;
        GLVertexBuffer(const GLvoid* data, const GLsizei size, const GLenum type):
        GLBuffer(GL_ARRAY_BUFFER, data, size, type) {
            
        }
    };
    /**
     * @ingroup graphics
     * @brief GLBuffer of type GL_ELEMENT_ARRAY_BUFFER
     * @param data Specifies a pointer to data that will be copied into the data store for
     *             initialization, or NULL if no data is to be copied.
     * @param size Specifies the size in bytes of the buffer object's new data store.
     * @param type Specifies the expected usage pattern of the data store. 
     *             The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, 
     *             GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY,
     *             GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
     */
    class FFW_API GLElementBuffer: public GLBuffer {
    public:
        GLElementBuffer() = default;
        GLElementBuffer(const GLvoid* data, const GLsizei size, const GLenum type):
        GLBuffer(GL_ELEMENT_ARRAY_BUFFER, data, size, type) {
            
        }
    };
};

inline void swap(ffw::GLBuffer& first, ffw::GLBuffer& second) NOEXCEPT {
    first.swap(second);
}
inline void swap(ffw::GLVertexBuffer& first, ffw::GLVertexBuffer& second) NOEXCEPT {
    first.swap(second);
}
inline void swap(ffw::GLElementBuffer& first, ffw::GLElementBuffer& second) NOEXCEPT {
    first.swap(second);
}
#endif
