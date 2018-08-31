#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <ffw/graphics/color.h>

TEST_CASE("Testing Color", "ffw::Color") {
    {
        ffw::Color vec;
        REQUIRE(vec.r == 0);
        REQUIRE(vec.g == 0);
        REQUIRE(vec.b == 0);
        REQUIRE(vec.a == 0);
    }

    {
        ffw::Color vec(42, 42);
        REQUIRE(vec.r == 42);
        REQUIRE(vec.g == 42);
        REQUIRE(vec.b == 42);
        REQUIRE(vec.a == 42);
    }

    {
        ffw::Color vec(10, 20, 30, 40);
        REQUIRE(vec.r == 10);
        REQUIRE(vec.g == 20);
        REQUIRE(vec.b == 30);
        REQUIRE(vec.a == 40);
    }

    {
        ffw::Color vec({ 10, 20, 30, 40 });
        REQUIRE(vec.r == 10);
        REQUIRE(vec.g == 20);
        REQUIRE(vec.b == 30);
        REQUIRE(vec.a == 40);
    }

    {
        ffw::Color vec({ 10, 20, 30, 40, 50 });
        REQUIRE(vec.r == 0);
        REQUIRE(vec.g == 0);
        REQUIRE(vec.b == 0);
        REQUIRE(vec.a == 0);
    }

    {
        ffw::Color vec;
        vec.set(42, 42);
        REQUIRE(vec.r == 42);
        REQUIRE(vec.g == 42);
        REQUIRE(vec.b == 42);
        REQUIRE(vec.a == 42);
    }

    {
        ffw::Color vec;
        vec.set(10, 20, 30, 40);
        REQUIRE(vec.r == 10);
        REQUIRE(vec.g == 20);
        REQUIRE(vec.b == 30);
        REQUIRE(vec.a == 40);
    }

    {
        ffw::Color vec;
        vec.set({ 10, 20, 30, 40 });
        REQUIRE(vec.r == 10);
        REQUIRE(vec.g == 20);
        REQUIRE(vec.b == 30);
        REQUIRE(vec.a == 40);
    }

    {
        ffw::Color vec(5, 5);
        vec.set({ 10, 20, 30, 40, 50 });
        REQUIRE(vec.r == 5);
        REQUIRE(vec.g == 5);
        REQUIRE(vec.b == 5);
        REQUIRE(vec.a == 5);
    }

    {
        ffw::Color vec = { 10, 20, 30, 40 };
        REQUIRE(vec.r == 10);
        REQUIRE(vec.g == 20);
        REQUIRE(vec.b == 30);
        REQUIRE(vec.a == 40);
    }

    {
        ffw::Color a(1, 5, 10, 6);
        ffw::Color b(5, 10, 2, 2);
        ffw::Color c = a + b;
        REQUIRE(c.r == 6);
        REQUIRE(c.g == 15);
        REQUIRE(c.b == 12);
        REQUIRE(c.a == 8);
        REQUIRE(a + b == c);
        b += a;
        REQUIRE(b == c);
    }

    {
        ffw::Color a(5, 10, 20, 15);
        ffw::Color b(1, 5, 5, 3);
        ffw::Color c = a - b;
        REQUIRE(c.r == 4);
        REQUIRE(c.g == 5);
        REQUIRE(c.b == 15);
        REQUIRE(c.a == 12);
        REQUIRE(a - b == c);
        a -= b;
        REQUIRE(a == c);
    }

    {
        ffw::Color a(5, 10, 8, 15);
        ffw::Color b(1, 5, 2, 3);
        ffw::Color c = a * b;
        REQUIRE(c.r == 5);
        REQUIRE(c.g == 50);
        REQUIRE(c.b == 16);
        REQUIRE(c.a == 45);
        REQUIRE(a * b == c);
        b *= a;
        REQUIRE(b == c);
    }

    {
        ffw::Color a(6, 12, 25, 15);
        ffw::Color b(2, 3, 5, 3);
        ffw::Color c = a / b;
        REQUIRE(c.r == 3);
        REQUIRE(c.g == 4);
        REQUIRE(c.b == 5);
        REQUIRE(c.a == 5);
        REQUIRE(a / b == c);
        a /= b;
        REQUIRE(a == c);
    }

    REQUIRE(ffw::Color(1, 2, 3, 4) == ffw::Color(1, 2, 3, 4));
    REQUIRE(ffw::Color(1, 2, 3, 4) != ffw::Color(2, 2, 2, 4));
    REQUIRE(ffw::Color(1, 2, 3, 4) != ffw::Color(1, 1, 1, 4));
    REQUIRE(ffw::Color(1, 2, 3, 4) != ffw::Color(3, 3, 3, 4));
    REQUIRE(ffw::Color(1.0f, 2.0f, 3.0f, 4.0f) == ffw::Color(1.0f, 2.0f, 3.0f, 4.0f));
    REQUIRE(ffw::Color(1.0f, 2.0f, 3.0f, 4.0f) != ffw::Color(1.0f, 2.001f, 3.0f, 4.0f));

    {
        ffw::Color a(6, 12, 16, 15);
        ffw::Color b = -a;
        REQUIRE(b.r == -6);
        REQUIRE(b.g == -12);
        REQUIRE(b.b == -16);
        REQUIRE(b.a == -15);
        b = -b;
        REQUIRE(b == a);
    }

    {
        ffw::Color vec(5, 10, 15, 3);
        vec.scale(3);
        REQUIRE(vec.r == 15);
        REQUIRE(vec.g == 30);
        REQUIRE(vec.b == 45);
        REQUIRE(vec.a == 9);
    }

    {
        ffw::Color vec(0.0f, 4.0f, 12.0f, 3.0f);
        vec.normalize();
        REQUIRE(std::fabs(vec.r - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec.g - 4.0f / 12.6491106407f) < 0.01f);
        REQUIRE(std::fabs(vec.b - 12.0f / 12.6491106407f) < 0.01f);
        REQUIRE(std::fabs(vec.a - 1.0f) < 0.01f);
    }

    {
        ffw::Color vec(1.0f, 1.0f, 1.0f, 1.0f);
        REQUIRE(std::fabs(vec.length() - sqrt(4.0)) < 0.01);
    }

    {
        ffw::Color vec(1, 1, 1, 1);
        REQUIRE(std::fabs(vec.length() - sqrt(4.0)) < 0.01);
    }

    {
        ffw::Color vec(1.0f, 1.0f, 1.0f, 1.0f);
        REQUIRE(vec.lengthSqrd() == 4.0f);
    }

    {
        ffw::Color vec(1, 1, 1, 1);
        REQUIRE(vec.lengthSqrd() == 4);
    }
}

TEST_CASE("Testing normalize", "ffw::Color") {
    // normalize
    auto v = ffw::Color(1.7f, 0.5f, 3.1f, 0.2f).normalize();
    REQUIRE(v == ffw::normalize(ffw::Color(1.7f, 0.5f, 3.1f, 0.2f)));
}
