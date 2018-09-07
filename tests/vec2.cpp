#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <ffw/graphics/vec2.h>

TEST_CASE("Testing Vec2", "ffw::Vec2") {
    {
        ffw::Vec2i vec;
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
    }

    {
        ffw::Vec2i vec(42);
        REQUIRE(vec.x == 42);
        REQUIRE(vec.y == 42);
    }

    {
        ffw::Vec2i vec(10, 20);
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
    }

    {
        ffw::Vec2i vec({ 10, 20 });
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
    }

    {
        ffw::Vec2i vec({ 10, 20, 30 });
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
    }

    {
        ffw::Vec2i vec;
        vec.set(42);
        REQUIRE(vec.x == 42);
        REQUIRE(vec.y == 42);
    }

    {
        ffw::Vec2i vec;
        vec.set(10, 20);
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
    }

    {
        ffw::Vec2i vec;
        vec.set({ 10, 20 });
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
    }

    {
        ffw::Vec2i vec;
        vec.set({ 10, 20, 30 });
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
    }

    {
        ffw::Vec2i vec = { 10, 20 };
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
    }

    {
        ffw::Vec2i a(1, 5);
        ffw::Vec2i b(5, 10);
        ffw::Vec2i c = a + b;
        REQUIRE(c.x == 6);
        REQUIRE(c.y == 15);
        REQUIRE(a + b == c);
        b += a;
        REQUIRE(b == c);
    }

    {
        ffw::Vec2i a(5, 10);
        ffw::Vec2i b(1, 5);
        ffw::Vec2i c = a - b;
        REQUIRE(c.x == 4);
        REQUIRE(c.y == 5);
        REQUIRE(a - b == c);
        a -= b;
        REQUIRE(a == c);
    }

    {
        ffw::Vec2i a(5, 10);
        ffw::Vec2i b(1, 5);
        ffw::Vec2i c = a * b;
        REQUIRE(c.x == 5);
        REQUIRE(c.y == 50);
        REQUIRE(a * b == c);
        b *= a;
        REQUIRE(b == c);
    }

    {
        ffw::Vec2i a(6, 12);
        ffw::Vec2i b(2, 3);
        ffw::Vec2i c = a / b;
        REQUIRE(c.x == 3);
        REQUIRE(c.y == 4);
        REQUIRE(a / b == c);
        a /= b;
        REQUIRE(a == c);
    }

    REQUIRE(ffw::Vec2i(1, 2) == ffw::Vec2i(1, 2));
    REQUIRE(ffw::Vec2i(1, 2) != ffw::Vec2i(2, 2));
    REQUIRE(ffw::Vec2i(1, 2) != ffw::Vec2i(1, 1));
    REQUIRE(ffw::Vec2f(1.0f, 2.0f) == ffw::Vec2f(1.0f, 2.0f));
    REQUIRE(ffw::Vec2f(1.0f, 2.0f) != ffw::Vec2f(1.0f, 2.001f));

    {
        ffw::Vec2i a(6, 12);
        ffw::Vec2i b = -a;
        REQUIRE(b.x == -6);
        REQUIRE(b.y == -12);
        b = -b;
        REQUIRE(b == a);
    }

    {
        ffw::Vec2i vec(5, 10);
        vec.scale(3);
        REQUIRE(vec.x == 15);
        REQUIRE(vec.y == 30);
    }

    {
        ffw::Vec2f vec(3.0f, 4.0f);
        vec.normalize();
        REQUIRE(std::fabs(vec.x - 3.0f / 5.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 4.0f / 5.0f) < 0.01f);
    }

    {
        ffw::Vec2f vec(1.0f, 0.0f);
        vec.rotate(90.0f);
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 1.0f) < 0.01f);
    }

    {
        ffw::Vec2f vec(1.0f, 0.0f);
        vec.rotateRad(90.0f * DEG_TO_RAD);
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 1.0f) < 0.01f);
    }

    {
        ffw::Vec2f vec(1.0f, 1.0f);
        REQUIRE(std::fabs(vec.length() - sqrt(2.0)) < 0.01);
    }

    {
        ffw::Vec2i vec(1, 1);
        REQUIRE(std::fabs(vec.length() - sqrt(2.0)) < 0.01);
    }

    {
        ffw::Vec2f vec(1.0f, 1.0f);
        REQUIRE(vec.lengthSqrd() == 2.0f);
    }

    {
        ffw::Vec2i vec(1, 1);
        REQUIRE(vec.lengthSqrd() == 2);
    }
}

TEST_CASE("Testing dot", "ffw::Vec2") {
    // dot product
    REQUIRE(ffw::dot(
        ffw::Vec2d(1.5, 0.0),
        ffw::Vec2d(1.0, 0.0))
        == Approx(3.0 / 2.0));
}

TEST_CASE("Testing distance", "ffw::Vec2") {
    // distance
    REQUIRE(ffw::distance(
        ffw::Vec2f(7.0f, 4.0f),
        ffw::Vec2f(-2.0f, 5.0f))
        == Approx(9.0554f));
}

TEST_CASE("Testing middle", "ffw::Vec2") {
    // middle
    REQUIRE(ffw::middle(
        ffw::Vec2f(3.0f, 0.0f),
        ffw::Vec2f(-3.0f, 1.0f))
        == ffw::Vec2f(0.0f, 0.5f));
}

TEST_CASE("Testing normalize", "ffw::Vec2") {
    // normalize
    auto v = ffw::Vec2f(1.0f, 2.0f).normalize();
    REQUIRE(v == ffw::normalize(ffw::Vec2f(1.0f, 2.0f)));
}

TEST_CASE("Testing angle", "ffw::Vec2") {
    // angle
    REQUIRE(ffw::angle(
        ffw::Vec2f(1.0f, 0.0f),
        ffw::Vec2f(0.0f, 1.0f))
        == Approx(90.0f));

    REQUIRE(ffw::angle(
        ffw::Vec2f(0.707f, 0.707f),
        ffw::Vec2f(0.0f, 1.0f))
        == Approx(45.0f));

    REQUIRE(ffw::angleRad(
        ffw::Vec2f(1.0f, 0.0f),
        ffw::Vec2f(0.0f, 1.0f))
        == Approx(90.0f * DEG_TO_RAD));

    REQUIRE(ffw::angleRad(
        ffw::Vec2f(0.707f, 0.707f),
        ffw::Vec2f(0.0f, 1.0f))
        == Approx(45.0f * DEG_TO_RAD));
}

TEST_CASE("sizeof", "ffw::Vec2") {
    REQUIRE(sizeof(ffw::Vec2f) == sizeof(float) * 2);
    REQUIRE(sizeof(ffw::Vec2i) == sizeof(int) * 2);
    REQUIRE(sizeof(ffw::Vec2d) == sizeof(double) * 2);
}
