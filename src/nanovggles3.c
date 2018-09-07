#include <ffw/graphics/glrenderextensions.h>
#define GL_GENERATE_MIPMAP 0x8191 // Taken from glext.h
#include "nanovg.h"
#define NANOVG_GLES3_IMPLEMENTATION
#include "nanovg_gl.h"

NVGcontext* nanovgCreateGLES3(const bool antialias, const bool strokes) {
    auto flags = 0;
    if (antialias) flags |= NVG_ANTIALIAS;
    if (strokes) flags |= NVG_STENCIL_STROKES;
    return nvgCreateGLES3(flags);
}

void nanovgDestroyGLES3(NVGcontext* vg) {
    nvgDeleteGLES3(vg);
}

int nanovgCreateImageGLES3(NVGcontext* vg, const GLuint textureId, const int w, const int h, const int flags) {
    return nvglCreateImageFromHandleGLES3(vg, textureId, w, h, flags);
}
