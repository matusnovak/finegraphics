#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <ffw/graphics/mat3.h>

TEST_CASE("init mat3", "ffw::Mat3x3") {
    ffw::Mat3x3f m;
    CHECK(m[0] == Approx(1.0f));
    CHECK(m[1] == Approx(0.0f));
    CHECK(m[2] == Approx(0.0f));

    CHECK(m[3] == Approx(0.0f));
    CHECK(m[4] == Approx(1.0f));
    CHECK(m[5] == Approx(0.0f));

    CHECK(m[6] == Approx(0.0f));
    CHECK(m[7] == Approx(0.0f));
    CHECK(m[8] == Approx(1.0f));
}

TEST_CASE("init mat3 identity", "ffw::Mat3x3") {
    ffw::Mat3x3f m(2.0f);
    CHECK(m[0] == Approx(2.0f));
    CHECK(m[1] == Approx(0.0f));
    CHECK(m[2] == Approx(0.0f));

    CHECK(m[3] == Approx(0.0f));
    CHECK(m[4] == Approx(2.0f));
    CHECK(m[5] == Approx(0.0f));

    CHECK(m[6] == Approx(0.0f));
    CHECK(m[7] == Approx(0.0f));
    CHECK(m[8] == Approx(2.0f));
}

TEST_CASE("init mat3 swap", "ffw::Mat3x3") {
    ffw::Mat3x3f other(2.0f);
    ffw::Mat3x3f m(1.0f);

    std::swap(other, m);

    CHECK(m[0] == Approx(2.0f));
    CHECK(m[1] == Approx(0.0f));
    CHECK(m[2] == Approx(0.0f));

    CHECK(m[3] == Approx(0.0f));
    CHECK(m[4] == Approx(2.0f));
    CHECK(m[5] == Approx(0.0f));

    CHECK(m[6] == Approx(0.0f));
    CHECK(m[7] == Approx(0.0f));
    CHECK(m[8] == Approx(2.0f));
}

TEST_CASE("init mat3 transpose", "ffw::Mat3x3") {
    ffw::Mat3x3f m(1.0f);

    m[0] = 0.0f;
    m[1] = 1.0f;
    m[2] = 2.0f;

    m[3] = 3.0f;
    m[4] = 4.0f;
    m[5] = 5.0f;

    m[6] = 6.0f;
    m[7] = 7.0f;
    m[8] = 8.0f;

    m.transpose();

    CHECK(m[0] == Approx(0.0f));
    CHECK(m[1] == Approx(3.0f));
    CHECK(m[2] == Approx(6.0f));

    CHECK(m[3] == Approx(1.0f));
    CHECK(m[4] == Approx(4.0f));
    CHECK(m[5] == Approx(7.0f));

    CHECK(m[6] == Approx(2.0f));
    CHECK(m[7] == Approx(5.0f));
    CHECK(m[8] == Approx(8.0f));
}

TEST_CASE("init mat3 copy", "ffw::Mat3x3") {
    ffw::Mat3x3f m;
    ffw::Mat3x3f o = ffw::Mat3x3f(2.0f);

    m[0] = 0.0f;
    m[1] = 1.0f;
    m[2] = 2.0f;

    m[3] = 3.0f;
    m[4] = 4.0f;
    m[5] = 5.0f;

    m[6] = 6.0f;
    m[7] = 7.0f;
    m[8] = 8.0f;

    m.transpose();

    o = m;

    CHECK(o[0] == Approx(0.0f));
    CHECK(o[1] == Approx(3.0f));
    CHECK(o[2] == Approx(6.0f));

    CHECK(o[3] == Approx(1.0f));
    CHECK(o[4] == Approx(4.0f));
    CHECK(o[5] == Approx(7.0f));

    CHECK(o[6] == Approx(2.0f));
    CHECK(o[7] == Approx(5.0f));
    CHECK(o[8] == Approx(8.0f));
}

TEST_CASE("init mat3 addition", "ffw::Mat3x3") {
    ffw::Mat3x3f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;

    a[3] = 4.0f;
    a[4] = 5.0f;
    a[5] = 6.0f;

    a[6] = 7.0f;
    a[7] = 8.0f;
    a[8] = 9.0f;

    b[0] = 10.0f;
    b[1] = 11.0f;
    b[2] = 12.0f;

    b[3] = 13.0f;
    b[4] = 14.0f;
    b[5] = 15.0f;

    b[6] = 16.0f;
    b[7] = 17.0f;
    b[8] = 18.0f;

    const auto m = a + b;

    CHECK(m[0] == Approx(11.0f));
    CHECK(m[1] == Approx(13.0f));
    CHECK(m[2] == Approx(15.0f));

    CHECK(m[3] == Approx(17.0f));
    CHECK(m[4] == Approx(19.0f));
    CHECK(m[5] == Approx(21.0f));

    CHECK(m[6] == Approx(23.0f));
    CHECK(m[7] == Approx(25.0f));
    CHECK(m[8] == Approx(27.0f));
}

