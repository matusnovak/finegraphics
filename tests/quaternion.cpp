#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/quaternion.h>

TEST_CASE("constructors", "ffw::Quaternion") {
    ffw::Quaternionf q(0.9f, 0.5f, 0.0f, 1.0f);
    REQUIRE(q.x == Approx(0.9f));
    REQUIRE(q.y == Approx(0.5f));
    REQUIRE(q.z == Approx(0.0f));
    REQUIRE(q.w == Approx(1.0f));
}

TEST_CASE("multiplication", "ffw::Quaternion") {
    ffw::Quaternionf a(0.9f, 0.5f, 0.0f, 1.0f);

    ffw::Quaternionf b(0.1f, 0.3f, 0.2f, 0.4f);

    const auto q = a * b;

    REQUIRE(q.x == Approx(0.56f));
    REQUIRE(q.y == Approx(0.32f));
    REQUIRE(q.z == Approx(0.42f));
    REQUIRE(q.w == Approx(0.16f));
}

TEST_CASE("multiplication assingment", "ffw::Quaternion") {
    ffw::Quaternionf a(0.9f, 0.5f, 0.0f, 1.0f);

    ffw::Quaternionf b(0.1f, 0.3f, 0.2f, 0.4f);

    a *= b;

    REQUIRE(a.x == Approx(0.56f));
    REQUIRE(a.y == Approx(0.32f));
    REQUIRE(a.z == Approx(0.42f));
    REQUIRE(a.w == Approx(0.16f));
}

TEST_CASE("inverse", "ffw::Quaternion") {
    ffw::Quaternionf a(0.9f, 0.5f, 0.0f, 1.0f);

    a.inverse();

    REQUIRE(a.x == Approx(-0.436893f));
    REQUIRE(a.y == Approx(-0.242718f));
    REQUIRE(a.z == Approx(0.0f));
    REQUIRE(a.w == Approx(0.485437f));
}

TEST_CASE("constant addition", "ffw::Quaternion") {
    ffw::Quaternionf a(0.9f, 0.5f, 0.0f, 1.0f);

    const auto q = a + 0.1f;

    REQUIRE(q.x == Approx(1.0f));
    REQUIRE(q.y == Approx(0.6f));
    REQUIRE(q.z == Approx(0.1f));
    REQUIRE(q.w == Approx(1.1f));
}

TEST_CASE("constant substraction", "ffw::Quaternion") {
    ffw::Quaternionf a(0.9f, 0.5f, 0.0f, 1.0f);

    const auto q = a - 0.1f;

    REQUIRE(q.x == Approx(0.8f));
    REQUIRE(q.y == Approx(0.4f));
    REQUIRE(q.z == Approx(-0.1f));
    REQUIRE(q.w == Approx(0.9f));
}

TEST_CASE("constant multiplication", "ffw::Quaternion") {
    ffw::Quaternionf a(0.9f, 0.5f, 0.0f, 1.0f);

    const auto q = a * 0.5f;

    REQUIRE(q.x == Approx(0.45f));
    REQUIRE(q.y == Approx(0.25f));
    REQUIRE(q.z == Approx(0.0f));
    REQUIRE(q.w == Approx(0.5f));
}

TEST_CASE("constant division", "ffw::Quaternion") {
    ffw::Quaternionf a(0.9f, 0.5f, 0.0f, 1.0f);

    const auto q = a / 2.0f;

    REQUIRE(q.x == Approx(0.45f));
    REQUIRE(q.y == Approx(0.25f));
    REQUIRE(q.z == Approx(0.0f));
    REQUIRE(q.w == Approx(0.5f));
}

