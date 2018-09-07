#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/mat3.h>
#include <ffw/graphics/mat4.h>

TEST_CASE("init mat4", "ffw::Mat4x4") {
    ffw::Mat4x4f m;
    CHECK(m[0] == Approx(1.0f));
    CHECK(m[1] == Approx(0.0f));
    CHECK(m[2] == Approx(0.0f));
    CHECK(m[3] == Approx(0.0f));

    CHECK(m[4] == Approx(0.0f));
    CHECK(m[5] == Approx(1.0f));
    CHECK(m[6] == Approx(0.0f));
    CHECK(m[7] == Approx(0.0f));

    CHECK(m[8] == Approx(0.0f));
    CHECK(m[9] == Approx(0.0f));
    CHECK(m[10] == Approx(1.0f));
    CHECK(m[11] == Approx(0.0f));

    CHECK(m[12] == Approx(0.0f));
    CHECK(m[13] == Approx(0.0f));
    CHECK(m[14] == Approx(0.0f));
    CHECK(m[15] == Approx(1.0f));
}

TEST_CASE("init mat4 identity", "ffw::Mat4x4") {
    ffw::Mat4x4f m(2.0f);
    CHECK(m[0] == Approx(2.0f));
    CHECK(m[1] == Approx(0.0f));
    CHECK(m[2] == Approx(0.0f));
    CHECK(m[3] == Approx(0.0f));

    CHECK(m[4] == Approx(0.0f));
    CHECK(m[5] == Approx(2.0f));
    CHECK(m[6] == Approx(0.0f));
    CHECK(m[7] == Approx(0.0f));

    CHECK(m[8] == Approx(0.0f));
    CHECK(m[9] == Approx(0.0f));
    CHECK(m[10] == Approx(2.0f));
    CHECK(m[11] == Approx(0.0f));

    CHECK(m[12] == Approx(0.0f));
    CHECK(m[13] == Approx(0.0f));
    CHECK(m[14] == Approx(0.0f));
    CHECK(m[15] == Approx(2.0f));
}

TEST_CASE("init mat4 swap", "ffw::Mat4x4") {
    ffw::Mat4x4f other(2.0f);
    ffw::Mat4x4f m(1.0f);

    std::swap(other, m);

    CHECK(m[0] == Approx(2.0f));
    CHECK(m[1] == Approx(0.0f));
    CHECK(m[2] == Approx(0.0f));
    CHECK(m[3] == Approx(0.0f));

    CHECK(m[4] == Approx(0.0f));
    CHECK(m[5] == Approx(2.0f));
    CHECK(m[6] == Approx(0.0f));
    CHECK(m[7] == Approx(0.0f));

    CHECK(m[8] == Approx(0.0f));
    CHECK(m[9] == Approx(0.0f));
    CHECK(m[10] == Approx(2.0f));
    CHECK(m[11] == Approx(0.0f));

    CHECK(m[12] == Approx(0.0f));
    CHECK(m[13] == Approx(0.0f));
    CHECK(m[14] == Approx(0.0f));
    CHECK(m[15] == Approx(2.0f));
}

TEST_CASE("init mat4 transpose", "ffw::Mat4x4") {
    ffw::Mat4x4f m(1.0f);

    m[0] = 0.0f;
    m[1] = 1.0f;
    m[2] = 2.0f;
    m[3] = 3.0f;

    m[4] = 4.0f;
    m[5] = 5.0f;
    m[6] = 6.0f;
    m[7] = 7.0f;

    m[8] = 8.0f;
    m[9] = 9.0f;
    m[10] = 10.0f;
    m[11] = 11.0f;

    m[12] = 12.0f;
    m[13] = 13.0f;
    m[14] = 14.0f;
    m[15] = 15.0f;

    m.transpose();

    CHECK(m[0] == Approx(0.0f));
    CHECK(m[1] == Approx(4.0f));
    CHECK(m[2] == Approx(8.0f));
    CHECK(m[3] == Approx(12.0f));

    CHECK(m[4] == Approx(1.0f));
    CHECK(m[5] == Approx(5.0f));
    CHECK(m[6] == Approx(9.0f));
    CHECK(m[7] == Approx(13.0f));

    CHECK(m[8] == Approx(2.0f));
    CHECK(m[9] == Approx(6.0f));
    CHECK(m[10] == Approx(10.0f));
    CHECK(m[11] == Approx(14.0f));

    CHECK(m[12] == Approx(3.0f));
    CHECK(m[13] == Approx(7.0f));
    CHECK(m[14] == Approx(11.0f));
    CHECK(m[15] == Approx(15.0f));
}

