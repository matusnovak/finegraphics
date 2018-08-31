#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/gltexture3d.h>
#include "dummywindow.h"
#include "traits.h"

static bool compareArray(const uint8_t* a, const uint8_t* b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i])return false;
    }
    return true;
}

TEST_CASE("Test functionality", "ffw::GLTexture3D") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLTexture3D tex;
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
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_3D);
        REQUIRE(tex.isCompressed() == false);
    }

    static const uint8_t pixels[4 * 4 * 4 * 3] = {
        32, 0, 0,
        32, 0, 0,
        32, 0, 0,
        32, 0, 0,
        0, 32, 0,
        0, 32, 0,
        0, 32, 0,
        0, 32, 0,
        0, 0, 32,
        0, 0, 32,
        0, 0, 32,
        0, 0, 32,
        32, 32, 32,
        32, 32, 32,
        32, 32, 32,
        32, 32, 32,

        64, 0, 0,
        64, 0, 0,
        64, 0, 0,
        64, 0, 0,
        0, 64, 0,
        0, 64, 0,
        0, 64, 0,
        0, 64, 0,
        0, 0, 64,
        0, 0, 64,
        0, 0, 64,
        0, 0, 64,
        64, 64, 64,
        64, 64, 64,
        64, 64, 64,
        64, 64, 64,

        128, 0, 0,
        128, 0, 0,
        128, 0, 0,
        128, 0, 0,
        0, 128, 0,
        0, 128, 0,
        0, 128, 0,
        0, 128, 0,
        0, 0, 128,
        0, 0, 128,
        0, 0, 128,
        0, 0, 128,
        128, 128, 128,
        128, 128, 128,
        128, 128, 128,
        128, 128, 128,

        255, 0, 0,
        255, 0, 0,
        255, 0, 0,
        255, 0, 0,
        0, 255, 0,
        0, 255, 0,
        0, 255, 0,
        0, 255, 0,
        0, 0, 255,
        0, 0, 255,
        0, 0, 255,
        0, 0, 255,
        255, 255, 255,
        255, 255, 255,
        255, 255, 255,
        255, 255, 255,
    };

    SECTION("basic functionality") {
        ffw::GLTexture3D tex = ffw::GLTexture3D(4, 4, 4, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        REQUIRE(tex.isCreated() == true);
        REQUIRE(tex.getHandle() != 0);
        REQUIRE(tex.getWidth() == 4);
        REQUIRE(tex.getHeight() == 4);
        REQUIRE(tex.getDepth() == 4);
        REQUIRE(tex.getLayers() == 0);
        REQUIRE(tex.getSamples() == 0);
        REQUIRE(tex.getInternalFormat() == GL_RGB8);
        REQUIRE(tex.getFormat() == GL_RGB);
        REQUIRE(tex.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_3D);
        REQUIRE(tex.isCompressed() == false);

        uint8_t ret[4 * 4 * 4 * 3] = { 0 };
        tex.getPixels(ret);

        /*for (int i = 0; i < 4 * 4 * 4 * 3; i++) {
            std::cout << int(ret[i]) << ", ";
            if (i % 3 == 2) std::cout << std::endl;
        }
        std::cout << std::endl;*/

        REQUIRE(compareArray(pixels, ret, 4 * 4 * 4 * 3) == true);

        tex.resize(4, 4, 2, pixels + 4 * 4 * 2 * 3); // Last 4x4x2 pixels
        REQUIRE(tex.isCreated() == true);
        REQUIRE(tex.getHandle() != 0);
        REQUIRE(tex.getWidth() == 4);
        REQUIRE(tex.getHeight() == 4);
        REQUIRE(tex.getDepth() == 2);
        REQUIRE(tex.getLayers() == 0);
        REQUIRE(tex.getSamples() == 0);
        REQUIRE(tex.getInternalFormat() == GL_RGB8);
        REQUIRE(tex.getFormat() == GL_RGB);
        REQUIRE(tex.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_3D);
        REQUIRE(tex.isCompressed() == false);

        uint8_t ret2[4 * 4 * 2 * 3] = { 0 };
        tex.getPixels(ret2);
        REQUIRE(compareArray(pixels + 4 * 4 * 2 * 3, ret2, 4 * 4 * 2 * 3) == true);

        static const uint8_t newPixels[4 * 4 * 1 * 3] = {
            1, 0, 0,
            2, 0, 0,
            3, 0, 0,
            4, 0, 0,
            0, 5, 0,
            0, 6, 0,
            0, 7, 0,
            0, 8, 0,
            0, 0, 9,
            0, 0, 10,
            0, 0, 11,
            0, 0, 12,
            13, 13, 13,
            14, 14, 14,
            15, 15, 15,
            16, 16, 16
        };

        tex.setPixels(0, 0, 0, 1, 4, 4, 1, &newPixels);
        tex.getPixels(ret2);

        REQUIRE(compareArray(newPixels, ret2 + 4 * 4 * 1 * 3, 4 * 4 * 1 * 3) == true);

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
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_3D);
        REQUIRE(tex.isCompressed() == false);
    }

    SECTION("swap textures") {
        ffw::GLTexture3D texA = ffw::GLTexture3D(4, 4, 4, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        ffw::GLTexture3D texB;

        REQUIRE(texA.isCreated() == true);
        REQUIRE(texA.getHandle() != 0);

        std::swap(texA, texB);

        REQUIRE(texB.isCreated() == true);
        REQUIRE(texB.getHandle() != 0);
        REQUIRE(texB.getWidth() == 4);
        REQUIRE(texB.getHeight() == 4);
        REQUIRE(texB.getDepth() == 4);
        REQUIRE(texB.getLayers() == 0);
        REQUIRE(texB.getSamples() == 0);
        REQUIRE(texB.getInternalFormat() == GL_RGB8);
        REQUIRE(texB.getFormat() == GL_RGB);
        REQUIRE(texB.getPixelFormat() == GL_UNSIGNED_BYTE);
        REQUIRE(texB.getTextureFormat() == GL_TEXTURE_3D);
        REQUIRE(texB.isCompressed() == false);
    }

    SECTION_TEST_MOVEABLE(ffw::GLTexture3D);
    SECTION_TEST_NOT_COPYABLE(ffw::GLTexture3D);
}
