#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/gltexture1d.h>
#include "dummywindow.h"
#include "traits.h"

static bool compareArray(const uint8_t* a, const uint8_t* b, size_t len) {
    for(size_t i = 0; i < len; i++) {
        if(a[i] != b[i])return false;
    }
    return true;
}

TEST_CASE("Test functionality", "ffw::GLTexture1D") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLTexture1D tex;
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
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_1D);
        REQUIRE(tex.isCompressed() == false);
    }

    static const uint8_t pixels[8 * 3] = {
        255, 0, 0,
        0, 255, 0,
        0, 0, 255,
        0, 0, 0,
        255, 255, 255,
        255, 255, 0,
        0, 255, 255,
        255, 0, 255
    };

    SECTION("basic functionality") {
        ffw::GLTexture1D tex = ffw::GLTexture1D(8, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        REQUIRE(tex.isCreated() == true);
        REQUIRE(tex.getHandle() != 0);
        REQUIRE(tex.getWidth() == 8);
        REQUIRE(tex.getHeight() == 1);
        REQUIRE(tex.getDepth() == 0);
        REQUIRE(tex.getLayers() == 0);
        REQUIRE(tex.getSamples() == 0);
        REQUIRE(tex.getInternalFormat() == GL_RGB8);
        REQUIRE(tex.getFormat() == GL_RGB);
        REQUIRE(tex.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_1D);
        REQUIRE(tex.isCompressed() == false);

        uint8_t ret[8 * 3] = { 0 };
        tex.getPixels(ret);
        REQUIRE(compareArray(pixels, ret, 8 * 3) == true);

        tex.resize(4, pixels + 4 * 3); // Last 4 pixels
        REQUIRE(tex.isCreated() == true);
        REQUIRE(tex.getHandle() != 0);
        REQUIRE(tex.getWidth() == 4);
        REQUIRE(tex.getHeight() == 1);
        REQUIRE(tex.getDepth() == 0);
        REQUIRE(tex.getLayers() == 0);
        REQUIRE(tex.getSamples() == 0);
        REQUIRE(tex.getInternalFormat() == GL_RGB8);
        REQUIRE(tex.getFormat() == GL_RGB);
        REQUIRE(tex.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_1D);
        REQUIRE(tex.isCompressed() == false);

        uint8_t ret2[4 * 3] = { 0 };
        tex.getPixels(ret2);
        REQUIRE(compareArray(pixels + 4 * 3, ret2, 4 * 3) == true);

        static const uint8_t newPixels[2*3] = {
            128, 128, 128, 
            128, 128, 128
        };

        tex.setPixels(0, 2, 2, &newPixels);
        tex.getPixels(ret2);

        REQUIRE(compareArray(pixels + 4 * 3, ret2, 2 * 3) == true);
        REQUIRE(compareArray(newPixels, ret2 + 2 * 3, 2 * 3) == true);

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
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_1D);
        REQUIRE(tex.isCompressed() == false);
    }

    SECTION("swap textures") {
        ffw::GLTexture1D texA = ffw::GLTexture1D(8, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        ffw::GLTexture1D texB;

        REQUIRE(texA.isCreated() == true);
        REQUIRE(texA.getHandle() != 0);

        std::swap(texA, texB);

        REQUIRE(texB.isCreated() == true);
        REQUIRE(texB.getHandle() != 0);
        REQUIRE(texB.getWidth() == 8);
        REQUIRE(texB.getHeight() == 1);
        REQUIRE(texB.getDepth() == 0);
        REQUIRE(texB.getLayers() == 0);
        REQUIRE(texB.getSamples() == 0);
        REQUIRE(texB.getInternalFormat() == GL_RGB8);
        REQUIRE(texB.getFormat() == GL_RGB);
        REQUIRE(texB.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(texB.getTextureFormat() == GL_TEXTURE_1D);
        REQUIRE(texB.isCompressed() == false);
    }

    SECTION_TEST_MOVEABLE(ffw::GLTexture1D);
    SECTION_TEST_NOT_COPYABLE(ffw::GLTexture1D);
}