TEST_CASE("init mat4 copy", "ffw::Mat4x4") {
    ffw::Mat4x4f m;
    ffw::Mat4x4f o = ffw::Mat4x4f(2.0f);

    m[0] = 0.0f;
    m[1] = 1.0f;
    m[2] = 2.0f;
    m[3] = 3.0f;

    m[4] = 4.0f;
    m[5] = 5.0f;
    m[6] = 6.0f;
    m[7] = 7.0f;

    m[8] = 8.0f;
    m[9] = 9.0f;
    m[10] = 10.0f;
    m[11] = 11.0f;

    m[12] = 12.0f;
    m[13] = 13.0f;
    m[14] = 14.0f;
    m[15] = 15.0f;

    m.transpose();

    o = m;

    CHECK(o[0] == Approx(0.0f));
    CHECK(o[1] == Approx(4.0f));
    CHECK(o[2] == Approx(8.0f));
    CHECK(o[3] == Approx(12.0f));

    CHECK(o[4] == Approx(1.0f));
    CHECK(o[5] == Approx(5.0f));
    CHECK(o[6] == Approx(9.0f));
    CHECK(o[7] == Approx(13.0f));

    CHECK(o[8] == Approx(2.0f));
    CHECK(o[9] == Approx(6.0f));
    CHECK(o[10] == Approx(10.0f));
    CHECK(o[11] == Approx(14.0f));

    CHECK(o[12] == Approx(3.0f));
    CHECK(o[13] == Approx(7.0f));
    CHECK(o[14] == Approx(11.0f));
    CHECK(o[15] == Approx(15.0f));
}

TEST_CASE("init mat4 addition", "ffw::Mat4x4") {
    ffw::Mat4x4f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;
    a[3] = 4.0f;

    a[4] = 5.0f;
    a[5] = 6.0f;
    a[6] = 7.0f;
    a[7] = 8.0f;

    a[8] = 9.0f;
    a[9] = 10.0f;
    a[10] = 11.0f;
    a[11] = 12.0f;

    a[12] = 13.0f;
    a[13] = 14.0f;
    a[14] = 15.0f;
    a[15] = 16.0f;

    b[0] = 17.0f;
    b[1] = 18.0f;
    b[2] = 19.0f;
    b[3] = 20.0f;

    b[4] = 21.0f;
    b[5] = 22.0f;
    b[6] = 23.0f;
    b[7] = 24.0f;

    b[8] = 25.0f;
    b[9] = 26.0f;
    b[10] = 27.0f;
    b[11] = 28.0f;

    b[12] = 29.0f;
    b[13] = 30.0f;
    b[14] = 31.0f;
    b[15] = 32.0f;

    const auto m = a + b;

    CHECK(m[0] == Approx(18.0f));
    CHECK(m[1] == Approx(20.0f));
    CHECK(m[2] == Approx(22.0f));
    CHECK(m[3] == Approx(24.0f));

    CHECK(m[4] == Approx(26.0f));
    CHECK(m[5] == Approx(28.0f));
    CHECK(m[6] == Approx(30.0f));
    CHECK(m[7] == Approx(32.0f));

    CHECK(m[8] == Approx(34.0f));
    CHECK(m[9] == Approx(36.0f));
    CHECK(m[10] == Approx(38.0f));
    CHECK(m[11] == Approx(40.0f));

    CHECK(m[12] == Approx(42.0f));
    CHECK(m[13] == Approx(44.0f));
    CHECK(m[14] == Approx(46.0f));
    CHECK(m[15] == Approx(48.0f));
}

