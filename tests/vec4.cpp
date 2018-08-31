#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <ffw/graphics/vec4.h>

TEST_CASE("Testing Vec4", "ffw::Vec4") {
    {
        ffw::Vec4i vec;
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
        REQUIRE(vec.z == 0);
        REQUIRE(vec.w == 0);
    }

    {
        ffw::Vec4i vec(42);
        REQUIRE(vec.x == 42);
        REQUIRE(vec.y == 42);
        REQUIRE(vec.z == 42);
        REQUIRE(vec.w == 42);
    }

    {
        ffw::Vec4i vec(10, 20, 30, 40);
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
        REQUIRE(vec.w == 40);
    }

    {
        ffw::Vec4i vec({ 10, 20, 30, 40 });
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
        REQUIRE(vec.w == 40);
    }

    {
        ffw::Vec4i vec({ 10, 20, 30, 40, 50 });
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
        REQUIRE(vec.z == 0);
        REQUIRE(vec.w == 0);
    }

    {
        ffw::Vec4i vec;
        vec.set(42);
        REQUIRE(vec.x == 42);
        REQUIRE(vec.y == 42);
        REQUIRE(vec.z == 42);
        REQUIRE(vec.w == 42);
    }

    {
        ffw::Vec4i vec;
        vec.set(10, 20, 30, 40);
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
        REQUIRE(vec.w == 40);
    }

    {
        ffw::Vec4i vec;
        vec.set({ 10, 20, 30, 40 });
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
        REQUIRE(vec.w == 40);
    }

    {
        ffw::Vec4i vec(5);
        vec.set({ 10, 20, 30, 40, 50 });
        REQUIRE(vec.x == 5);
        REQUIRE(vec.y == 5);
        REQUIRE(vec.z == 5);
        REQUIRE(vec.w == 5);
    }

    {
        ffw::Vec4i vec = { 10, 20, 30, 40 };
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
        REQUIRE(vec.w == 40);
    }

    {
        ffw::Vec4i a(1, 5, 10, 6);
        ffw::Vec4i b(5, 10, 2, 2);
        ffw::Vec4i c = a + b;
        REQUIRE(c.x == 6);
        REQUIRE(c.y == 15);
        REQUIRE(c.z == 12);
        REQUIRE(c.w == 8);
        REQUIRE(a + b == c);
        b += a;
        REQUIRE(b == c);
    }

    {
        ffw::Vec4i a(5, 10, 20, 15);
        ffw::Vec4i b(1, 5, 5, 3);
        ffw::Vec4i c = a - b;
        REQUIRE(c.x == 4);
        REQUIRE(c.y == 5);
        REQUIRE(c.z == 15);
        REQUIRE(c.w == 12);
        REQUIRE(a - b == c);
        a -= b;
        REQUIRE(a == c);
    }

    {
        ffw::Vec4i a(5, 10, 8, 15);
        ffw::Vec4i b(1, 5, 2, 3);
        ffw::Vec4i c = a * b;
        REQUIRE(c.x == 5);
        REQUIRE(c.y == 50);
        REQUIRE(c.z == 16);
        REQUIRE(c.w == 45);
        REQUIRE(a * b == c);
        b *= a;
        REQUIRE(b == c);
    }

    {
        ffw::Vec4i a(6, 12, 25, 15);
        ffw::Vec4i b(2, 3, 5, 3);
        ffw::Vec4i c = a / b;
        REQUIRE(c.x == 3);
        REQUIRE(c.y == 4);
        REQUIRE(c.z == 5);
        REQUIRE(c.w == 5);
        REQUIRE(a / b == c);
        a /= b;
        REQUIRE(a == c);
    }

    REQUIRE(ffw::Vec4i(1, 2, 3, 4) == ffw::Vec4i(1, 2, 3, 4));
    REQUIRE(ffw::Vec4i(1, 2, 3, 4) != ffw::Vec4i(2, 2, 2, 4));
    REQUIRE(ffw::Vec4i(1, 2, 3, 4) != ffw::Vec4i(1, 1, 1, 4));
    REQUIRE(ffw::Vec4i(1, 2, 3, 4) != ffw::Vec4i(3, 3, 3, 4));
    REQUIRE(ffw::Vec4f(1.0f, 2.0f, 3.0f, 4.0f) == ffw::Vec4f(1.0f, 2.0f, 3.0f, 4.0f));
    REQUIRE(ffw::Vec4f(1.0f, 2.0f, 3.0f, 4.0f) != ffw::Vec4f(1.0f, 2.001f, 3.0f, 4.0f));

    {
        ffw::Vec4i a(6, 12, 16, 15);
        ffw::Vec4i b = -a;
        REQUIRE(b.x == -6);
        REQUIRE(b.y == -12);
        REQUIRE(b.z == -16);
        REQUIRE(b.w == -15);
        b = -b;
        REQUIRE(b == a);
    }

    {
        ffw::Vec4i vec(5, 10, 15, 3);
        vec.scale(3);
        REQUIRE(vec.x == 15);
        REQUIRE(vec.y == 30);
        REQUIRE(vec.z == 45);
        REQUIRE(vec.w == 9);
    }

    {
        ffw::Vec4f vec(0.0f, 4.0f, 12.0f, 3.0f);
        vec.normalize();
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 4.0f / 13.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 12.0f / 13.0f) < 0.01f);
        REQUIRE(std::fabs(vec.w - 3.0f / 13.0f) < 0.01f);
    }

    {
        ffw::Vec4f vec(1.0f, 1.0f, 1.0f, 1.0f);
        REQUIRE(std::fabs(vec.length() - sqrt(4.0)) < 0.01);
    }

    {
        ffw::Vec4i vec(1, 1, 1, 1);
        REQUIRE(std::fabs(vec.length() - sqrt(4.0)) < 0.01);
    }

    {
        ffw::Vec4f vec(1.0f, 1.0f, 1.0f, 1.0f);
        REQUIRE(vec.lengthSqrd() == 4.0f);
    }

    {
        ffw::Vec4i vec(1, 1, 1, 1);
        REQUIRE(vec.lengthSqrd() == 4);
    }
}

