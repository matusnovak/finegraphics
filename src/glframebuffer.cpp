/*** This file is part of FineFramework project ***/

#include <utility>
#include "ffw/graphics/glframebuffer.h"
#include "ffw/graphics/exceptions.h"

///=============================================================================
ffw::GLFramebuffer::GLFramebuffer(){
    created = false;
    colorcount = 0;
    fbo = 0;
}

///=============================================================================
ffw::GLFramebuffer::GLFramebuffer(GLFramebuffer&& other) NOEXCEPT {
    created = false;
    colorcount = 0;
    fbo = 0;
    swap(other);
}

///=============================================================================
void ffw::GLFramebuffer::swap(GLFramebuffer& other) NOEXCEPT {
    if (this != &other) {
        using std::swap;
        swap(created, other.created);
        swap(colorcount, other.colorcount);
        swap(fbo, other.fbo);
    }
}

///=============================================================================
ffw::GLFramebuffer& ffw::GLFramebuffer::operator = (GLFramebuffer&& other) NOEXCEPT {
    if(this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLFramebuffer::~GLFramebuffer(){
    destroy();
}

///=============================================================================
ffw::GLFramebuffer::GLFramebuffer(const std::initializer_list<Attachment>& attachments):
created(true),fbo(0), colorcount(0) {

    glGenFramebuffers(1, &fbo);
    if (fbo == 0) throw GLException("Failed to allocate framebuffer");

    for (const auto& att : attachments) {
        att(*this);
    }
}

///=============================================================================
void ffw::GLFramebuffer::addTexture(const GLenum attachment, const GLuint textype, 
    const GLuint texture, const GLint level) const {

    if (!created)throw GLException("Framebuffer is not allocated");
    if (texture == 0)throw GLException("Invalid texture handle");

    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textype, texture, level);
}

///=============================================================================
void ffw::GLFramebuffer::addRenderbuffer(const GLenum attachment, const GLuint texture) const {
    if (!created)throw GLException("Framebuffer is not allocated");
    if (texture == 0)throw GLException("Invalid renderbuffer handle");

    bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, texture);
}

///=============================================================================
bool ffw::GLFramebuffer::checkStatus(){
    if(!created)return false;
    
    bind();

    const auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        destroy();
        return false;
    }
    return true;
}

///=============================================================================
bool ffw::GLFramebuffer::destroy(){
    if(created)glDeleteFramebuffers(1, &fbo);
    colorcount = 0;
    created = false;
    return true;
}

///=============================================================================
void ffw::GLFramebuffer::bind() const {
    if(created)glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

///=============================================================================
void ffw::GLFramebuffer::unbind() const {
    if(created)glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
