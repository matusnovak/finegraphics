/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_FRAMEBUFFER
#define FFW_GRAPHICS_FRAMEBUFFER

#include "glrenderextensions.h"
#include "gltexture2d.h"
#include "gltexture2dms.h"
#include "glrenderbuffer2d.h"
#include "glrenderbuffer2dms.h"
#include "gltexturecubemap.h"
#include <functional>

namespace ffw {
    /**
     * @ingroup graphics
     */
    class FFW_API GLFramebuffer {
    public:
        class Attachment {
        public:
            Attachment(const ffw::GLTexture2D* texture, const GLenum attachment, const GLint level = 0) {
                action = [=](GLFramebuffer& fbo){
                    fbo.addTexture(attachment, GL_TEXTURE_2D, texture->getHandle(), level);
                };
            }
            Attachment(const ffw::GLTexture2DMS* texture, const GLenum attachment, const GLint level = 0) {
                action = [=](GLFramebuffer& fbo) {
                    fbo.addTexture(attachment, GL_TEXTURE_2D_MULTISAMPLE, texture->getHandle(), level);
                };
            }
            Attachment(const ffw::GLRenderbuffer2D* texture, const GLenum attachment, const GLint level = 0) {
                action = [=](GLFramebuffer& fbo) {
                    fbo.addRenderbuffer(attachment, texture->getHandle());
                };
            }
            Attachment(const ffw::GLRenderbuffer2DMS* texture, const GLenum attachment, const GLint level = 0) {
                action = [=](GLFramebuffer& fbo) {
                    fbo.addRenderbuffer(attachment, texture->getHandle());
                };
            }
            Attachment(const ffw::GLTextureCubemap* texture, const GLenum attachment, const int side, const GLint level = 0) {
                action = [=](GLFramebuffer& fbo) {
                    fbo.addTexture(attachment, GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, texture->getHandle(), level);
                };
            }
            void operator()(GLFramebuffer& fbo) const {
                action(fbo);
            }
        private:
            std::function<void(GLFramebuffer&)> action;
        };
        static const std::initializer_list<Attachment> NO_ATTACHMENTS;
        /**
         * @brief Constructs a framebuffer object using a list of attachments
         */
        GLFramebuffer(const std::initializer_list<Attachment>& attachments);
        template<typename Iterator>
        GLFramebuffer(Iterator begin, Iterator end):GLFramebuffer({}) {
            for (auto it = begin; it != end; ++it) {
                *it(*this);
            }
        }
        GLFramebuffer();
        GLFramebuffer(const GLFramebuffer& other) = delete;
        GLFramebuffer(GLFramebuffer&& other) NOEXCEPT;
        void swap(GLFramebuffer& other) NOEXCEPT;
        ~GLFramebuffer();
        /**
         * @brief Returns true if the framebuffer object has been created
         */
        inline bool isCreated() const {
            return created;
        }
        /**
         * @brief Attach a texture image to the framebuffer object
         * @param attachment Specifies the attachment point to which an image from texture should 
         *                   be attached. Must be one of the GL_COLOR_ATTACHMENT0, 
         *                   GL_DEPTH_ATTACHMENT, or GL_STENCIL_ATTACHMENT.
         * @param textype    Specifies the texture target. Must be one of the GL_TEXTURE_2D,
		 *                   GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		 *                   GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		 *                   GL_TEXTURE_CUBE_MAP_POSITIVE_Z, or GL_TEXTURE_CUBE_MAP_NEGATIVE_Z.
		 * @param texture    Specifies the texture object whose image is to be attached. (the 
		 *                   handle returned by ffw::Texture::getHandle())
		 * @param level      Specifies the mipmap level of the texture image to be attached,
		 *                   which must be 0.
		 * @see ffw::Texture::getHandle
         */
        void addTexture(GLenum attachment, GLuint textype, GLuint texture, GLint level = 0) const;
        /**
         * @brief Attach a renderbuffer object to a framebuffer object
         * @param attachment Specifies the attachment point to which renderbuffer should be 
         *                   attached. Must be one of the GL_COLOR_ATTACHMENT0, 
         *                   GL_DEPTH_ATTACHMENT, or GL_STENCIL_ATTACHMENT.
         * @param texture    Specifies the renderbuffer object that is to be attached. (the 
		 *                   handle returned by ffw::Renderbuffer::getHandle())
		 * @see ffw::Renderbuffer::getHandle
         */
        void addRenderbuffer(GLenum attachment, GLuint texture) const;
        /**
         * @brief Attach a stencil texture to the framebuffer object
         * @param texture The texture that is to be attached.
         * @param level   The mipmap level, must be 0.
         */
        inline void addStencilTexture(const ffw::GLTexture2D* texture, const GLint level = 0) {
            addTexture(GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture->getHandle(), level);
        }
        /**
         * @brief Attach a stencil renderbuffer to the framebuffer object
         * @param texture The renderbuffer that is to be attached.
         * @param level   The mipmap level, must be 0.
         */
        inline void addStencilBuffer(const ffw::GLRenderbuffer2D* texture) {
            addRenderbuffer(GL_STENCIL_ATTACHMENT, texture->getHandle());
        }
        /**
         * @brief Attach a color texture to the framebuffer object
         * @param texture The texture that is to be attached.
         * @param level   The mipmap level, must be 0.
         */
        void addColorTexture(const ffw::GLTexture2D* texture, const GLint level = 0) {
            addTexture(GL_COLOR_ATTACHMENT0 + colorcount,
                GL_TEXTURE_2D, texture->getHandle(), level);
            colorcount++;
        }
        /**
         * @brief Attach a color cubemap texture to the framebuffer object
         * @param texture The texture that is to be attached.
         * @param side    The size of the cubemap to attach where 0 is positive X side followed by
         *                X negative (1), Y positive (2), Y negative (3), Z positive (4), 
         *                Z negative (5).
         * @param level   The mipmap level, must be 0.
         */
        void addCubemapTexture(const ffw::GLTextureCubemap* texture,
            const GLint side, const GLint level = 0) {
            addTexture(GL_COLOR_ATTACHMENT0 + colorcount,
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + side, texture->getHandle(), level);
            colorcount++;
        }
        /**
         * @brief Attach a depth texture to the framebuffer object
         * @param texture The texture that is to be attached.
         * @param level   The mipmap level, must be 0.
         */
        void addDepthTexture(const ffw::GLTexture2D* texture, const GLint level = 0) {
            addTexture(GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 
                texture->getHandle(), level);
        }
        /**
         * @brief Attach a color multisample texture to the framebuffer object
         * @param texture The texture that is to be attached.
         * @param level   The mipmap level, must be 0.
         */
        void addColorTextureMS(const ffw::GLTexture2DMS* texture, const GLint level = 0) {
            addTexture(GL_COLOR_ATTACHMENT0 + colorcount, GL_TEXTURE_2D_MULTISAMPLE,
                texture->getHandle(), level);
            colorcount++;
        }
        /**
         * @brief Attach a depth multisample texture to the framebuffer object
         * @param texture The texture that is to be attached.
         * @param level   The mipmap level, must be 0.
         */
        void addDepthTextureMS(const ffw::GLTexture2DMS* texture, const GLint level = 0) {
            addTexture(GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, 
                texture->getHandle(), level);
        }
        /**
         * @brief Attach a color renderbuffer to the framebuffer object
         * @param texture The renderbuffer that is to be attached.
         */
        void addColorRenderbuffer(const ffw::GLRenderbuffer2D* texture) {
            addRenderbuffer(GL_COLOR_ATTACHMENT0 + colorcount, 
                texture->getHandle());
            colorcount++;
        }
        /**
         * @brief Attach a depth renderbuffer to the framebuffer object
         * @param texture The renderbuffer that is to be attached.
         */
        void addDepthRenderbuffer(const ffw::GLRenderbuffer2D* texture) {
            addRenderbuffer(GL_DEPTH_ATTACHMENT, texture->getHandle());
        }
        /**
         * @brief Attach a color multisample renderbuffer to the framebuffer object
         * @param texture The renderbuffer that is to be attached.
         */
        void addColorRenderbufferMS(const ffw::GLRenderbuffer2DMS* texture) {
            addRenderbuffer(GL_COLOR_ATTACHMENT0 + colorcount, 
                texture->getHandle());
            colorcount++;
        }
        /**
         * @brief Attach a depth multisample renderbuffer to the framebuffer object
         * @param texture The renderbuffer that is to be attached.
         */
        void addDepthRenderbufferMS(const ffw::GLRenderbuffer2DMS* texture) {
            addRenderbuffer(GL_DEPTH_ATTACHMENT, texture->getHandle());
        }
        /**
         * @brief Check the completeness status of a framebuffer
         */
        bool checkStatus();
        /**
         * @brief Returns the named object of the framebuffer (the handle)
         */
        inline unsigned int getHandle() const {
            return fbo;
        }
        /**
         * @brief Resets the color count of the color attachments
         */
        inline void resetColorCount() {
            colorcount = 0;
        }
        /**
         * @brief Destroys the framebuffer object
         */
        bool destroy();
        /**
         * @brief Binds the framebuffer object as GL_FRAMEBUFFER
         */
        void bind() const;
        /**
         * @brief Unbinds the framebuffer object by setting the current GL_FRAMEBUFFER to zero
         */
        void unbind() const;
        GLFramebuffer& operator = (const GLFramebuffer& other) = delete;
        GLFramebuffer& operator = (GLFramebuffer&& other) NOEXCEPT;
    private:
        bool created;
        unsigned int fbo;
        int colorcount;
    };
};

inline void swap(ffw::GLFramebuffer& first, ffw::GLFramebuffer& second) NOEXCEPT {
    first.swap(second);
}
#endif
