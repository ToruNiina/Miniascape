#define BOOST_TEST_MODULE "test_make_array"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "util/make_array.hpp"

using namespace miniascape;

BOOST_AUTO_TEST_CASE(test_make_array)
{
    int a1(0), a2(1), a3(2);
    auto a = make_array(a1, a2, a3);
    static_assert(std::is_same<std::array<int, 3>, decltype(a)>::value,
                  "check typeof return value failed");

    BOOST_CHECK_EQUAL(a[0], a1);
    BOOST_CHECK_EQUAL(a[1], a2);
    BOOST_CHECK_EQUAL(a[2], a3);
}

BOOST_AUTO_TEST_CASE(test_make_array_type)
{
    int a1(0), a3(2);
    short a2(1);
    auto a = make_array_type<int>(a1, a2, a3);
    static_assert(std::is_same<std::array<int, 3>, decltype(a)>::value,
                  "check typeof return value failed");

    BOOST_CHECK_EQUAL(a[0], 0);
    BOOST_CHECK_EQUAL(a[1], 1);
    BOOST_CHECK_EQUAL(a[2], 2);
}
