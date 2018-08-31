#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <ffw/graphics/vec3.h>

TEST_CASE("Testing Vec3", "ffw::Vec3") {
    {
        ffw::Vec3i vec;
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
        REQUIRE(vec.z == 0);
    }

    {
        ffw::Vec3i vec(42);
        REQUIRE(vec.x == 42);
        REQUIRE(vec.y == 42);
        REQUIRE(vec.z == 42);
    }

    {
        ffw::Vec3i vec(10, 20, 30);
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
    }

    {
        ffw::Vec3i vec({ 10, 20, 30 });
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
    }

    {
        ffw::Vec3i vec({ 10, 20, 30, 40 });
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
        REQUIRE(vec.z == 0);
    }

    {
        ffw::Vec3i vec;
        vec.set(42);
        REQUIRE(vec.x == 42);
        REQUIRE(vec.y == 42);
        REQUIRE(vec.z == 42);
    }

    {
        ffw::Vec3i vec;
        vec.set(10, 20, 30);
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
    }

    {
        ffw::Vec3i vec;
        vec.set({ 10, 20, 30 });
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
    }

    {
        ffw::Vec3i vec;
        vec.set({ 10, 20, 30, 40 });
        REQUIRE(vec.x == 0);
        REQUIRE(vec.y == 0);
        REQUIRE(vec.z == 0);
    }

    {
        ffw::Vec3i vec = { 10, 20, 30 };
        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == 20);
        REQUIRE(vec.z == 30);
    }

    {
        ffw::Vec3i a(1, 5, 10);
        ffw::Vec3i b(5, 10, 2);
        ffw::Vec3i c = a + b;
        REQUIRE(c.x == 6);
        REQUIRE(c.y == 15);
        REQUIRE(c.z == 12);
        REQUIRE(a + b == c);
        b += a;
        REQUIRE(b == c);
    }

    {
        ffw::Vec3i a(5, 10, 20);
        ffw::Vec3i b(1, 5, 5);
        ffw::Vec3i c = a - b;
        REQUIRE(c.x == 4);
        REQUIRE(c.y == 5);
        REQUIRE(c.z == 15);
        REQUIRE(a - b == c);
        a -= b;
        REQUIRE(a == c);
    }

    {
        ffw::Vec3i a(5, 10, 8);
        ffw::Vec3i b(1, 5, 2);
        ffw::Vec3i c = a * b;
        REQUIRE(c.x == 5);
        REQUIRE(c.y == 50);
        REQUIRE(c.z == 16);
        REQUIRE(a * b == c);
        b *= a;
        REQUIRE(b == c);
    }

    {
        ffw::Vec3i a(6, 12, 25);
        ffw::Vec3i b(2, 3, 5);
        ffw::Vec3i c = a / b;
        REQUIRE(c.x == 3);
        REQUIRE(c.y == 4);
        REQUIRE(c.z == 5);
        REQUIRE(a / b == c);
        a /= b;
        REQUIRE(a == c);
    }

    REQUIRE(ffw::Vec3i(1, 2, 3) == ffw::Vec3i(1, 2, 3));
    REQUIRE(ffw::Vec3i(1, 2, 3) != ffw::Vec3i(2, 2, 2));
    REQUIRE(ffw::Vec3i(1, 2, 3) != ffw::Vec3i(1, 1, 1));
    REQUIRE(ffw::Vec3i(1, 2, 3) != ffw::Vec3i(3, 3, 3));
    REQUIRE(ffw::Vec3f(1.0f, 2.0f, 3.0f) == ffw::Vec3f(1.0f, 2.0f, 3.0f));
    REQUIRE(ffw::Vec3f(1.0f, 2.0f, 3.0f) != ffw::Vec3f(1.0f, 2.001f, 3.0f));

    {
        ffw::Vec3i a(6, 12, 16);
        ffw::Vec3i b = -a;
        REQUIRE(b.x == -6);
        REQUIRE(b.y == -12);
        REQUIRE(b.z == -16);
        b = -b;
        REQUIRE(b == a);
    }

    {
        ffw::Vec3i vec(5, 10, 15);
        vec.scale(3);
        REQUIRE(vec.x == 15);
        REQUIRE(vec.y == 30);
        REQUIRE(vec.z == 45);
    }

    {
        ffw::Vec3f vec(3.0f, 4.0f, 12.0f);
        vec.normalize();
        REQUIRE(std::fabs(vec.x - 3.0f / 13.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 4.0f / 13.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 12.0f / 13.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(1.0f, 0.0f, 0.0f);
        vec.rotateZ(90.0f);
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 0.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(1.0f, 0.0f, 0.0f);
        vec.rotateZ(30.0f);
        REQUIRE(std::fabs(vec.x - 0.866025f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 0.5f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 0.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(1.0f, 0.0f, 0.0f);
        vec.rotateZRad(90.0f * DEG_TO_RAD);
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 0.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(1.0f, 0.0f, 0.0f);
        vec.rotateZRad(30.0f * DEG_TO_RAD);
        REQUIRE(std::fabs(vec.x - 0.866025f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 0.5f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 0.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateY(90.0f);
        REQUIRE(std::fabs(vec.x - 1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 0.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateY(30.0f);
        REQUIRE(std::fabs(vec.x - 0.5f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 0.866025f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateYRad(90.0f * DEG_TO_RAD);
        REQUIRE(std::fabs(vec.x - 1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 0.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateYRad(30.0f * DEG_TO_RAD);
        REQUIRE(std::fabs(vec.x - 0.5f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 0.866025f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateX(90.0f);
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - -1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 1.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateX(30.0f);
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 0.366025f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 1.366025f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateXRad(90.0f * DEG_TO_RAD);
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - -1.0f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 1.0f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateXRad(30.0f * DEG_TO_RAD);
        REQUIRE(std::fabs(vec.x - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 0.366025f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 1.366025f) < 0.01f);
    }

    {
        ffw::Vec3f vec(0.0f, 1.0f, 1.0f);
        vec.rotateByAxis(30.0f, ffw::Vec3f(0.2f, 0.8f, 0.6f));
        REQUIRE(std::fabs(vec.x - 0.134128f) < 0.01f);
        REQUIRE(std::fabs(vec.y - 0.912248f) < 0.01f);
        REQUIRE(std::fabs(vec.z - 1.072294f) < 0.01f);
    }

    {
        ffw::Vec3f vec(1.0f, 1.0f, 1.0f);
        REQUIRE(std::fabs(vec.length() - sqrt(3.0)) < 0.01);
    }

    {
        ffw::Vec3i vec(1, 1, 1);
        REQUIRE(std::fabs(vec.length() - sqrt(3.0)) < 0.01);
    }

    {
        ffw::Vec3f vec(1.0f, 1.0f, 1.0f);
        REQUIRE(vec.lengthSqrd() == 3.0f);
    }

    {
        ffw::Vec3i vec(1, 1, 1);
        REQUIRE(vec.lengthSqrd() == 3);
    }
}

TEST_CASE("Testing dot", "ffw::Vec3") {
    // dot product
    REQUIRE(ffw::dot(
        ffw::Vec3d(0.0, 1.5, 0.0),
        ffw::Vec3d(1.0, 1.0, 0.0))
        == Approx(3.0 / 2.0));
}

TEST_CASE("Testing cross", "ffw::Vec3") {
    // cross product
    REQUIRE(ffw::cross(
        ffw::Vec3f(2.0f, 3.0f, 4.0f),
        ffw::Vec3f(-2.0f, 0.0f, 7.0f))
        == ffw::Vec3f(21.0f, -22.0f, 6.0f));

    REQUIRE(ffw::cross(
        ffw::Vec3f(1.0f, 0.0f, 0.0f),
        ffw::Vec3f(0.0f, 1.0f, 0.0f))
        == ffw::Vec3f(0.0f, 0.0f, 1.0f));
}

TEST_CASE("Testing distance", "ffw::Vec3") {
    // distance
    REQUIRE(ffw::distance(
        ffw::Vec3f(7.0f, 4.0f, -9.0f),
        ffw::Vec3f(-2.0f, 5.0f, 1.0f))
        == Approx(13.490738f));
}

TEST_CASE("Testing middle", "ffw::Vec3") {
    // middle
    REQUIRE(ffw::middle(
        ffw::Vec3f(3.0f, 0.0f, -2.0f),
        ffw::Vec3f(-3.0f, 1.0f, -5.0f))
        == ffw::Vec3f(0.0f, 0.5f, -3.5f));
}

TEST_CASE("Testing normalize", "ffw::Vec3") {
    // normalize
    auto v = ffw::Vec3f(-2.0f, 7.0f, 3.0f).normalize();
    REQUIRE(v == ffw::normalize(ffw::Vec3f(-2.0f, 7.0f, 3.0f)));
}

TEST_CASE("Testing angle", "ffw::Vec3") {
    // angle
    REQUIRE(ffw::angle(
        ffw::Vec3f(-1.0f, 2.0f, 3.0f),
        ffw::Vec3f(4.0f, 5.0f, 6.0f))
        == Approx(43.03190f));

    REQUIRE(ffw::angleRad(
        ffw::Vec3f(-1.0f, 2.0f, 3.0f),
        ffw::Vec3f(4.0f, 5.0f, 6.0f))
        == Approx(43.03190f * DEG_TO_RAD));
}

TEST_CASE("sizeof", "ffw::Vec3") {
    REQUIRE(sizeof(ffw::Vec3f) == sizeof(float) * 3);
    REQUIRE(sizeof(ffw::Vec3i) == sizeof(int) * 3);
    REQUIRE(sizeof(ffw::Vec3d) == sizeof(double) * 3);
}
