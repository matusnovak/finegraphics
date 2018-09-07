/* This file is part of FineFramework project */
#ifndef FFW_GRAPHICS_CANVAS
#define FFW_GRAPHICS_CANVAS

#include <string>
#include <memory>
#include "config.h"
#include "color.h"
#include "mat4.h"
#include "mat3.h"
#include "vec2.h"
#include "gltexture2d.h"

namespace ffw {
    /**
     * @ingroup graphics
     * @breif Canvas used for drawing simple 2D shapes using nanovg library.
     */
    class FFW_API GLCanvas {
    public:
        enum class API {
            AUTO = 0,
            GL2,
            GL3,
            GLES2,
            GLES3
        };

        struct Settings {
            API api = API::AUTO;
            bool antialias = true;
            bool strokes = true;
            // Device pixel ration allows to control the rendering on Hi - DPI devices.
            float devicePixelRatio = 1.0f;
        };

        enum class Mode {
            FILL,
            STROKE,
            FILL_AND_STROKE,
        };

        enum class Winding {
            // Winding for solid shapes
            CCW,
            // Winding for holes
            CW,
        };

        enum class Solidity {
            SOLID,
            HOLE,
        };

        enum class LineCap {
            BUTT,
            ROUND,
            SQUARE
        };

        enum class LineJoin {
            ROUND,
            BEVEL,
            MITER
        };

        struct TextAlign {
            typedef uint32_t Flag;
            // Default, align text horizontally to left.
            static const Flag LEFT = 1 << 0;
            // Align text horizontally to center.
            static const Flag CENTER = 1 << 1;
            // Align text horizontally to right.
            static const Flag RIGHT = 1 << 2;
            // Align text vertically to top.
            static const Flag TOP = 1 << 3;
            // Align text vertically to middle.
            static const Flag MIDDLE = 1 << 4;
            // Align text vertically to bottom.
            static const Flag BOTTOM = 1 << 5;
            // Default, align text vertically to baseline.
            static const Flag BASELINE = 1 << 6;
        };

        enum class BlendFactor {
            ZERO,
            ONE,
            SRC_COLOR,
            ONE_MINUS_SRC_COLOR,
            DST_COLOR,
            ONE_MINUS_DST_COLOR,
            SRC_ALPHA,
            ONE_MINUS_SRC_ALPHA,
            DST_ALPHA,
            ONE_MINUS_DST_ALPHA,
            SRC_ALPHA_SATURATE,
        };

        enum class CompositeOperation {
            SOURCE_OVER,
            SOURCE_IN,
            SOURCE_OUT,
            ATOP,
            DESTINATION_OVER,
            DESTINATION_IN,
            DESTINATION_OUT,
            DESTINATION_ATOP,
            LIGHTER,
            COPY,
            XOR,
        };

        class FFW_API Image {
        public:
            Image() = default;
            Image(const GLCanvas* canvas, int ref);
            Image(const Image& other) = delete;
            Image(Image&& other) NOEXCEPT;
            Image& operator = (const Image& other) = delete;
            Image& operator = (Image&& other) NOEXCEPT;
            void swap(Image& other) NOEXCEPT;
            virtual ~Image();

            const GLCanvas* canvas = nullptr;
            int ref = -1;
        };

        class FFW_API Font {
        public:
            Font() = default;
            Font(const GLCanvas* canvas, int ref);
            Font(const Font& other) = delete;
            Font(Font&& other) NOEXCEPT;
            Font& operator = (const Font& other) = delete;
            Font& operator = (Font&& other) NOEXCEPT;
            void swap(Font& other) NOEXCEPT;
            virtual ~Font();

            const GLCanvas* canvas = nullptr;
            int ref = -1;
        };

        struct FFW_API Paint {
#if defined(_MSC_VER) && _MSC_VER == 1800
            Paint() {
                xform[0] = xform[1] = xform[2] = xform[3] = xform[4] = xform[5] = 0;
                extent[0] = extent[1] = 0;
            }
            float xform[6];
            float extent[2];
#else
            float xform[6] = { 0 };
            float extent[2] = { 0 };
#endif
            float radius = 0;
            float feather = 0;
            Color innerColor;
            Color outerColor;
            int image = 0;
        };