TEST_CASE("init mat4 addition equals", "ffw::Mat4x4") {
    ffw::Mat4x4f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;
    a[3] = 4.0f;

    a[4] = 5.0f;
    a[5] = 6.0f;
    a[6] = 7.0f;
    a[7] = 8.0f;

    a[8] = 9.0f;
    a[9] = 10.0f;
    a[10] = 11.0f;
    a[11] = 12.0f;

    a[12] = 13.0f;
    a[13] = 14.0f;
    a[14] = 15.0f;
    a[15] = 16.0f;

    b[0] = 17.0f;
    b[1] = 18.0f;
    b[2] = 19.0f;
    b[3] = 20.0f;

    b[4] = 21.0f;
    b[5] = 22.0f;
    b[6] = 23.0f;
    b[7] = 24.0f;

    b[8] = 25.0f;
    b[9] = 26.0f;
    b[10] = 27.0f;
    b[11] = 28.0f;

    b[12] = 29.0f;
    b[13] = 30.0f;
    b[14] = 31.0f;
    b[15] = 32.0f;

    a += b;

    CHECK(a[0] == Approx(18.0f));
    CHECK(a[1] == Approx(20.0f));
    CHECK(a[2] == Approx(22.0f));
    CHECK(a[3] == Approx(24.0f));

    CHECK(a[4] == Approx(26.0f));
    CHECK(a[5] == Approx(28.0f));
    CHECK(a[6] == Approx(30.0f));
    CHECK(a[7] == Approx(32.0f));

    CHECK(a[8] == Approx(34.0f));
    CHECK(a[9] == Approx(36.0f));
    CHECK(a[10] == Approx(38.0f));
    CHECK(a[11] == Approx(40.0f));

    CHECK(a[12] == Approx(42.0f));
    CHECK(a[13] == Approx(44.0f));
    CHECK(a[14] == Approx(46.0f));
    CHECK(a[15] == Approx(48.0f));
}


TEST_CASE("init mat4 substraction", "ffw::Mat4x4") {
    ffw::Mat4x4f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;
    a[3] = 4.0f;

    a[4] = 5.0f;
    a[5] = 6.0f;
    a[6] = 7.0f;
    a[7] = 8.0f;

    a[8] = 9.0f;
    a[9] = 10.0f;
    a[10] = 11.0f;
    a[11] = 12.0f;

    a[12] = 13.0f;
    a[13] = 14.0f;
    a[14] = 15.0f;
    a[15] = 16.0f;

    b[0] = 17.0f;
    b[1] = 18.0f;
    b[2] = 19.0f;
    b[3] = 20.0f;

    b[4] = 21.0f;
    b[5] = 22.0f;
    b[6] = 23.0f;
    b[7] = 24.0f;

    b[8] = 25.0f;
    b[9] = 26.0f;
    b[10] = 27.0f;
    b[11] = 28.0f;

    b[12] = 29.0f;
    b[13] = 30.0f;
    b[14] = 31.0f;
    b[15] = 32.0f;

    const auto m = a - b;

    CHECK(m[0] == Approx(-16.0f));
    CHECK(m[1] == Approx(-16.0f));
    CHECK(m[2] == Approx(-16.0f));
    CHECK(m[3] == Approx(-16.0f));

    CHECK(m[4] == Approx(-16.0f));
    CHECK(m[5] == Approx(-16.0f));
    CHECK(m[6] == Approx(-16.0f));
    CHECK(m[7] == Approx(-16.0f));

    CHECK(m[8] == Approx(-16.0f));
    CHECK(m[9] == Approx(-16.0f));
    CHECK(m[10] == Approx(-16.0f));
    CHECK(m[11] == Approx(-16.0f));

    CHECK(m[12] == Approx(-16.0f));
    CHECK(m[13] == Approx(-16.0f));
    CHECK(m[14] == Approx(-16.0f));
    CHECK(m[15] == Approx(-16.0f));
}

