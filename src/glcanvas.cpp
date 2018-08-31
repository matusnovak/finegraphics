#include <utility>
#include <nanovg.h>
#include <ffw/graphics/glcanvas.h>
#include <ffw/graphics/exceptions.h>
#include "ffw/graphics/mvp.h"
#include <iostream>

extern NVGcontext* nanovgCreateGL3(bool antialias, bool strokes);
extern NVGcontext* nanovgCreateGL2(bool antialias, bool strokes);
extern NVGcontext* nanovgCreateGLES2(bool antialias, bool strokes);
extern NVGcontext* nanovgCreateGLES3(bool antialias, bool strokes);
extern void nanovgDestroyGL2(NVGcontext* vg);
extern void nanovgDestroyGL3(NVGcontext* vg);
extern void nanovgDestroyGLES2(NVGcontext* vg);
extern void nanovgDestroyGLES3(NVGcontext* vg);
extern int nanovgCreateImageGL2(NVGcontext* vg, GLuint textureId, int w, int h, int flags);
extern int nanovgCreateImageGL3(NVGcontext* vg, GLuint textureId, int w, int h, int flags);
extern int nanovgCreateImageGLES2(NVGcontext* vg, GLuint textureId, int w, int h, int flags);
extern int nanovgCreateImageGLES3(NVGcontext* vg, GLuint textureId, int w, int h, int flags);

///=============================================================================
ffw::GLCanvas::Image::Image(const GLCanvas* canvas, const int ref):canvas(canvas),ref(ref) {
    
}

///=============================================================================
ffw::GLCanvas::Image::~Image() {
    if (ref >= 0 && canvas != nullptr) {
        //canvas->removeImage(*this);
    }
}

///=============================================================================
ffw::GLCanvas::Image::Image(Image&& other) NOEXCEPT {
    swap(other);
}

