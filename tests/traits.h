#include <type_traits>

#define SECTION_TEST_MOVEABLE(T) \
    SECTION("is moveable") { \
        REQUIRE(std::is_move_constructible<T>::value); \
        REQUIRE(std::is_nothrow_move_constructible<T>::value); \
        REQUIRE(std::is_move_assignable<T>::value); \
    }

#define SECTION_TEST_NOT_COPYABLE(T) \
    SECTION("is NOT copyable") { \
        REQUIRE(std::is_copy_constructible<T>::value == false); \
        REQUIRE(std::is_nothrow_copy_constructible<T>::value == false); \
        REQUIRE(std::is_copy_assignable<T>::value == false); \
    }