TEST_CASE("init mat4 substraction equals", "ffw::Mat4x4") {
    ffw::Mat4x4f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;
    a[3] = 4.0f;

    a[4] = 5.0f;
    a[5] = 6.0f;
    a[6] = 7.0f;
    a[7] = 8.0f;

    a[8] = 9.0f;
    a[9] = 10.0f;
    a[10] = 11.0f;
    a[11] = 12.0f;

    a[12] = 13.0f;
    a[13] = 14.0f;
    a[14] = 15.0f;
    a[15] = 16.0f;

    b[0] = 17.0f;
    b[1] = 18.0f;
    b[2] = 19.0f;
    b[3] = 20.0f;

    b[4] = 21.0f;
    b[5] = 22.0f;
    b[6] = 23.0f;
    b[7] = 24.0f;

    b[8] = 25.0f;
    b[9] = 26.0f;
    b[10] = 27.0f;
    b[11] = 28.0f;

    b[12] = 29.0f;
    b[13] = 30.0f;
    b[14] = 31.0f;
    b[15] = 32.0f;

    a -= b;

    CHECK(a[0] == Approx(-16.0f));
    CHECK(a[1] == Approx(-16.0f));
    CHECK(a[2] == Approx(-16.0f));
    CHECK(a[3] == Approx(-16.0f));

    CHECK(a[4] == Approx(-16.0f));
    CHECK(a[5] == Approx(-16.0f));
    CHECK(a[6] == Approx(-16.0f));
    CHECK(a[7] == Approx(-16.0f));

    CHECK(a[8] == Approx(-16.0f));
    CHECK(a[9] == Approx(-16.0f));
    CHECK(a[10] == Approx(-16.0f));
    CHECK(a[11] == Approx(-16.0f));

    CHECK(a[12] == Approx(-16.0f));
    CHECK(a[13] == Approx(-16.0f));
    CHECK(a[14] == Approx(-16.0f));
    CHECK(a[15] == Approx(-16.0f));
}

TEST_CASE("init mat4 multiply", "ffw::Mat4x4") {
    ffw::Mat4x4f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;
    a[3] = 4.0f;

    a[4] = 5.0f;
    a[5] = 6.0f;
    a[6] = 7.0f;
    a[7] = 8.0f;

    a[8] = 9.0f;
    a[9] = 10.0f;
    a[10] = 11.0f;
    a[11] = 12.0f;

    a[12] = 13.0f;
    a[13] = 14.0f;
    a[14] = 15.0f;
    a[15] = 16.0f;

    b[0] = 17.0f;
    b[1] = 18.0f;
    b[2] = 19.0f;
    b[3] = 20.0f;

    b[4] = 21.0f;
    b[5] = 22.0f;
    b[6] = 23.0f;
    b[7] = 24.0f;

    b[8] = 25.0f;
    b[9] = 26.0f;
    b[10] = 27.0f;
    b[11] = 28.0f;

    b[12] = 29.0f;
    b[13] = 30.0f;
    b[14] = 31.0f;
    b[15] = 32.0f;

    const auto m = a * b;

    CHECK(m[0] == Approx(538.0f));
    CHECK(m[1] == Approx(612.0f));
    CHECK(m[2] == Approx(686.0f));
    CHECK(m[3] == Approx(760.0f));

    CHECK(m[4] == Approx(650.0f));
    CHECK(m[5] == Approx(740.0f));
    CHECK(m[6] == Approx(830.0f));
    CHECK(m[7] == Approx(920.0f));

    CHECK(m[8] == Approx(762.0f));
    CHECK(m[9] == Approx(868.0f));
    CHECK(m[10] == Approx(974.0f));
    CHECK(m[11] == Approx(1080.0f));

    CHECK(m[12] == Approx(874.0f));
    CHECK(m[13] == Approx(996.0f));
    CHECK(m[14] == Approx(1118.0f));
    CHECK(m[15] == Approx(1240.0f));
}

