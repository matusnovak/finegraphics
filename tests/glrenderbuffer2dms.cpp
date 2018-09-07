#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/glrenderbuffer2dms.h>
#include "dummywindow.h"
#include "traits.h"

TEST_CASE("Test functionality", "ffw::GLRenderbuffer2DMS") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLRenderbuffer2DMS buffer;
        REQUIRE(buffer.isCreated() == false);
        REQUIRE(buffer.getHandle() == 0);
        REQUIRE_THROWS_AS(buffer.resize(512, 512, 4), ffw::GLException);
    }

    SECTION("basic functionality") {
        static const short data[4] = { 0x00, 0x42, 0x128, 0x255 };
        ffw::GLRenderbuffer2DMS buffer = ffw::GLRenderbuffer2DMS(1024, 512, GL_RGBA8, 4);
        REQUIRE(buffer.isCreated() == true);
        REQUIRE(buffer.getHandle() != 0);
        REQUIRE(buffer.getWidth() == 1024);
        REQUIRE(buffer.getHeight() == 512);
        REQUIRE(buffer.getSamples() == 4);
        REQUIRE(buffer.getInternalFormat() == GL_RGBA8);

        buffer.resize(2048, 512, 8);
        REQUIRE(buffer.isCreated() == true);
        REQUIRE(buffer.getHandle() != 0);
        REQUIRE(buffer.getWidth() == 2048);
        REQUIRE(buffer.getHeight() == 512);
        REQUIRE(buffer.getSamples() == 8);
        REQUIRE(buffer.getInternalFormat() == GL_RGBA8);

        buffer.destroy();
        REQUIRE(buffer.isCreated() == false);
        REQUIRE(buffer.getHandle() == 0);
        REQUIRE(buffer.getWidth() == 0);
        REQUIRE(buffer.getHeight() == 0);
        REQUIRE(buffer.getSamples() == 0);
        REQUIRE_THROWS_AS(buffer.resize(512, 512, 4), ffw::GLException);
    }

    SECTION("swap buffers") {
        static const short dataA[4] = { 0x00, 0x42, 0x128, 0x255 };

        ffw::GLRenderbuffer2DMS bufferA = ffw::GLRenderbuffer2DMS(1024, 512, GL_RGBA8, 4);
        ffw::GLRenderbuffer2DMS bufferB;

        std::swap(bufferA, bufferB);

        REQUIRE(bufferB.isCreated() == true);
        REQUIRE(bufferB.getHandle() != 0);
        REQUIRE(bufferB.getWidth() == 1024);
        REQUIRE(bufferB.getHeight() == 512);
        REQUIRE(bufferB.getSamples() == 4);
        REQUIRE(bufferB.getInternalFormat() == GL_RGBA8);

        REQUIRE(bufferA.isCreated() == false);
        REQUIRE(bufferA.getHandle() == 0);
        REQUIRE(bufferA.getWidth() == 0);
        REQUIRE(bufferA.getHeight() == 0);
    }

    SECTION_TEST_MOVEABLE(ffw::GLRenderbuffer2DMS);
    SECTION_TEST_NOT_COPYABLE(ffw::GLRenderbuffer2DMS);
}
