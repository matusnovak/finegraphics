#include <ffw/graphics/glrenderextensions.h>
#define GL_GENERATE_MIPMAP 0x8191 // Taken from glext.h
#include "nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

NVGcontext* nanovgCreateGL3(const bool antialias, const bool strokes) {
    auto flags = 0;
    if (antialias) flags |= NVG_ANTIALIAS;
    if (strokes) flags |= NVG_STENCIL_STROKES;
    return nvgCreateGL3(flags);
}

void nanovgDestroyGL3(NVGcontext* vg) {
    nvgDeleteGL3(vg);
}

int nanovgCreateImageGL3(NVGcontext* vg, const GLuint textureId, const int w, const int h, const int flags) {
    return nvglCreateImageFromHandleGL3(vg, textureId, w, h, flags);
}
