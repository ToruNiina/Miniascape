#define BOOST_TEST_MODULE "test_zip_iterator"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#define private public
#include "zip_iterator.hpp"
#undef private 

#include <vector>
using namespace miniascape;

BOOST_AUTO_TEST_CASE(zip_iterator_constructable)
{
    std::vector<int>    veci{1, 2, 3, 4};
    std::vector<double> vecf{1.1, 2.2, 3.3, 4.4};
    std::vector<char>   vecc{'a', 'b', 'c', 'd'};

    zip_iterator<std::vector<int>::const_iterator,
                 std::vector<double>::const_iterator,
                 std::vector<char>::const_iterator>
        begin(veci.cbegin(), vecf.cbegin(), vecc.cbegin());

    BOOST_CHECK(std::get<0>(begin.iters_) == veci.cbegin());
    BOOST_CHECK(std::get<1>(begin.iters_) == vecf.cbegin());
    BOOST_CHECK(std::get<2>(begin.iters_) == vecc.cbegin());
}

BOOST_AUTO_TEST_CASE(zip_iterator_make_zip)
{
    std::vector<int>    veci{1, 2, 3, 4};
    std::vector<double> vecf{1.1, 2.2, 3.3, 4.4};
    std::vector<char>   vecc{'a', 'b', 'c', 'd'};

    zip_iterator<std::vector<int>::const_iterator,
                 std::vector<double>::const_iterator,
                 std::vector<char>::const_iterator>
        begin(veci.cbegin(), vecf.cbegin(), vecc.cbegin());
    auto maked = make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin());

    BOOST_CHECK(std::get<0>(begin.iters_) == std::get<0>(maked.iters_));
    BOOST_CHECK(std::get<1>(begin.iters_) == std::get<1>(maked.iters_));
    BOOST_CHECK(std::get<2>(begin.iters_) == std::get<2>(maked.iters_));
}

BOOST_AUTO_TEST_CASE(zip_iterator_equal_operator)
{
    std::vector<int>    veci{1, 2, 3, 4};
    std::vector<double> vecf{1.1, 2.2, 3.3, 4.4};
    std::vector<char>   vecc{'a', 'b', 'c', 'd'};

    zip_iterator<std::vector<int>::const_iterator,
                 std::vector<double>::const_iterator,
                 std::vector<char>::const_iterator>
        begin_(veci.cbegin(), vecf.cbegin(), vecc.cbegin());
    auto begin1 = make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin());
    auto begin2 = make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin());
    auto begin3 = make_zip(veci.cbegin(), vecf.cbegin() + 1, vecc.cbegin());
    auto end   = make_zip(veci.cend(), vecf.cend(), vecc.cend());

    BOOST_CHECK(begin_ == begin1);
    BOOST_CHECK(begin1 == begin2);
    BOOST_CHECK(begin1 != begin3);
    BOOST_CHECK(begin1 != end);
}

BOOST_AUTO_TEST_CASE(zip_iterator_get)
{
    std::vector<int>    veci{1, 2, 3, 4};
    std::vector<double> vecf{1.1, 2.2, 3.3, 4.4};
    std::vector<char>   vecc{'a', 'b', 'c', 'd'};

    auto begin = make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin());

    BOOST_CHECK(*get<0>(begin) == 1);
    BOOST_CHECK(*get<1>(begin) == 1.1);
    BOOST_CHECK(*get<2>(begin) == 'a');

    auto next = make_zip(veci.cbegin() + 1, vecf.cbegin() + 1, vecc.cbegin() + 1);

    BOOST_CHECK(*get<0>(next) == 2);
    BOOST_CHECK(*get<1>(next) == 2.2);
    BOOST_CHECK(*get<2>(next) == 'b');
}

BOOST_AUTO_TEST_CASE(zip_iterator_increment)
{
    std::vector<int>    veci{1, 2, 3, 4};
    std::vector<double> vecf{1.1, 2.2, 3.3, 4.4};
    std::vector<char>   vecc{'a', 'b', 'c', 'd'};

    auto begin1 = make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin());
    auto begin2 = make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin());
    auto next   = make_zip(veci.cbegin() + 1, vecf.cbegin() + 1, vecc.cbegin() + 1);
    auto end_   = make_zip(veci.cend(), vecf.cend(), vecc.cend());

    ++begin1;
    begin2++;
    BOOST_CHECK(begin1 == next);
    BOOST_CHECK(begin2 == next);

    ++begin1;
    ++begin1;
    ++begin1;
    begin2++;
    begin2++;
    begin2++;
    BOOST_CHECK(begin1 == end_);
    BOOST_CHECK(begin2 == end_);
}

BOOST_AUTO_TEST_CASE(zip_iterator_decrement)
{
    std::vector<int>    veci{1, 2, 3, 4};
    std::vector<double> vecf{1.1, 2.2, 3.3, 4.4};
    std::vector<char>   vecc{'a', 'b', 'c', 'd'};

    auto begin_ = make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin());
    auto next1 = make_zip(veci.cbegin() + 1, vecf.cbegin() + 1, vecc.cbegin() + 1);
    auto next2 = make_zip(veci.cbegin() + 1, vecf.cbegin() + 1, vecc.cbegin() + 1);
    auto end1   = make_zip(veci.cend(), vecf.cend(), vecc.cend());
    auto end2   = make_zip(veci.cend(), vecf.cend(), vecc.cend());
    --next1;
    next2--;

    BOOST_CHECK(begin_ == next1);
    BOOST_CHECK(begin_ == next2);

    --end1;
    --end1;
    --end1;
    --end1;

    end2--;
    end2--;
    end2--;
    end2--;
    BOOST_CHECK(begin_ == end1);
    BOOST_CHECK(begin_ == end2);
}

BOOST_AUTO_TEST_CASE(zip_iterator_loop)
{
    std::vector<int>    veci{1, 2, 3, 4};
    std::vector<double> vecf{1.1, 2.2, 3.3, 4.4};
    std::vector<char>   vecc{'a', 'b', 'c', 'd'};

    std::size_t index = 0;
    for(auto zip = make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin());
            zip != make_zip(veci.cbegin(), vecf.cbegin(), vecc.cbegin()); ++zip)
    {
        BOOST_CHECK_EQUAL(*get<0>(zip), veci.at(index));
        BOOST_CHECK_EQUAL(*get<1>(zip), vecf.at(index));
        BOOST_CHECK_EQUAL(*get<2>(zip), vecc.at(index));
        ++index;
    }
    BOOST_CHECK_EQUAL(index, 4);
}