        struct GlyphPosition {
            const char* str;	// Position of the glyph in the input string.
            float x;			// The x-coordinate of the logical glyph position.
            float minx, maxx;	// The bounds of the glyph shape.
        };

        struct TextRow {
            const char* start;	// Pointer to the input text where the row starts.
            const char* end;	// Pointer to the input text where the row ends (one past the last character).
            const char* next;	// Pointer to the beginning of the next row.
            float width;		// Logical width of the row.
            float minx, maxx;	// Actual bounds of the row. Logical with and bounds can differ because of kerning and some parts over extending.
        };

        struct ImageFlags {
            typedef uint32_t Flag;
            /**
             * @brief Generate mipmaps during creation of the image
             */
            const static Flag IMAGE_GENERATE_MIPMAPS = 1 << 0;
            /**
             * @brief Repeat image in X direction
             */
            const static Flag IMAGE_REPEATX = 1 << 1;
            /**
             * @brief Repeat image in Y direction
             */
            const static Flag IMAGE_REPEATY = 1 << 2;
            /**
             * @brief Flips (inverses) image in Y direction when rendered
             */
            const static Flag IMAGE_FLIPY = 1 << 3;
            /**
             * @brief Image data has premultiplied alpha
             */
            const static Flag IMAGE_PREMULTIPLIED = 1 << 4;
            /**
             * @brief Image interpolation is Nearest instead Linear
             */
            const static Flag IMAGE_NEAREST = 1 << 5;
        };

        GLCanvas();
        GLCanvas(const Settings& settings);
        GLCanvas(const GLCanvas& other) = delete;
        GLCanvas(GLCanvas&& other) NOEXCEPT;
        GLCanvas& operator = (const GLCanvas& other) = delete;
        GLCanvas& operator = (GLCanvas&& other) NOEXCEPT;
        void swap(GLCanvas& other) NOEXCEPT;
        virtual ~GLCanvas();
        void destroy();

