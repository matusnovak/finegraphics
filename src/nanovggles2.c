#include <ffw/graphics/glrenderextensions.h>
#define GL_GENERATE_MIPMAP 0x8191 // Taken from glext.h
#include "nanovg.h"
#define NANOVG_GLES2_IMPLEMENTATION
#include "nanovg_gl.h"

NVGcontext* nanovgCreateGLES2(const bool antialias, const bool strokes) {
    auto flags = 0;
    if (antialias) flags |= NVG_ANTIALIAS;
    if (strokes) flags |= NVG_STENCIL_STROKES;
    return nvgCreateGLES2(flags);
}

void nanovgDestroyGLES2(NVGcontext* vg) {
    nvgDeleteGLES2(vg);
}

int nanovgCreateImageGLES2(NVGcontext* vg, const GLuint textureId, const int w, const int h, const int flags) {
    return nvglCreateImageFromHandleGLES2(vg, textureId, w, h, flags);
}