///=============================================================================
ffw::GLCanvas::Image& ffw::GLCanvas::Image::operator = (Image&& other) NOEXCEPT {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
void ffw::GLCanvas::Image::swap(Image& other) NOEXCEPT {
    using std::swap;
    swap(canvas, other.canvas);
    swap(ref, other.ref);
}

///=============================================================================
ffw::GLCanvas::Font::Font(const GLCanvas* canvas, const int ref) : canvas(canvas), ref(ref) {

}

///=============================================================================
ffw::GLCanvas::Font::~Font() {
    if (ref >= 0 && canvas != nullptr) {
        canvas->removeFont(*this);
    }
}

///=============================================================================
ffw::GLCanvas::Font::Font(Font&& other) NOEXCEPT {
    swap(other);
}

///=============================================================================
ffw::GLCanvas::Font& ffw::GLCanvas::Font::operator = (Font&& other) NOEXCEPT {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
void ffw::GLCanvas::Font::swap(Font& other) NOEXCEPT {
    using std::swap;
    swap(canvas, other.canvas);
    swap(ref, other.ref);
}

///=============================================================================
class ffw::GLCanvas::Impl {
public:
    NVGcontext* nvg = nullptr;
    Settings settings;
};

///=============================================================================
ffw::GLCanvas::GLCanvas():pimpl(nullptr) {

}

///=============================================================================
ffw::GLCanvas::GLCanvas(const Settings& settings):pimpl(new Impl) {
    pimpl->settings = settings;
    switch(settings.api) {
        case API::GL2: {
            pimpl->nvg = nanovgCreateGL2(settings.antialias, settings.strokes);
            break;
        }
        case API::GL3: {
            pimpl->nvg = nanovgCreateGL3(settings.antialias, settings.strokes);
            break;
        }
        case API::GLES2: {
            pimpl->nvg = nanovgCreateGLES2(settings.antialias, settings.strokes);
            break;
        }
        case API::GLES3: {
            pimpl->nvg = nanovgCreateGLES3(settings.antialias, settings.strokes);
            break;
        }
        case API::AUTO: {
            pimpl->nvg = nanovgCreateGL3(settings.antialias, settings.strokes);
            pimpl->settings.api = API::GL3;
            if (pimpl->nvg) break;
            pimpl->nvg = nanovgCreateGL2(settings.antialias, settings.strokes);
            pimpl->settings.api = API::GL2;
            if (pimpl->nvg) break;
            pimpl->nvg = nanovgCreateGLES2(settings.antialias, settings.strokes);
            pimpl->settings.api = API::GLES2;
            if (pimpl->nvg) break;
            pimpl->nvg = nanovgCreateGLES3(settings.antialias, settings.strokes);
            pimpl->settings.api = API::GLES3;
            break;
        }
        default: {
            throw GLException("Unsupported API");
        }
    }

    if (!pimpl->nvg) throw GLException("Failed to initialize canvas");
}

///=============================================================================
ffw::GLCanvas::GLCanvas(GLCanvas&& other) NOEXCEPT : GLCanvas() {
    swap(other);
}

///=============================================================================
ffw::GLCanvas& ffw::GLCanvas::operator = (GLCanvas&& other) NOEXCEPT {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GLCanvas::~GLCanvas() {
    destroy();
}

///=============================================================================
void ffw::GLCanvas::destroy() {
    if (pimpl && pimpl->nvg) {
        switch(pimpl->settings.api) {
            case API::GL2: {
                nanovgDestroyGL2(pimpl->nvg);
                break;
            }
            case API::GL3: {
                nanovgDestroyGL3(pimpl->nvg);
                break;
            }
            case API::GLES2: {
                nanovgDestroyGLES2(pimpl->nvg);
                break;
            }
            case API::GLES3: {
                nanovgDestroyGLES3(pimpl->nvg);
                break;
            }
            default: {
                break;
            }
        }
    }
}

///=============================================================================
void ffw::GLCanvas::swap(GLCanvas& other) NOEXCEPT {
    using std::swap;
    swap(pimpl, other.pimpl);
}

///=============================================================================
void ffw::GLCanvas::beginFrame(const Vec2f& size) const {
    nvgBeginFrame(pimpl->nvg, size.x, size.y, pimpl->settings.devicePixelRatio);
}

///=============================================================================
void ffw::GLCanvas::endFrame() const {
    nvgEndFrame(pimpl->nvg);
}

///=============================================================================
void ffw::GLCanvas::cancelFrame() const {
    nvgCancelFrame(pimpl->nvg);
}

///=============================================================================
static NVGblendFactor toBlendFactor(const ffw::GLCanvas::BlendFactor factor) {
    switch (factor) {
    case ffw::GLCanvas::BlendFactor::ZERO: 
        return NVGblendFactor::NVG_ZERO;
    case ffw::GLCanvas::BlendFactor::ONE: 
        return NVGblendFactor::NVG_ONE;
    case ffw::GLCanvas::BlendFactor::SRC_COLOR: 
        return NVGblendFactor::NVG_SRC_COLOR;
    case ffw::GLCanvas::BlendFactor::ONE_MINUS_SRC_COLOR: 
        return NVGblendFactor::NVG_ONE_MINUS_SRC_COLOR;
    case ffw::GLCanvas::BlendFactor::DST_COLOR: 
        return NVGblendFactor::NVG_DST_COLOR;
    case ffw::GLCanvas::BlendFactor::ONE_MINUS_DST_COLOR: 
        return NVGblendFactor::NVG_ONE_MINUS_DST_COLOR;
    case ffw::GLCanvas::BlendFactor::SRC_ALPHA: 
        return NVGblendFactor::NVG_SRC_ALPHA;
    case ffw::GLCanvas::BlendFactor::ONE_MINUS_SRC_ALPHA:
        return NVGblendFactor::NVG_ONE_MINUS_SRC_ALPHA;
    case ffw::GLCanvas::BlendFactor::DST_ALPHA: 
        return NVGblendFactor::NVG_DST_ALPHA;
    case ffw::GLCanvas::BlendFactor::ONE_MINUS_DST_ALPHA: 
        return NVGblendFactor::NVG_ONE_MINUS_DST_ALPHA;
    case ffw::GLCanvas::BlendFactor::SRC_ALPHA_SATURATE: 
        return NVGblendFactor::NVG_SRC_ALPHA_SATURATE;
    default: return NVGblendFactor::NVG_ZERO;
    }
}

///=============================================================================
static NVGcompositeOperation toCompositeOperation(const ffw::GLCanvas::CompositeOperation op) {
    switch(op) {
        case ffw::GLCanvas::CompositeOperation::SOURCE_OVER: 
            return NVGcompositeOperation::NVG_SOURCE_OVER;
        case ffw::GLCanvas::CompositeOperation::SOURCE_IN: 
            return NVGcompositeOperation::NVG_SOURCE_IN;
        case ffw::GLCanvas::CompositeOperation::SOURCE_OUT: 
            return NVGcompositeOperation::NVG_SOURCE_OUT;
        case ffw::GLCanvas::CompositeOperation::ATOP: 
            return NVGcompositeOperation::NVG_ATOP;
        case ffw::GLCanvas::CompositeOperation::DESTINATION_OVER: 
            return NVGcompositeOperation::NVG_DESTINATION_OVER;
        case ffw::GLCanvas::CompositeOperation::DESTINATION_IN: 
            return NVGcompositeOperation::NVG_DESTINATION_IN;
        case ffw::GLCanvas::CompositeOperation::DESTINATION_OUT: 
            return NVGcompositeOperation::NVG_DESTINATION_OUT;
        case ffw::GLCanvas::CompositeOperation::DESTINATION_ATOP: 
            return NVGcompositeOperation::NVG_DESTINATION_ATOP;
        case ffw::GLCanvas::CompositeOperation::LIGHTER: 
            return NVGcompositeOperation::NVG_LIGHTER;
        case ffw::GLCanvas::CompositeOperation::COPY:
            return NVGcompositeOperation::NVG_COPY;
        case ffw::GLCanvas::CompositeOperation::XOR: 
            return NVGcompositeOperation::NVG_XOR;
        default: return NVGcompositeOperation::NVG_COPY;
    }
}

///=============================================================================
void ffw::GLCanvas::globalCompositeOperation(const CompositeOperation op) const {
    nvgGlobalCompositeOperation(pimpl->nvg, toCompositeOperation(op));
}

///=============================================================================
void ffw::GLCanvas::globalCompositeBlendFunc(
    const BlendFactor sfactor, const BlendFactor dfactor) const  {
    nvgGlobalCompositeBlendFunc(pimpl->nvg, toBlendFactor(sfactor), toBlendFactor(dfactor));
}

///=============================================================================
void ffw::GLCanvas::globalCompositeBlendFuncSeparate(
    const BlendFactor srcRGB, const BlendFactor dstRGB, 
    const BlendFactor srcAlpha, const BlendFactor dstAlpha) const  {

    nvgGlobalCompositeBlendFuncSeparate(pimpl->nvg, toBlendFactor(srcRGB), toBlendFactor(dstRGB), 
        toBlendFactor(srcAlpha), toBlendFactor(dstAlpha));
}

///=============================================================================
void ffw::GLCanvas::save() const {
    nvgSave(pimpl->nvg);
}

///=============================================================================
void ffw::GLCanvas::restore() const {
    nvgRestore(pimpl->nvg);
}

///=============================================================================
void ffw::GLCanvas::reset() const {
    nvgReset(pimpl->nvg);
}

///=============================================================================
void ffw::GLCanvas::shapeAntiAlias(const bool enabled) const {
    nvgShapeAntiAlias(pimpl->nvg, enabled ? 1 : 0);
}

///=============================================================================
void ffw::GLCanvas::strokeColor(const Color& color) const {
    nvgStrokeColor(pimpl->nvg, *reinterpret_cast<const NVGcolor*>(&color));
}

///=============================================================================
void ffw::GLCanvas::strokePaint(const Paint& paint) const {
    nvgStrokePaint(pimpl->nvg, *reinterpret_cast<const NVGpaint*>(&paint));
}

///=============================================================================
void ffw::GLCanvas::fillColor(const Color& color) const {
    nvgFillColor(pimpl->nvg, *reinterpret_cast<const NVGcolor*>(&color));
}

///=============================================================================
void ffw::GLCanvas::fillPaint(const Paint& paint) const {
    nvgFillPaint(pimpl->nvg, *reinterpret_cast<const NVGpaint*>(&paint));
}

///=============================================================================
void ffw::GLCanvas::miterLimit(const float limit) const {
    nvgMiterLimit(pimpl->nvg, limit);
}

///=============================================================================
void ffw::GLCanvas::strokeWidth(const float size) const {
    nvgStrokeWidth(pimpl->nvg, size);
}

///=============================================================================
static NVGlineCap toLineCap(const ffw::GLCanvas::LineCap cap) {
    switch (cap) {
        case ffw::GLCanvas::LineCap::ROUND: return NVGlineCap::NVG_ROUND;
        case ffw::GLCanvas::LineCap::BUTT: return NVGlineCap::NVG_BUTT;
        case ffw::GLCanvas::LineCap::SQUARE: return NVGlineCap::NVG_SQUARE;
        default: return NVGlineCap::NVG_BUTT;
    }
}

///=============================================================================
void ffw::GLCanvas::lineCap(const LineCap cap) const {
    nvgLineCap(pimpl->nvg, toLineCap(cap));
}

///=============================================================================
static NVGlineCap toLineCap(const ffw::GLCanvas::LineJoin join) {
    switch(join) {
        case ffw::GLCanvas::LineJoin::ROUND: return NVGlineCap::NVG_ROUND;
        case ffw::GLCanvas::LineJoin::BEVEL: return NVGlineCap::NVG_BEVEL;
        case ffw::GLCanvas::LineJoin::MITER: return NVGlineCap::NVG_MITER;
        default: return NVGlineCap::NVG_MITER;
    }
}

///=============================================================================
void ffw::GLCanvas::lineJoin(const LineJoin join) const {
    nvgLineJoin(pimpl->nvg, toLineCap(join));
}

///=============================================================================
void ffw::GLCanvas::globalAlpha(const float alpha) const {
    nvgGlobalAlpha(pimpl->nvg, alpha);
}

///=============================================================================
void ffw::GLCanvas::resetTransform() const {
    nvgResetTransform(pimpl->nvg);
}

///=============================================================================
void ffw::GLCanvas::transform(const Mat3x3f& mat) const {
    nvgTransform(pimpl->nvg, mat[0], mat[1], mat[3], mat[4], mat[6], mat[7]);
}

///=============================================================================
void ffw::GLCanvas::translate(const Vec2f& pos) const {
    nvgTranslate(pimpl->nvg, pos.x, pos.y);
}

///=============================================================================
void ffw::GLCanvas::rotate(const float angle) const {
    nvgRotate(pimpl->nvg, float(angle * DEG_TO_RAD));
}

///=============================================================================
void ffw::GLCanvas::rotateRad(const float angle) const {
    nvgRotate(pimpl->nvg, angle);
}

///=============================================================================
void ffw::GLCanvas::skewX(const float angle) const {
    nvgSkewX(pimpl->nvg, float(angle * DEG_TO_RAD));
}

///=============================================================================
void ffw::GLCanvas::skewXRad(const float angle) const {
    nvgSkewX(pimpl->nvg, angle);
}

///=============================================================================
void ffw::GLCanvas::skewY(const float angle) const {
    nvgSkewY(pimpl->nvg, float(angle * DEG_TO_RAD));
}

///=============================================================================
void ffw::GLCanvas::skewYRad(const float angle) const {
    nvgSkewY(pimpl->nvg, angle);
}

///=============================================================================
void ffw::GLCanvas::scale(float x, float y) const {
    nvgScale(pimpl->nvg, x, y);
}

///=============================================================================
ffw::Mat3x3f ffw::GLCanvas::getCurrentTransform() const {
    float xform[6] = { 0 };
    nvgCurrentTransform(pimpl->nvg, xform);

    Mat3x3f mat;
    mat[0] = xform[0];
    mat[1] = xform[1];
    mat[3] = xform[2];
    mat[4] = xform[3];
    mat[6] = xform[4];
    mat[7] = xform[5];

    return mat;
}

///=============================================================================
void ffw::GLCanvas::setTransform(const Mat3x3f& mat) const {
    nvgResetTransform(pimpl->nvg);
    nvgTransform(pimpl->nvg, mat[0], mat[1], mat[3], mat[4], mat[6], mat[7]);
}

///=============================================================================
ffw::GLCanvas::Image ffw::GLCanvas::createImage(const GLTexture2D& texture, ImageFlags::Flag imageFlags) const {
    int ref;
	switch(pimpl->settings.api) {
        case API::GL2: {
            ref = nanovgCreateImageGL2(pimpl->nvg, texture.getHandle(), texture.getWidth(), texture.getHeight(), imageFlags);
            break;
        }
        case API::GL3: {
            ref = nanovgCreateImageGL3(pimpl->nvg, texture.getHandle(), texture.getWidth(), texture.getHeight(), imageFlags);
            break;
        }
        case API::GLES2: {
            ref = nanovgCreateImageGLES2(pimpl->nvg, texture.getHandle(), texture.getWidth(), texture.getHeight(), imageFlags);
            break;
        }
        case API::GLES3: {
            ref = nanovgCreateImageGLES3(pimpl->nvg, texture.getHandle(), texture.getWidth(), texture.getHeight(), imageFlags);
            break;
        }
        default: {
            throw GLException("Unsupported API");
        }
    }
    auto ret = Image(this, ref);
    return ret;
}

///=============================================================================
void ffw::GLCanvas::removeImage(Image& image) const {
    nvgDeleteImage(pimpl->nvg, image.ref);
}

///=============================================================================
ffw::GLCanvas::Paint ffw::GLCanvas::linearGradient(const ffw::Vec2f& start, const ffw::Vec2f& end,
    const Color& icol, const Color& ocol) const {

    const auto paint = nvgLinearGradient(pimpl->nvg, 
        start.x, start.y, end.x, end.y,
        *reinterpret_cast<const NVGcolor*>(&icol), 
        *reinterpret_cast<const NVGcolor*>(&ocol));
    Paint ret;
    ret.extent[0] = paint.extent[0];
    ret.extent[1] = paint.extent[1];
    for(auto i = 0; i < 6; i++)ret.xform[i] = paint.xform[i];
    ret.feather = paint.feather;
    ret.innerColor = icol;
    ret.outerColor = ocol;
    return ret;
}

///=============================================================================
ffw::GLCanvas::Paint ffw::GLCanvas::boxGradient(const ffw::Vec2f& pos, const ffw::Vec2f& size,
    const float r, const float f, const Color& icol, const Color& ocol) const {

    const auto paint = nvgBoxGradient(pimpl->nvg,
        pos.x, pos.y, size.x, size.y, r, f,
        *reinterpret_cast<const NVGcolor*>(&icol),
        *reinterpret_cast<const NVGcolor*>(&ocol));
    Paint ret;
    ret.extent[0] = paint.extent[0];
    ret.extent[1] = paint.extent[1];
    for (auto i = 0; i < 6; i++)ret.xform[i] = paint.xform[i];
    ret.feather = paint.feather;
    ret.innerColor = icol;
    ret.outerColor = ocol;
    return ret;
}

///=============================================================================
ffw::GLCanvas::Paint ffw::GLCanvas::radialGradient(const Vec2f& center, const float inr, 
    const float outr, const Color& icol, const Color& ocol) const {

    const auto paint = nvgRadialGradient(pimpl->nvg,
        center.x, center.y, inr, outr,
        *reinterpret_cast<const NVGcolor*>(&icol),
        *reinterpret_cast<const NVGcolor*>(&ocol));
    Paint ret;
    ret.extent[0] = paint.extent[0];
    ret.extent[1] = paint.extent[1];
    for (auto i = 0; i < 6; i++)ret.xform[i] = paint.xform[i];
    ret.feather = paint.feather;
    ret.innerColor = icol;
    ret.outerColor = ocol;
    return ret;
}

///=============================================================================
ffw::GLCanvas::Paint ffw::GLCanvas::imagePattern(const Vec2f& start, const Vec2f& end,
    const float angle, const Image& image, const float alpha) const {
    
    const auto paint = nvgImagePattern(pimpl->nvg,
        start.x, start.y, end.x, end.y, float(angle * DEG_TO_RAD), image.ref, alpha);
    Paint ret;
    for (auto i = 0; i < 2; i++)ret.extent[i] = paint.extent[i];
    for (auto i = 0; i < 6; i++)ret.xform[i] = paint.xform[i];
    ret.feather = paint.feather;
    ret.image = paint.image;
    ret.innerColor = *reinterpret_cast<const ffw::Color*>(&paint.innerColor);
    ret.outerColor = *reinterpret_cast<const ffw::Color*>(&paint.outerColor);
    return ret;
}

///=============================================================================
void ffw::GLCanvas::scissor(const Vec2f& pos, const Vec2f& size) const {
    nvgScissor(pimpl->nvg, pos.x, pos.y, size.x, size.y);
}

///=============================================================================
void ffw::GLCanvas::intersectScissor(const Vec2f& pos, const Vec2f& size) const {
    nvgIntersectScissor(pimpl->nvg, pos.x, pos.y, size.x, size.y);
}

///=============================================================================
void ffw::GLCanvas::resetScissor() const {
    nvgResetScissor(pimpl->nvg);
}

///=============================================================================
void ffw::GLCanvas::beginPath() const {
    nvgBeginPath(pimpl->nvg);
}

///=============================================================================
void ffw::GLCanvas::moveTo(const Vec2f& pos) const {
    nvgMoveTo(pimpl->nvg, pos.x, pos.y);
}

///=============================================================================
void ffw::GLCanvas::lineTo(const Vec2f& pos) const {
    nvgLineTo(pimpl->nvg, pos.x, pos.y);
}

///=============================================================================
void ffw::GLCanvas::bezierTo(const Vec2f& c1, const Vec2f& c2, const Vec2f& pos) const {
    nvgBezierTo(pimpl->nvg, c1.x, c1.y, c2.x, c2.y, pos.x, pos.y);
}

///=============================================================================
void ffw::GLCanvas::quadTo(const Vec2f& c, const Vec2f& pos) const {
    nvgQuadTo(pimpl->nvg, c.x, c.y, pos.x, pos.y);
}

///=============================================================================
void ffw::GLCanvas::arcTo(const Vec2f& x1, const Vec2f& x2, const float angle) const {
    nvgArcTo(pimpl->nvg, x1.x, x1.y, x2.x, x2.y, float(angle * DEG_TO_RAD));
}

///=============================================================================
void ffw::GLCanvas::arcToRad(const Vec2f& x1, const Vec2f& x2, const float angle) const {
    nvgArcTo(pimpl->nvg, x1.x, x1.y, x2.x, x2.y, angle);
}

///=============================================================================
void ffw::GLCanvas::closePath() const {
    nvgClosePath(pimpl->nvg);
}

///=============================================================================
static NVGwinding toWinding(const ffw::GLCanvas::Winding dir) {
    switch(dir) {
        case ffw::GLCanvas::Winding::CCW: return NVGwinding::NVG_CCW;
        case ffw::GLCanvas::Winding::CW: return NVGwinding::NVG_CW;
        default: return NVGwinding::NVG_CCW;
    }
}

///=============================================================================
void ffw::GLCanvas::pathWinding(const Winding dir) const {
    nvgPathWinding(pimpl->nvg, toWinding(dir));
}

///=============================================================================
static NVGsolidity toSolidity(const ffw::GLCanvas::Solidity dir) {
    switch (dir) {
    case ffw::GLCanvas::Solidity::HOLE: return NVGsolidity::NVG_HOLE;
    case ffw::GLCanvas::Solidity::SOLID: return NVGsolidity::NVG_SOLID;
    default: return NVGsolidity::NVG_SOLID;
    }
}

///=============================================================================
void ffw::GLCanvas::pathWinding(const Solidity dir) const {
    nvgPathWinding(pimpl->nvg, toSolidity(dir));
}

///=============================================================================
void ffw::GLCanvas::arc(const Vec2f& center, const float r, 
    const float a0, const float a1, const Winding dir) const {
    nvgArc(pimpl->nvg, center.x, center.y, r, float(a0 * DEG_TO_RAD), float(a1 * DEG_TO_RAD), toWinding(dir));
}

///=============================================================================
void ffw::GLCanvas::arcRad(const Vec2f& center, const float r, 
    const float a0, const float a1, const Winding dir) const {
    nvgArc(pimpl->nvg, center.x, center.y, r, a0, a1, toWinding(dir));
}

///=============================================================================
void ffw::GLCanvas::rect(const Vec2f& pos, const Vec2f& size) const {
    nvgRect(pimpl->nvg, pos.x, pos.y, size.x, size.y);
}

///=============================================================================
void ffw::GLCanvas::roundedRect(const Vec2f& pos, const Vec2f& size, const float r) const {
    nvgRoundedRect(pimpl->nvg, pos.x, pos.y, size.x, size.y, r);
}

///=============================================================================
void ffw::GLCanvas::roundedRect(const Vec2f& pos, const Vec2f& size, const float radTopLeft,
    const float radTopRight, const float radBottomRight, const float radBottomLeft) const {
    nvgRoundedRectVarying(pimpl->nvg, pos.x, pos.y, size.x, size.y,
        radTopLeft, radTopRight, radBottomRight, radBottomLeft);
}

///=============================================================================
void ffw::GLCanvas::ellipse(const Vec2f& pos, const float rx, const float ry) const {
    nvgEllipse(pimpl->nvg, pos.x, pos.y, rx, ry);
}

///=============================================================================
void ffw::GLCanvas::circle(const Vec2f& pos, const float r) const {
    nvgCircle(pimpl->nvg, pos.x, pos.y, r);
}

///=============================================================================
void ffw::GLCanvas::fill() const {
    nvgFill(pimpl->nvg);
}

///=============================================================================
void ffw::GLCanvas::stroke() const {
    nvgStroke(pimpl->nvg);
}

///=============================================================================
ffw::GLCanvas::Font ffw::GLCanvas::createFont(const std::string& filename) const {
    const auto ref = nvgCreateFont(pimpl->nvg, "", filename.c_str());
    auto ret = Font(this, ref);
    return ret;
}

///=============================================================================
ffw::GLCanvas::Font ffw::GLCanvas::createFontMem(unsigned char* data, const size_t length) const {
    const auto ref = nvgCreateFontMem(pimpl->nvg, "", data, length, 0);
    auto ret = Font(this, ref);
    return ret;
}

///=============================================================================
void ffw::GLCanvas::addFallbackFontId(Font& baseFont, Font& fallbackFont) const {
    nvgAddFallbackFontId(pimpl->nvg, baseFont.ref, fallbackFont.ref);
}

///=============================================================================
void ffw::GLCanvas::removeFont(Font& font) const {
    (void)font;
    // ???
}

///=============================================================================
void ffw::GLCanvas::fontSize(const float size) const {
    nvgFontSize(pimpl->nvg, size);
}

///=============================================================================
void ffw::GLCanvas::fontBlur(const float blur) const {
    nvgFontBlur(pimpl->nvg, blur);
}

///=============================================================================
void ffw::GLCanvas::textLetterSpacing(const float spacing) const {
    nvgTextLetterSpacing(pimpl->nvg, spacing);
}

///=============================================================================
void ffw::GLCanvas::textLineHeight(const float lineHeight) const {
    nvgTextLineHeight(pimpl->nvg, lineHeight);
}

///=============================================================================
void ffw::GLCanvas::textAlign(const TextAlign::Flag align) const {
    nvgTextAlign(pimpl->nvg, align);
}

///=============================================================================
void ffw::GLCanvas::fontFace(const Font& font) const {
    nvgFontFaceId(pimpl->nvg, font.ref);
}

///=============================================================================
void ffw::GLCanvas::text(const Vec2f& pos, const char* string, const char* end) const {
    nvgTextBox(pimpl->nvg, pos.x, pos.y, std::numeric_limits<float>::max(), string, end);
}

///=============================================================================
void ffw::GLCanvas::textBox(const Vec2f& pos, const float breakRowWidth, const char* string, const char* end) const {
    nvgTextBox(pimpl->nvg, pos.x, pos.y, breakRowWidth, string, end);
}

///=============================================================================
float ffw::GLCanvas::textBounds(const Vec2f& pos, const char* string, const char* end, Vec4f& bounds) const {
    return nvgTextBounds(pimpl->nvg, pos.x, pos.y, string, end, &bounds[0]);
}

///=============================================================================
ffw::Vec2f ffw::GLCanvas::textBoxBounds(const Vec2f& pos, const float breakRowWidth, const char* string, const char* end) const {
    Vec2f ret;
    nvgTextBoxBounds(pimpl->nvg, pos.x, pos.y, breakRowWidth, string, end, &ret[0]);
    return ret;
}

///=============================================================================
void ffw::GLCanvas::textMetrics(float& ascender, float& descender, float& lineh) const {
    nvgTextMetrics(pimpl->nvg, &ascender, &descender, &lineh);
}

///=============================================================================
void ffw::GLCanvas::text(const Vec2f& pos, const std::string& str) const {
    text(pos, str.c_str(), str.c_str() + str.size());
}

///=============================================================================
void ffw::GLCanvas::textBox(const Vec2f& pos, float breakRowWidth, const std::string& str) const {
    textBox(pos, breakRowWidth, str.c_str(), str.c_str() + str.size());
}

///=============================================================================
float ffw::GLCanvas::textBounds(const Vec2f& pos, const std::string& str, Vec4f& bounds) const {
    return textBounds(pos, str.c_str(), str.c_str() + str.size(), bounds);
}

///=============================================================================
ffw::Vec2f ffw::GLCanvas::textBoxBounds(const Vec2f& pos, float breakRowWidth, const std::string& str) const {
    return textBoxBounds(pos, breakRowWidth, str.c_str(), str.c_str() + str.size());
}