        /**
         * @brief Begin drawing a new frame
         * @details Calls to nanovg drawing API should be wrapped in beginFrame() & endFrame()
         * beginFrame() defines the size of the window to render to in relation currently
         * set viewport (i.e. glViewport on GL backends).
         */
        void beginFrame(const Vec2f& size) const;
        /**
         * @brief Ends drawing flushing remaining render state
         */
        void endFrame() const;
        /**
         * @brief Cancels drawing the current frame
         */
        void cancelFrame() const;
        /**
         * @brief Sets the composite operation.
         */
        void globalCompositeOperation(CompositeOperation op) const;
        /**
         * @brief Sets the composite operation with custom pixel arithmetic.
         */
        void globalCompositeBlendFunc(BlendFactor sfactor, BlendFactor dfactor) const;
        /**
         * @brief Sets the composite operation with custom pixel arithmetic for RGB and alpha components separately.
         */
        void globalCompositeBlendFuncSeparate(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha) const;
        /**
         * @brief Pushes and saves the current render state into a state stack
         * @note A matching nvgRestore() must be used to restore the state.
         */
        void save() const;
        /**
         * @brief Pops and restores current render state
         */
        void restore() const;
        /**
         * @brief Resets current render state to default values
         * @note Does not affect the render state stack.
         */
        void reset() const;
        /**
         * @brief Sets whether to draw antialias for stroke() and fill().
         * @details It's enabled by default.
         */
        void shapeAntiAlias(bool enabled) const;
        /**
         * @brief Sets current stroke style to a solid color
         */
        void strokeColor(const Color& color) const;
        /**
         * @brief Sets current stroke style to a paint, which can be a one of the gradients or a pattern
         */
        void strokePaint(const Paint& paint) const;
        /**
         * @brief Sets current fill style to a solid color
         */
        void fillColor(const Color& color) const;
        /**
         * @brief Sets current fill style to a paint, which can be a one of the gradients or a pattern
         */
        void fillPaint(const Paint& paint) const;
        /**
         * @brief Sets the miter limit of the stroke style
         * @details Miter limit controls when a sharp corner is beveled
         */
        void miterLimit(float limit) const;
        /**
         * @brief Sets the stroke width of the stroke style
         */
        void strokeWidth(float size) const;
        /**
         * @brief Sets how the end of the line (cap) is drawn
         */
        void lineCap(LineCap cap) const;
        /**
         * @brief Sets how sharp path corners are drawn
         */
        void lineJoin(LineJoin join) const;
        /**
         * @brief Sets the transparency applied to all rendered shapes
         * @details Already transparent paths will get proportionally more transparent as well
         */
        void globalAlpha(float alpha) const;
        /**
         * @brief Resets current transform to a identity matrix
         */
        void resetTransform() const;
        /**
        * @brief Premultiplies current coordinate system by specified matrix
        */
        void transform(const Mat3x3f& mat) const;
        /**
         * @brief Translates current coordinate system
         */
        void translate(const Vec2f& pos) const;
        /**
         * @brief Rotates current coordinate system in degrees
         */
        void rotate(float angle) const;
        /**
        * @brief Rotates current coordinate system in radians
        */
        void rotateRad(float angle) const;
        /**
         * @brief Skews the current coordinate system along X axis in degrees
         */
        void skewX(float angle) const;
        /**
        * @brief Skews the current coordinate system along X axis in radians
        */
        void skewXRad(float angle) const;
        /**
         * @brief Skews the current coordinate system along Y axis in degrees
         */
        void skewY(float angle) const;
        /**
        * @brief Skews the current coordinate system along Y axis in radians
        */
        void skewYRad(float angle) const;
        /**
         * @brief Scales the current coordinate system
         */
        void scale(float x, float y) const;
        /**
         * @brief Returns the current transformation matrix
         */
        Mat3x3f getCurrentTransform() const;
        /**
        * @brief Sets the current transformation matrix
        */
        void setTransform(const Mat3x3f& mat) const;
        /**
         * @brief Creates image from raw RGBA pixels
         */
        Image createImage(const GLTexture2D& texture, ImageFlags::Flag imageFlags = 0) const;
        /**
         * @brief Creates and returns a linear gradient
         * @details Parameters (start)-(end) specify the start and end coordinates
         * of the linear gradient, icol specifies the start color and ocol the end color.
         * The gradient is transformed by the current transform when it is passed to fillPaint()
         *  or strokePaint().
         */
        Paint linearGradient(const ffw::Vec2f& start, const ffw::Vec2f& end,
            const Color& icol, const Color& ocol) const;
        /**
         * @brief Creates and returns a box gradient
         * @details Box gradient is a feathered rounded rectangle, it is useful for rendering
         * drop shadows or highlights for boxes. Parameters (pos) define the top-left corner of 
         * the rectangle, (size) define the size of the rectangle, r defines the corner radius, 
         * and f feather. Feather defines how blurry the border of the rectangle is. Parameter icol 
         * specifies the inner color and ocol the outer color of the gradient. The gradient is 
         * transformed by the current transform when it is passed to fillPaint() or strokePaint().
         */
        Paint boxGradient(const ffw::Vec2f& pos, const ffw::Vec2f& size,
            float r, float f, const Color& icol, const Color& ocol) const;
        /**
         * @brief Creates and returns a radial gradient
         * @details Parameters (center) specify the center, inr and outr specify the inner and outer 
         * radius of the gradient, icol specifies the start color and ocol the end color. The 
         * gradient is transformed by the current transform when it is passed to fillPaint() or 
         * strokePaint().
         */
        Paint radialGradient(const ffw::Vec2f& center, float inr, float outr,
            const Color& icol, const Color& ocol) const;
        /**
         * @brief Creates and returns an image patter
         * @details Parameters (start) specify the left-top location of the image pattern, (end) 
         * the size of one image, angle (degrees) rotation around the top-left corner, image is 
         * handle to the image to render. The gradient is transformed by the current transform when 
         * it is passed to fillPaint() or strokePaint().
         */
        Paint imagePattern(const Vec2f& start, const Vec2f& end,
            float angle, const Image& image, float alpha) const;
        /**
         * @brief Sets the current scissor rectangle
         * @details The scissor rectangle is transformed by the current transform.
         */
        void scissor(const Vec2f& pos, const Vec2f& size) const;
        /**
         * @brief Intersects current scissor rectangle with the specified rectangle
         * @details The scissor rectangle is transformed by the current transform.
         * @note In case the rotation of previous scissor rect differs from the current one, 
         * the intersection will be done between the specified rectangle and the previous scissor 
         * rectangle transformed in the current transform space. The resulting shape is always 
         * rectangle.
         */
        void intersectScissor(const Vec2f& pos, const Vec2f& size) const;
        /**
         * @brief Reset and disables scissoring
         */
        void resetScissor() const;
        /**
         * @brief Clears the current path and sub-paths
         */
        void beginPath() const;
        /**
         * @brief Starts new sub-path with specified point as first point
         */
        void moveTo(const Vec2f& pos) const;
        /**
         * @brief Adds line segment from the last point in the path to the specified point
         */
        void lineTo(const Vec2f& pos) const;
        /**
         * @brief Adds cubic bezier segment from last point in the path via two control points
         * to the specified point
         */
        void bezierTo(const Vec2f& c1, const Vec2f& c2, const Vec2f& pos) const;
        /**
         * @brief Adds quadratic bezier segment from last point in the path via a control point to 
         * the specified point
         */
        void quadTo(const Vec2f& c, const Vec2f& pos) const;
        /**
         * @brief Adds an arc segment at the corner defined by the last path point, and two 
         * specified points
         */
        void arcTo(const Vec2f& x1, const Vec2f& x2, float angle) const;
        /**
        * @brief Adds an arc segment at the corner defined by the last path point, and two
        * specified points
        */
        void arcToRad(const Vec2f& x1, const Vec2f& x2, float angle) const;
        /**
         * @brief Closes current sub-path with a line segment
         */
        void closePath() const;
        /**
         * @brief Sets the current sub-path winding
         */
        void pathWinding(Winding dir) const;
        /**
        * @brief Sets the current sub-path winding
        */
        void pathWinding(Solidity dir) const;
        /**
         * @brief Creates new circle arc shaped sub-path
         * @details The arc center is at cx,cy, the arc radius is r, and the arc is drawn from
         * angle a0 to a1, and swept in direction dir (Winding::CCW, or Winding::CW). Angles 
         * are specified in degrees.
         */
        void arc(const Vec2f& center, float r, float a0, float a1, Winding dir) const;
        /**
        * @brief Creates new circle arc shaped sub-path
        * @details The arc center is at cx,cy, the arc radius is r, and the arc is drawn from
        * angle a0 to a1, and swept in direction dir (Winding::CCW, or Winding::CW). Angles 
        * are specified in radians.
        */
        void arcRad(const Vec2f& center, float r, float a0, float a1, Winding dir) const;
        /**
         * @brief Creates new rectangle shaped sub-path
         */
        void rect(const Vec2f& pos, const Vec2f& size) const;
        /**
         * @brief Creates new rounded rectangle shaped sub-path
         */
        void roundedRect(const Vec2f& pos, const Vec2f& size, float r) const;
        /**
         * @brief Creates new rounded rectangle shaped sub-path with varying radii for each corner
         */
        void roundedRect(const Vec2f& pos, const Vec2f& size, float radTopLeft,
            float radTopRight, float radBottomRight, float radBottomLeft) const;
        /**
         * @brief Creates new ellipse shaped sub-path
         */
        void ellipse(const Vec2f& pos, float rx, float ry) const;
        /**
         * @brief Creates new circle shaped sub-path
         */
        void circle(const Vec2f& pos, float r) const;
        /**
         * @brief Fills the current path with current fill style
         */
        void fill() const;
        /**
         * @brief Fills the current path with current stroke style
         */
        void stroke() const;
        /**
         * @brief Creates font by loading it from the disk from specified file name
         */
        Font createFont(const std::string& filename) const;
        /**
         * @brief Creates font by loading it from the specified memory chunk
         */
        Font createFontMem(unsigned char* data, size_t length) const;
        /**
         * @brief Adds a fallback font by handle
         */
        void addFallbackFontId(Font& baseFont, Font& fallbackFont) const;
        /**
         * @brief Sets the font size of current text style
         */
        void fontSize(float size) const;
        /**
         * @brief Sets the blur of current text style
         */
        void fontBlur(float blur) const;
        /**
         * @brief Sets the letter spacing of current text style
         */
        void textLetterSpacing(float spacing) const;
        /**
         * @brief Sets the proportional line height of current text style. The line height 
         * is specified as multiple of font size.
         */
        void textLineHeight(float lineHeight) const;
        /**
         * @brief Sets the text align of current text style
         */
        void textAlign(TextAlign::Flag align) const;
        /**
         * @brief Sets the font face based on specified id of current text style
         */
        void fontFace(const Font& font) const;
        /**
         * @brief Draws text string at specified location
         * @details If end is specified only the sub-string up to the end is drawn.
         */
        void text(const Vec2f& pos, const char* string, const char* end) const;
        /**
        * @brief Draws text string at specified location
        * @details If end is specified only the sub-string up to the end is drawn.
        */
        void text(const Vec2f& pos, const std::string& str) const;
        /**
         * @brief Draws multi-line text string at specified location wrapped at the specified width
         * @details If end is specified only the sub-string up to the end is drawn. White space is
         * stripped at the beginning of the rows, the text is split at word boundaries or when
         * new-line characters are encountered. Words longer than the max width are slit at 
         * nearest character (i.e. no hyphenation).
         */
        void textBox(const Vec2f& pos, float breakRowWidth, const char* string,
            const char* end) const;
        /**
        * @brief Draws multi-line text string at specified location wrapped at the specified width
        * @details If end is specified only the sub-string up to the end is drawn. White space is
        * stripped at the beginning of the rows, the text is split at word boundaries or when
        * new-line characters are encountered. Words longer than the max width are slit at
        * nearest character (i.e. no hyphenation).
        */
        void textBox(const Vec2f& pos, float breakRowWidth, const std::string& str) const;
        /**
         * @brief Measures the specified text string
         * @details Parameter bounds should be a pointer to float[4], if the bounding box of the 
         * text should be returned. The bounds value are [xmin,ymin, xmax,ymax] Returns the 
         * horizontal advance of the measured text (i.e. where the next character should drawn).
         * Measured values are returned in local coordinate space.
         */
        float textBounds(const Vec2f& pos, const char* string,
            const char* end, Vec4f& bounds) const;
        /**
        * @brief Measures the specified text string
        * @details Parameter bounds should be a pointer to float[4], if the bounding box of the
        * text should be returned. The bounds value are [xmin,ymin, xmax,ymax] Returns the
        * horizontal advance of the measured text (i.e. where the next character should drawn).
        * Measured values are returned in local coordinate space.
        */
        float textBounds(const Vec2f& pos, const std::string& str, Vec4f& bounds) const;
        /**
         * @brief Measures the specified multi-text string
         * @details Parameter bounds should be a pointer to float[4], if the bounding box of the 
         * text should be returned. The bounds value are [xmin,ymin, xmax,ymax] Measured values 
         * are returned in local coordinate space.
         */
        Vec2f textBoxBounds(const Vec2f& pos, float breakRowWidth,
            const char* string, const char* end) const;
        /**
        * @brief Measures the specified multi-text string
        * @details Parameter bounds should be a pointer to float[4], if the bounding box of the
        * text should be returned. The bounds value are [xmin,ymin, xmax,ymax] Measured values
        * are returned in local coordinate space.
        */
        Vec2f textBoxBounds(const Vec2f& pos, float breakRowWidth, const std::string& str) const ;
        /**
         * @brief Returns the vertical metrics based on the current text style
         * @details Measured values are returned in local coordinate space.
         */
        void textMetrics(float& ascender, float& descender, float& lineh) const;

        friend Font;
        friend Image;
    private:
        void removeFont(Font& font) const;
        void removeImage(Image& image) const;

        class Impl;
        std::unique_ptr<Impl> pimpl;
    };
}

inline void swap(ffw::GLCanvas& first, ffw::GLCanvas& second) NOEXCEPT {
    first.swap(second);
}

inline void swap(ffw::GLCanvas::Font& first, ffw::GLCanvas::Font& second) NOEXCEPT {
    first.swap(second);
}

inline void swap(ffw::GLCanvas::Image& first, ffw::GLCanvas::Image& second) NOEXCEPT {
    first.swap(second);
}

#endif
