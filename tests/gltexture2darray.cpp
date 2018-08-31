#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/gltexture2darray.h>
#include "dummywindow.h"
#include "traits.h"

static bool compareArray(const uint8_t* a, const uint8_t* b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i])return false;
    }
    return true;
}

TEST_CASE("Test functionality", "ffw::GLTexture2DArray") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLTexture2DArray tex;
        REQUIRE(tex.isCreated() == false);
        REQUIRE(tex.getHandle() == 0);
        REQUIRE(tex.getWidth() == 0);
        REQUIRE(tex.getHeight() == 0);
        REQUIRE(tex.getDepth() == 0);
        REQUIRE(tex.getLayers() == 0);
        REQUIRE(tex.getSamples() == 0);
        REQUIRE(tex.getInternalFormat() == 0);
        REQUIRE(tex.getFormat() == 0);
        REQUIRE(tex.getPixelFormat() == 0);
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_2D_ARRAY);
        REQUIRE(tex.isCompressed() == false);
    }

    static const uint8_t pixels[4 * 4 * 2 * 3] = {
        // Layer 0
        255, 0, 0,
        255, 0, 0,
        0, 255, 0,
        0, 255, 0,

        255, 0, 0,
        255, 0, 0,
        0, 255, 0,
        0, 255, 0,

        0, 0, 255,
        0, 0, 255,
        255, 255, 255,
        255, 255, 255,

        0, 0, 255,
        0, 0, 255,
        255, 255, 255,
        255, 255, 255,

        // Layer 1
        128, 0, 0,
        128, 0, 0,
        0, 128, 0,
        0, 128, 0,

        128, 0, 0,
        128, 0, 0,
        0, 128, 0,
        0, 128, 0,

        0, 0, 128,
        0, 0, 128,
        128, 128, 128,
        128, 128, 128,

        0, 0, 128,
        0, 0, 128,
        128, 128, 128,
        128, 128, 128,
    };

    SECTION("basic functionality") {
        // tex of size 4x2 in 2 layers
        ffw::GLTexture2DArray tex = ffw::GLTexture2DArray(4, 4, 2, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        REQUIRE(tex.isCreated() == true);
        REQUIRE(tex.getHandle() != 0);
        REQUIRE(tex.getWidth() == 4);
        REQUIRE(tex.getHeight() == 4);
        REQUIRE(tex.getDepth() == 0);
        REQUIRE(tex.getLayers() == 2);
        REQUIRE(tex.getSamples() == 0);
        REQUIRE(tex.getInternalFormat() == GL_RGB8);
        REQUIRE(tex.getFormat() == GL_RGB);
        REQUIRE(tex.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_2D_ARRAY);
        REQUIRE(tex.isCompressed() == false);

        uint8_t ret[4 * 4 * 2 * 3] = { 0 };
        tex.getPixels(ret);
        REQUIRE(compareArray(pixels, ret, 4 * 4 * 2 * 3) == true);

        // Tex of 4x2 pixels with 2 layers.
        // the layer 1 from "pixels" is split in two.
        tex.resize(4, 2, 2, pixels + 4 * 4 * 3);
        REQUIRE(tex.isCreated() == true);
        REQUIRE(tex.getHandle() != 0);
        REQUIRE(tex.getWidth() == 4);
        REQUIRE(tex.getHeight() == 2);
        REQUIRE(tex.getDepth() == 0);
        REQUIRE(tex.getLayers() == 2);
        REQUIRE(tex.getSamples() == 0);
        REQUIRE(tex.getInternalFormat() == GL_RGB8);
        REQUIRE(tex.getFormat() == GL_RGB);
        REQUIRE(tex.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_2D_ARRAY);
        REQUIRE(tex.isCompressed() == false);

        uint8_t ret2[4 * 2 * 2 * 3] = { 0 };
        tex.getPixels(ret2);
        REQUIRE(compareArray(pixels + 4 * 2 * 2 * 3, ret2, 4 * 2 * 2 * 3) == true);

        static const uint8_t newPixels[4 * 1 * 3] = {
            128, 128, 128,
            128, 128, 128,
            128, 128, 128,
            128, 128, 128
        };

        tex.setPixels(0, 0, 1, 1, 4, 1, &newPixels);
        tex.getPixels(ret2);

        REQUIRE(compareArray(newPixels, ret2 + 4 * 3 * 3, 4 * 1 * 3) == true);

        tex.destroy();

        REQUIRE(tex.isCreated() == false);
        REQUIRE(tex.getHandle() == 0);
        REQUIRE(tex.getWidth() == 0);
        REQUIRE(tex.getHeight() == 0);
        REQUIRE(tex.getDepth() == 0);
        REQUIRE(tex.getLayers() == 0);
        REQUIRE(tex.getSamples() == 0);
        REQUIRE(tex.getInternalFormat() == 0);
        REQUIRE(tex.getFormat() == 0);
        REQUIRE(tex.getPixelFormat() == 0);
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_2D_ARRAY);
        REQUIRE(tex.isCompressed() == false);
    }

    SECTION("swap textures") {
        ffw::GLTexture2DArray texA = ffw::GLTexture2DArray(4, 4, 2, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        ffw::GLTexture2DArray texB;

        REQUIRE(texA.isCreated() == true);
        REQUIRE(texA.getHandle() != 0);

        std::swap(texA, texB);

        REQUIRE(texB.isCreated() == true);
        REQUIRE(texB.getHandle() != 0);
        REQUIRE(texB.getWidth() == 4);
        REQUIRE(texB.getHeight() == 4);
        REQUIRE(texB.getDepth() == 0);
        REQUIRE(texB.getLayers() == 2);
        REQUIRE(texB.getSamples() == 0);
        REQUIRE(texB.getInternalFormat() == GL_RGB8);
        REQUIRE(texB.getFormat() == GL_RGB);
        REQUIRE(texB.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(texB.getTextureFormat() == GL_TEXTURE_2D_ARRAY);
        REQUIRE(texB.isCompressed() == false);
    }

    SECTION_TEST_MOVEABLE(ffw::GLTexture2DArray);
    SECTION_TEST_NOT_COPYABLE(ffw::GLTexture2DArray);
}