TEST_CASE("init mat3 addition equals", "ffw::Mat3x3") {
    ffw::Mat3x3f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;

    a[3] = 4.0f;
    a[4] = 5.0f;
    a[5] = 6.0f;

    a[6] = 7.0f;
    a[7] = 8.0f;
    a[8] = 9.0f;

    b[0] = 10.0f;
    b[1] = 11.0f;
    b[2] = 12.0f;

    b[3] = 13.0f;
    b[4] = 14.0f;
    b[5] = 15.0f;

    b[6] = 16.0f;
    b[7] = 17.0f;
    b[8] = 18.0f;

    a += b;

    CHECK(a[0] == Approx(11.0f));
    CHECK(a[1] == Approx(13.0f));
    CHECK(a[2] == Approx(15.0f));

    CHECK(a[3] == Approx(17.0f));
    CHECK(a[4] == Approx(19.0f));
    CHECK(a[5] == Approx(21.0f));

    CHECK(a[6] == Approx(23.0f));
    CHECK(a[7] == Approx(25.0f));
    CHECK(a[8] == Approx(27.0f));
}


TEST_CASE("init mat3 substraction", "ffw::Mat3x3") {
    ffw::Mat3x3f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;

    a[3] = 4.0f;
    a[4] = 5.0f;
    a[5] = 6.0f;

    a[6] = 7.0f;
    a[7] = 8.0f;
    a[8] = 9.0f;

    b[0] = 10.0f;
    b[1] = 11.0f;
    b[2] = 12.0f;

    b[3] = 13.0f;
    b[4] = 14.0f;
    b[5] = 15.0f;

    b[6] = 16.0f;
    b[7] = 17.0f;
    b[8] = 18.0f;

    const auto m = a - b;

    CHECK(m[0] == Approx(-9.0f));
    CHECK(m[1] == Approx(-9.0f));
    CHECK(m[2] == Approx(-9.0f));

    CHECK(m[3] == Approx(-9.0f));
    CHECK(m[4] == Approx(-9.0f));
    CHECK(m[5] == Approx(-9.0f));

    CHECK(m[6] == Approx(-9.0f));
    CHECK(m[7] == Approx(-9.0f));
    CHECK(m[8] == Approx(-9.0f));
}

TEST_CASE("init mat3 substraction equals", "ffw::Mat3x3") {
    ffw::Mat3x3f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;

    a[3] = 4.0f;
    a[4] = 5.0f;
    a[5] = 6.0f;

    a[6] = 7.0f;
    a[7] = 8.0f;
    a[8] = 9.0f;

    b[0] = 10.0f;
    b[1] = 11.0f;
    b[2] = 12.0f;

    b[3] = 13.0f;
    b[4] = 14.0f;
    b[5] = 15.0f;

    b[6] = 16.0f;
    b[7] = 17.0f;
    b[8] = 18.0f;

    a -= b;

    CHECK(a[0] == Approx(-9.0f));
    CHECK(a[1] == Approx(-9.0f));
    CHECK(a[2] == Approx(-9.0f));

    CHECK(a[3] == Approx(-9.0f));
    CHECK(a[4] == Approx(-9.0f));
    CHECK(a[5] == Approx(-9.0f));

    CHECK(a[6] == Approx(-9.0f));
    CHECK(a[7] == Approx(-9.0f));
    CHECK(a[8] == Approx(-9.0f));
}

TEST_CASE("init mat3 multiply", "ffw::Mat3x3") {
    ffw::Mat3x3f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;

    a[3] = 4.0f;
    a[4] = 5.0f;
    a[5] = 6.0f;

    a[6] = 7.0f;
    a[7] = 8.0f;
    a[8] = 9.0f;

    b[0] = 10.0f;
    b[1] = 11.0f;
    b[2] = 12.0f;

    b[3] = 13.0f;
    b[4] = 14.0f;
    b[5] = 15.0f;

    b[6] = 16.0f;
    b[7] = 17.0f;
    b[8] = 18.0f;

    const auto m = a * b;

    CHECK(m[0] == Approx(138.0f));
    CHECK(m[1] == Approx(171.0f));
    CHECK(m[2] == Approx(204.0f));

    CHECK(m[3] == Approx(174.0f));
    CHECK(m[4] == Approx(216.0f));
    CHECK(m[5] == Approx(258.0f));

    CHECK(m[6] == Approx(210.0f));
    CHECK(m[7] == Approx(261.0f));
    CHECK(m[8] == Approx(312.0f));
}

