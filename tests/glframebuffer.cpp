#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/glframebuffer.h>
#include "dummywindow.h"
#include "traits.h"

TEST_CASE("Test functionality", "ffw::GLFramebuffer") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLFramebuffer fbo;
        REQUIRE(fbo.isCreated() == false);
        REQUIRE(fbo.getHandle() == 0);
    }

    SECTION("basic functionality") {
        ffw::GLTexture2D tex = ffw::GLTexture2D(512, 512, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
        REQUIRE(tex.isCreated());

        ffw::GLFramebuffer fbo = ffw::GLFramebuffer({
            ffw::GLFramebuffer::Attachment(&tex, GL_COLOR_ATTACHMENT0)
        });
        REQUIRE(fbo.isCreated());
        REQUIRE(fbo.checkStatus());
        REQUIRE(fbo.getHandle() != 0);

        ffw::GLFramebuffer other = std::move(fbo);
        REQUIRE(other.isCreated());
        REQUIRE(other.checkStatus());
        REQUIRE(other.getHandle() != 0);

        REQUIRE(fbo.isCreated() == false);
        REQUIRE(fbo.checkStatus() == false);
        REQUIRE(fbo.getHandle() == 0);
    }

    SECTION_TEST_MOVEABLE(ffw::GLFramebuffer);
    SECTION_TEST_NOT_COPYABLE(ffw::GLFramebuffer);
}
