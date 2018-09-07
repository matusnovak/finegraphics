#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/glbuffer.h>
#include "dummywindow.h"
#include "traits.h"

TEST_CASE("Test functionality", "ffw::GLBuffer") {
    DUMMY_APP;

    SECTION("default constructor") {
        ffw::GLBuffer buffer;
        REQUIRE(buffer.isCreated() == false);
        REQUIRE(buffer.getHandle() == 0);
        REQUIRE_THROWS_AS(buffer.getData(0, 8), ffw::GLException);
    }

    SECTION("basic functionality") {
        static const short data[4] = { 0x00, 0x42, 0x128, 0x255 };
        ffw::GLBuffer buffer = ffw::GLBuffer(GL_ARRAY_BUFFER, &data, sizeof(short) * 4, GL_STATIC_READ);
        REQUIRE(buffer.isCreated() == true);
        REQUIRE(buffer.getHandle() != 0);
        REQUIRE(buffer.getAccessType() == GL_STATIC_READ);
        REQUIRE(buffer.getSize() == 8);
        REQUIRE(buffer.getBufferType() == GL_ARRAY_BUFFER);
        const auto buff = buffer.getData(0, sizeof(short) * 4);
        const auto ptr = reinterpret_cast<const short*>(&buff[0]);
        REQUIRE(buff.size() == 8);
        REQUIRE(ptr[0] == 0x00);
        REQUIRE(ptr[1] == 0x42);
        REQUIRE(ptr[2] == 0x128);
        REQUIRE(ptr[3] == 0x255);

        buffer.destroy();
        REQUIRE(buffer.isCreated() == false);
        REQUIRE(buffer.getHandle() == 0);
        REQUIRE_THROWS_AS(buffer.getData(0, 8), ffw::GLException);
    }

    SECTION("copy buffers") {
        static const short dataA[4] = { 0x00, 0x42, 0x128, 0x255 };

        ffw::GLBuffer bufferA = ffw::GLBuffer(GL_ARRAY_BUFFER, &dataA, sizeof(short) * 4, GL_STATIC_READ);
        ffw::GLBuffer bufferB = ffw::GLBuffer(GL_ARRAY_BUFFER, nullptr, sizeof(short) * 4, GL_DYNAMIC_DRAW);

        REQUIRE(bufferA.isCreated() == true);
        REQUIRE(bufferA.getHandle() != 0);
        REQUIRE(bufferB.isCreated() == true);
        REQUIRE(bufferB.getHandle() != 0);

        bufferB.copyFrom(&bufferA, sizeof(short) * 2, 0, sizeof(short) * 2);
        const auto buff = bufferB.getData(0, sizeof(short) * 4);
        const auto ptr = reinterpret_cast<const short*>(&buff[0]);
        REQUIRE(ptr[0] == 0x128);
        REQUIRE(ptr[1] == 0x255);
    }

    SECTION("swap buffers") {
        static const short dataA[4] = { 0x00, 0x42, 0x128, 0x255 };

        ffw::GLBuffer bufferA = ffw::GLBuffer(GL_ARRAY_BUFFER, &dataA, sizeof(short) * 4, GL_STATIC_READ);
        ffw::GLBuffer bufferB;

        std::swap(bufferA, bufferB);

        REQUIRE(bufferB.isCreated() == true);
        REQUIRE(bufferB.getHandle() != 0);
        REQUIRE(bufferB.getAccessType() == GL_STATIC_READ);
        REQUIRE(bufferB.getSize() == 8);
        REQUIRE(bufferB.getBufferType() == GL_ARRAY_BUFFER);

        REQUIRE(bufferA.isCreated() == false);
        REQUIRE(bufferA.getHandle() == 0);
        REQUIRE(bufferA.getSize() == 0);
    }

    SECTION_TEST_MOVEABLE(ffw::GLBuffer);
    SECTION_TEST_NOT_COPYABLE(ffw::GLBuffer);
}
