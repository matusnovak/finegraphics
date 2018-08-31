#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <ffw/graphics/vecx.h>

TEST_CASE("Testing variable Vec", "[Vec]") {
    {
        ffw::Vec<int, 4> vec;
        REQUIRE(vec[0] == 0);
        REQUIRE(vec[1] == 0);
        REQUIRE(vec[2] == 0);
        REQUIRE(vec[3] == 0);
    }

    {
        ffw::Vec<int, 4> vec(42);
        REQUIRE(vec[0] == 42);
        REQUIRE(vec[1] == 42);
        REQUIRE(vec[2] == 42);
        REQUIRE(vec[3] == 42);
    }

    {
        ffw::Vec<int, 4> vec({ 10, 20, 30, 40 });
        REQUIRE(vec[0] == 10);
        REQUIRE(vec[1] == 20);
        REQUIRE(vec[2] == 30);
        REQUIRE(vec[3] == 40);
    }

    {
        ffw::Vec<int, 4> vec({ 10, 20, 30, 40, 50 });
        REQUIRE(vec[0] == 0);
        REQUIRE(vec[1] == 0);
        REQUIRE(vec[2] == 0);
        REQUIRE(vec[3] == 0);
    }

    {
        ffw::Vec<int, 4> vec;
        vec.set(42);
        REQUIRE(vec[0] == 42);
        REQUIRE(vec[1] == 42);
        REQUIRE(vec[2] == 42);
        REQUIRE(vec[3] == 42);
    }

    {
        ffw::Vec<int, 4> vec;
        vec.set({ 10, 20, 30, 40 });
        REQUIRE(vec[0] == 10);
        REQUIRE(vec[1] == 20);
        REQUIRE(vec[2] == 30);
        REQUIRE(vec[3] == 40);
    }

    {
        ffw::Vec<int, 4> vec = { 10, 20, 30, 40 };
        REQUIRE(vec[0] == 10);
        REQUIRE(vec[1] == 20);
        REQUIRE(vec[2] == 30);
        REQUIRE(vec[3] == 40);
    }

    {
        ffw::Vec<int, 4> a({ 1, 5, 10, 6 });
        ffw::Vec<int, 4> b({ 5, 10, 2, 2 });
        ffw::Vec<int, 4> c = a + b;
        REQUIRE(c[0] == 6);
        REQUIRE(c[1] == 15);
        REQUIRE(c[2] == 12);
        REQUIRE(c[3] == 8);
        REQUIRE(a + b == c);
        b += a;
        REQUIRE(b == c);
    }

    {
        ffw::Vec<int, 4> a({ 5, 10, 20, 15 });
        ffw::Vec<int, 4> b({ 1, 5, 5, 3 });
        ffw::Vec<int, 4> c = a - b;
        REQUIRE(c[0] == 4);
        REQUIRE(c[1] == 5);
        REQUIRE(c[2] == 15);
        REQUIRE(c[3] == 12);
        REQUIRE(a - b == c);
        a -= b;
        REQUIRE(a == c);
    }

    {
        ffw::Vec<int, 4> a({ 5, 10, 8, 15 });
        ffw::Vec<int, 4> b({ 1, 5, 2, 3 });
        ffw::Vec<int, 4> c = a * b;
        REQUIRE(c[0] == 5);
        REQUIRE(c[1] == 50);
        REQUIRE(c[2] == 16);
        REQUIRE(c[3] == 45);
        REQUIRE(a * b == c);
        b *= a;
        REQUIRE(b == c);
    }

    {
        ffw::Vec<int, 4> a({ 6, 12, 25, 15 });
        ffw::Vec<int, 4> b({ 2, 3, 5, 3 });
        ffw::Vec<int, 4> c = a / b;
        REQUIRE(c[0] == 3);
        REQUIRE(c[1] == 4);
        REQUIRE(c[2] == 5);
        REQUIRE(c[3] == 5);
        REQUIRE(a / b == c);
        a /= b;
        REQUIRE(a == c);
    }


    auto a = ffw::Vec<int, 4>({ 1, 2, 3, 4 }); auto b = ffw::Vec<int, 4>({ 1, 2, 3, 4 });
    REQUIRE(a == b);

    auto c = ffw::Vec<int, 4>({ 1, 2, 3, 4 }); auto d = ffw::Vec<int, 4>({ 2, 2, 2, 4 });
    REQUIRE(c != d);

    auto e = ffw::Vec<int, 4>({ 1, 2, 3, 4 }); auto f = ffw::Vec<int, 4>({ 1, 1, 1, 4 });
    REQUIRE(e != f);

    auto g = ffw::Vec<int, 4>({ 1, 2, 3, 4 }); auto h = ffw::Vec<int, 4>({ 3, 3, 3, 4 });
    REQUIRE(g != h);

    auto i = ffw::Vec<float, 4>({ 1.0f, 2.0f, 3.0f, 4.0f }); auto j = ffw::Vec<float, 4>({ 1.0f, 2.0f, 3.0f, 4.0f });
    REQUIRE(i == j);

    auto k = ffw::Vec<float, 4>({ 1.0f, 2.0f, 3.0f, 4.0f }); auto l = ffw::Vec<float, 4>({ 1.0f, 2.001f, 3.0f, 4.0f });
    REQUIRE(k != l);

    {
        ffw::Vec<int, 4> a({ 6, 12, 16, 15 });
        ffw::Vec<int, 4> b = -a;
        REQUIRE(b[0] == -6);
        REQUIRE(b[1] == -12);
        REQUIRE(b[2] == -16);
        REQUIRE(b[3] == -15);
        b = -b;
        REQUIRE(b == a);
    }

    {
        ffw::Vec<int, 4> vec({ 5, 10, 15, 3 });
        vec.scale(3);
        REQUIRE(vec[0] == 15);
        REQUIRE(vec[1] == 30);
        REQUIRE(vec[2] == 45);
        REQUIRE(vec[3] == 9);
    }

    {
        ffw::Vec<float, 4> vec({ 0.0f, 4.0f, 12.0f, 3.0f });
        vec.normalize();
        REQUIRE(std::fabs(vec[0] - 0.0f) < 0.01f);
        REQUIRE(std::fabs(vec[1] - 4.0f / 13.0f) < 0.01f);
        REQUIRE(std::fabs(vec[2] - 12.0f / 13.0f) < 0.01f);
        REQUIRE(std::fabs(vec[3] - 3.0f / 13.0f) < 0.01f);
    }

    {
        ffw::Vec<float, 4> vec({ 1.0f, 1.0f, 1.0f, 1.0f });
        REQUIRE(vec.lengthSqrd() == Approx(4.0f));
    }

    {
        ffw::Vec<int, 4> vec({ 1, 1, 1, 1 });
        REQUIRE(vec.lengthSqrd() == 4);
    }

    {
        ffw::Vec<float, 4> vec({ 1.0f, 1.0f, 1.0f, 1.0f });
        REQUIRE(std::fabs(vec.length() - sqrt(4.0)) < 0.01);
    }

    {
        ffw::Vec<int, 4> vec({ 1, 1, 1, 1 });
        REQUIRE(std::fabs(vec.length() - sqrt(4.0)) < 0.01);
    }
}