TEST_CASE("Testing dot", "ffw::Vec4") {
    // dot product
    REQUIRE(ffw::dot(
        ffw::Vec4d(0.0, 1.5, 2.0, 0.0),
        ffw::Vec4d(0.0, 1.0, 0.5, 0.0))
        == Approx(5.0 / 2.0));
}

TEST_CASE("Testing distance", "ffw::Vec4") {
    // distance
    REQUIRE(ffw::distance(
        ffw::Vec4f(1.0f, 7.0f, 4.0f, -9.0f),
        ffw::Vec4f(-1.0f, -2.0f, 5.0f, 1.0f))
        == Approx(13.63818f));
}

TEST_CASE("Testing middle", "ffw::Vec4") {
    // middle
    REQUIRE(ffw::middle(
        ffw::Vec4f(3.0f, 0.0f, -2.0f, 0.0f),
        ffw::Vec4f(-3.0f, 1.0f, -5.0f, 100.f))
        == ffw::Vec4f(0.0f, 0.5f, -3.5f, 50.0f));
}

TEST_CASE("Testing normalize", "ffw::Vec4") {
    // normalize
    auto v = ffw::Vec4f(-2.0f, 7.0f, 3.0f, -1.0f).normalize();
    REQUIRE(v == ffw::normalize(ffw::Vec4f(-2.0f, 7.0f, 3.0f, -1.0f)));
}

TEST_CASE("sizeof", "ffw::Vec4") {
    REQUIRE(sizeof(ffw::Vec4f) == sizeof(float) * 4);
    REQUIRE(sizeof(ffw::Vec4i) == sizeof(int) * 4);
    REQUIRE(sizeof(ffw::Vec4d) == sizeof(double) * 4);
}
