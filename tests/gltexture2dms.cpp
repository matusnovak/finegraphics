#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/gltexture2dms.h>
#include "dummywindow.h"
#include "traits.h"

static bool compareArray(const uint8_t* a, const uint8_t* b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i])return false;
    }
    return true;
}

TEST_CASE("Test functionality", "ffw::GLTexture2DMS") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLTexture2DMS tex;
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
        REQUIRE(tex.getTextureFormat() == GL_TEXTURE_2D_MULTISAMPLE);
        REQUIRE(tex.isCompressed() == false);
    }

    SECTION("basic functionality") {
        ffw::GLTexture2DMS texA = ffw::GLTexture2DMS(16, 16, GL_RGB8, 4);
        ffw::GLTexture2DMS texB;

        REQUIRE(texA.isCreated() == true);
        REQUIRE(texA.getHandle() != 0);

        std::swap(texA, texB);

        REQUIRE(texB.isCreated() == true);
        REQUIRE(texB.getHandle() != 0);
        REQUIRE(texB.getWidth() == 16);
        REQUIRE(texB.getHeight() == 16);
        REQUIRE(texB.getDepth() == 0);
        REQUIRE(texB.getLayers() == 0);
        REQUIRE(texB.getSamples() == 4);
        REQUIRE(texB.getInternalFormat() == GL_RGB8);
        REQUIRE(texB.getFormat() == 0);
        REQUIRE(texB.getPixelFormat() == 0);
        REQUIRE(texB.getTextureFormat() == GL_TEXTURE_2D_MULTISAMPLE);
        REQUIRE(texB.isCompressed() == false);

        texB.destroy();

        REQUIRE(texB.isCreated() == false);
        REQUIRE(texB.getHandle() == 0);
        REQUIRE(texB.getWidth() == 0);
        REQUIRE(texB.getHeight() == 0);
        REQUIRE(texB.getDepth() == 0);
        REQUIRE(texB.getLayers() == 0);
        REQUIRE(texB.getSamples() == 0);
        REQUIRE(texB.getInternalFormat() == 0);
        REQUIRE(texB.getFormat() == 0);
        REQUIRE(texB.getPixelFormat() == 0);
        REQUIRE(texB.getTextureFormat() == GL_TEXTURE_2D_MULTISAMPLE);
        REQUIRE(texB.isCompressed() == false);
    }

    SECTION_TEST_MOVEABLE(ffw::GLTexture2DMS);
    SECTION_TEST_NOT_COPYABLE(ffw::GLTexture2DMS);
}
