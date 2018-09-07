#include <ffw/graphics/glrenderextensions.h>
#define GL_GENERATE_MIPMAP 0x8191 // Taken from glext.h
#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

NVGcontext* nanovgCreateGL2(const bool antialias, const bool strokes) {
    auto flags = 0;
    if (antialias) flags |= NVG_ANTIALIAS;
    if (strokes) flags |= NVG_STENCIL_STROKES;
    return nvgCreateGL2(flags);
}

void nanovgDestroyGL2(NVGcontext* vg) {
    nvgDeleteGL2(vg);
}

int nanovgCreateImageGL2(NVGcontext* vg, const GLuint textureId, const int w, const int h, const int flags) {
    return nvglCreateImageFromHandleGL2(vg, textureId, w, h, flags);
}