TEST_CASE("init mat4 multiply equals", "ffw::Mat4x4") {
    ffw::Mat4x4f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;
    a[3] = 4.0f;

    a[4] = 5.0f;
    a[5] = 6.0f;
    a[6] = 7.0f;
    a[7] = 8.0f;

    a[8] = 9.0f;
    a[9] = 10.0f;
    a[10] = 11.0f;
    a[11] = 12.0f;

    a[12] = 13.0f;
    a[13] = 14.0f;
    a[14] = 15.0f;
    a[15] = 16.0f;

    b[0] = 17.0f;
    b[1] = 18.0f;
    b[2] = 19.0f;
    b[3] = 20.0f;

    b[4] = 21.0f;
    b[5] = 22.0f;
    b[6] = 23.0f;
    b[7] = 24.0f;

    b[8] = 25.0f;
    b[9] = 26.0f;
    b[10] = 27.0f;
    b[11] = 28.0f;

    b[12] = 29.0f;
    b[13] = 30.0f;
    b[14] = 31.0f;
    b[15] = 32.0f;

    a *= b;

    CHECK(a[0] == Approx(538.0f));
    CHECK(a[1] == Approx(612.0f));
    CHECK(a[2] == Approx(686.0f));
    CHECK(a[3] == Approx(760.0f));

    CHECK(a[4] == Approx(650.0f));
    CHECK(a[5] == Approx(740.0f));
    CHECK(a[6] == Approx(830.0f));
    CHECK(a[7] == Approx(920.0f));

    CHECK(a[8] == Approx(762.0f));
    CHECK(a[9] == Approx(868.0f));
    CHECK(a[10] == Approx(974.0f));
    CHECK(a[11] == Approx(1080.0f));

    CHECK(a[12] == Approx(874.0f));
    CHECK(a[13] == Approx(996.0f));
    CHECK(a[14] == Approx(1118.0f));
    CHECK(a[15] == Approx(1240.0f));
}

TEST_CASE("init mat4 determinant", "ffw::Mat4x4") {
    ffw::Mat4x4f a;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;
    a[3] = 4.0f;

    a[4] = 5.0f;
    a[5] = 6.0f;
    a[6] = 7.0f;
    a[7] = 5.0f;

    a[8] = 5.0f;
    a[9] = 7.0f;
    a[10] = 6.0f;
    a[11] = 5.0f;

    a[12] = 4.0f;
    a[13] = 3.0f;
    a[14] = 2.0f;
    a[15] = 1.0f;

    const auto d = a.determinant();

    CHECK(d == Approx(45.0f));
}