TEST_CASE("init mat3 multiply equals", "ffw::Mat3x3") {
    ffw::Mat3x3f a, b;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;

    a[3] = 4.0f;
    a[4] = 5.0f;
    a[5] = 6.0f;

    a[6] = 7.0f;
    a[7] = 8.0f;
    a[8] = 9.0f;

    b[0] = 10.0f;
    b[1] = 11.0f;
    b[2] = 12.0f;

    b[3] = 13.0f;
    b[4] = 14.0f;
    b[5] = 15.0f;

    b[6] = 16.0f;
    b[7] = 17.0f;
    b[8] = 18.0f;

    a *= b;

    CHECK(a[0] == Approx(138.0f));
    CHECK(a[1] == Approx(171.0f));
    CHECK(a[2] == Approx(204.0f));

    CHECK(a[3] == Approx(174.0f));
    CHECK(a[4] == Approx(216.0f));
    CHECK(a[5] == Approx(258.0f));

    CHECK(a[6] == Approx(210.0f));
    CHECK(a[7] == Approx(261.0f));
    CHECK(a[8] == Approx(312.0f));
}

TEST_CASE("init mat3 determinant", "ffw::Mat3x3") {
    ffw::Mat3x3f a;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;

    a[3] = 2.0f;
    a[4] = 5.0f;
    a[5] = 2.0f;

    a[6] = 3.0f;
    a[7] = 2.0f;
    a[8] = 1.0f;

    const auto det = a.determinant();

    CHECK(det == Approx(-24.0f));
}

TEST_CASE("init mat3 inverse", "ffw::Mat3x3") {
    ffw::Mat3x3f a;

    a[0] = 1.0f;
    a[1] = 2.0f;
    a[2] = 3.0f;

    a[3] = 2.0f;
    a[4] = 5.0f;
    a[5] = 2.0f;

    a[6] = 3.0f;
    a[7] = 2.0f;
    a[8] = 1.0f;

    a.inverse();

    CHECK(a[0] == Approx(-1.0f / 24.0f));
    CHECK(a[1] == Approx(-4.0f / 24.0f));
    CHECK(a[2] == Approx(11.0f / 24.0f));

    CHECK(a[3] == Approx(-4.0f / 24.0f));
    CHECK(a[4] == Approx(8.0f / 24.0f));
    CHECK(a[5] == Approx(-4.0f / 24.0f));

    CHECK(a[6] == Approx(11.0f / 24.0f));
    CHECK(a[7] == Approx(-4.0f / 24.0f));
    CHECK(a[8] == Approx(-1.0f / 24.0f));
}

TEST_CASE("init mat3 multiply vec", "ffw::Mat3x3") {
    ffw::Mat3x3f a;

    a[0] = 1.0f;
    a[1] = 4.0f;
    a[2] = 7.0f;

    a[3] = 2.0f;
    a[4] = 5.0f;
    a[5] = 8.0f;

    a[6] = 3.0f;
    a[7] = 6.0f;
    a[8] = 9.0f;

    ffw::Vec3f v(2.0f, 1.0f, 3.0f);

    ffw::Vec3f res = a * v;

    CHECK(res.x == Approx(13.0f));
    CHECK(res.y == Approx(31.0f));
    CHECK(res.z == Approx(49.0f));
}

TEST_CASE("init mat3 rotate", "ffw::Mat3x3") {
    ffw::Mat3x3f m(1.0f);

    ffw::Quaternionf q(0.5f, 0.7f, 0.2f, 1.0f);

    m.rotate(q);

    CHECK(m[0] == Approx(0.4044944f));
    CHECK(m[1] == Approx(0.6179775f));
    CHECK(m[2] == Approx(-0.6741573f));

    CHECK(m[3] == Approx(0.1685393f));
    CHECK(m[4] == Approx(0.6741573f));
    CHECK(m[5] == Approx(0.7191011f));

    CHECK(m[6] == Approx(0.8988764f));
    CHECK(m[7] == Approx(-0.4044944f));
    CHECK(m[8] == Approx(0.1685393f));
}