TEST_CASE("init mat4 inverse", "ffw::Mat4x4") {
    ffw::Mat4x4f a;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;
    a[3] = 4.0f;

    a[4] = 3.0f;
    a[5] = 4.0f;
    a[6] = 5.0f;
    a[7] = 3.0f;

    a[8] = 3.0f;
    a[9] = 5.0f;
    a[10] = 4.0f;
    a[11] = 3.0f;

    a[12] = 4.0f;
    a[13] = 3.0f;
    a[14] = 2.0f;
    a[15] = 1.0f;

    a.inverse();

    CHECK(a[0] == Approx(6.0f / 45.0f));
    CHECK(a[1] == Approx(0.0f));
    CHECK(a[2] == Approx(-15.0f / 45.0f));
    CHECK(a[3] == Approx(21.0f / 45.0f));

    CHECK(a[4] == Approx(-9.0f / 45.0f));
    CHECK(a[5] == Approx(-15.0f / 45.0f));
    CHECK(a[6] == Approx(30.0f / 45.0f));
    CHECK(a[7] == Approx(-9.0f / 45.0f));

    CHECK(a[8] == Approx(-9.0f / 45.0f));
    CHECK(a[9] == Approx(30.0f / 45.0f));
    CHECK(a[10] == Approx(-15.0f / 45.0f));
    CHECK(a[11] == Approx(-9.0f / 45.0f));

    CHECK(a[12] == Approx(21.0f / 45.0f));
    CHECK(a[13] == Approx(-15.0f / 45.0f));
    CHECK(a[14] == Approx(0.0f));
    CHECK(a[15] == Approx(6.0f / 45.0f));
}

TEST_CASE("init mat4 multiply vec3", "ffw::Mat4x4") {
    ffw::Mat4x4f a;

    a[0] = 1.0f;
    a[1] = 4.0f;
    a[2] = 7.0f;
    a[3] = 0.0f;

    a[4] = 2.0f;
    a[5] = 5.0f;
    a[6] = 8.0f;
    a[7] = 0.0f;

    a[8] = 3.0f;
    a[9] = 6.0f;
    a[10] = 9.0f;
    a[11] = 0.0f;

    a[12] = 0.0f;
    a[13] = 0.0f;
    a[14] = 0.0f;
    a[15] = 1.0f;

    ffw::Vec3f v(2.0f, 1.0f, 3.0f);

    ffw::Vec3f res = a * v;

    CHECK(res.x == Approx(13.0f));
    CHECK(res.y == Approx(31.0f));
    CHECK(res.z == Approx(49.0f));
}

TEST_CASE("init mat4 multiply vec4", "ffw::Mat4x4") {
    ffw::Mat4x4f a;

    a[0] = 1.0f;
    a[1] = 4.0f;
    a[2] = 7.0f;
    a[3] = 0.0f;

    a[4] = 2.0f;
    a[5] = 5.0f;
    a[6] = 8.0f;
    a[7] = 0.0f;

    a[8] = 3.0f;
    a[9] = 6.0f;
    a[10] = 9.0f;
    a[11] = 0.0f;

    a[12] = 10.0f;
    a[13] = 20.0f;
    a[14] = 30.0f;
    a[15] = 0.5f;

    ffw::Vec4f v(2.0f, 1.0f, 3.0f, 0.5f);

    ffw::Vec4f res = a * v;

    CHECK(res.x == Approx(18.0f));
    CHECK(res.y == Approx(41.0f));
    CHECK(res.z == Approx(64.0f));
    CHECK(res.w == Approx(0.25f));
}

TEST_CASE("init mat4 rotate", "ffw::Mat4x4") {
    ffw::Mat4x4f m(1.0f);

    ffw::Quaternionf q(0.5f, 0.7f, 0.2f, 1.0f);

    m.rotate(q);

    CHECK(m[0] == Approx(0.4044944f));
    CHECK(m[1] == Approx(0.6179775f));
    CHECK(m[2] == Approx(-0.6741573f));
    CHECK(m[3] == Approx(0.0f));

    CHECK(m[4] == Approx(0.1685393f));
    CHECK(m[5] == Approx(0.6741573f));
    CHECK(m[6] == Approx(0.7191011f));
    CHECK(m[7] == Approx(0.0f));

    CHECK(m[8] == Approx(0.8988764f));
    CHECK(m[9] == Approx(-0.4044944f));
    CHECK(m[10] == Approx(0.1685393f));
    CHECK(m[11] == Approx(0.0f));

    CHECK(m[12] == Approx(0.0f));
    CHECK(m[13] == Approx(0.0f));
    CHECK(m[14] == Approx(0.0f));
    CHECK(m[15] == Approx(1.0f));
}