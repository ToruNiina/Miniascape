#define BOOST_TEST_MODULE "test_periodic_boundary"

#ifdef UNITTEST_FRAMEWORK_LIBRARY_EXIST
#include <boost/test/unit_test.hpp>
#else
#define BOOST_TEST_NO_LIB
#include <boost/test/included/unit_test.hpp>
#endif

#include "core/PeriodicBoundary.hpp"
#include "core/NeighborhoodIndex.hpp"

struct Linear{
    constexpr static std::size_t dimension = 1;
    using cell_index_type = std::array<int,1>;
};

struct LinearWorld{
    using cell_ptr = std::size_t;
    std::vector<cell_ptr> cell;
    std::size_t  operator()(const std::array<int, 1>& idx) const {return cell.at(idx[0]);}
    std::size_t& operator()(const std::array<int, 1>& idx)       {return cell.at(idx[0]);}
};

struct Square{
    constexpr static std::size_t dimension = 2;
    using cell_index_type = std::array<int,2>;
};

struct SquareWorld{
    using cell_ptr = std::pair<std::size_t, std::size_t>;
    std::vector<std::vector<cell_ptr>> cell;
    cell_ptr const& operator()(const std::array<int, 2>& idx) const
    {return cell.at(idx[0]).at(idx[1]);}
    cell_ptr &      operator()(const std::array<int, 2>& idx)
    {return cell.at(idx[0]).at(idx[1]);}
};

bool operator==(const std::pair<std::size_t, std::size_t>& lhs,
                const std::pair<std::size_t, std::size_t>& rhs)
{
    return (lhs.first == rhs.first) && (lhs.second == rhs.second);
}

BOOST_AUTO_TEST_CASE(periodic_boundary_access_oneD)
{
    miniascape::PeriodicBoundary<Linear> peri({{0}}, {{3}});
    LinearWorld world;
    world.cell.push_back(0);
    world.cell.push_back(1);
    world.cell.push_back(2);

    BOOST_CHECK(peri.access({{-3}}, world) == 0);
    BOOST_CHECK(peri.access({{-2}}, world) == 1);
    BOOST_CHECK(peri.access({{-1}}, world) == 2);
    BOOST_CHECK(peri.access({{0}}, world) == 0);
    BOOST_CHECK(peri.access({{1}}, world) == 1);
    BOOST_CHECK(peri.access({{2}}, world) == 2);
    BOOST_CHECK(peri.access({{3}}, world) == 0);
    BOOST_CHECK(peri.access({{4}}, world) == 1);
    BOOST_CHECK(peri.access({{5}}, world) == 2);
}

BOOST_AUTO_TEST_CASE(periodic_boundary_access_twoD)
{
    miniascape::PeriodicBoundary<Square> peri({{0,0}}, {{3,3}});
    SquareWorld world;
    world.cell.push_back({{0,0},{0,1},{0,2}});
    world.cell.push_back({{1,0},{1,1},{1,2}});
    world.cell.push_back({{2,0},{2,1},{2,2}});

    BOOST_CHECK(peri.access({{0,0}}, world) == std::make_pair(0,0));
    BOOST_CHECK(peri.access({{0,1}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{0,2}}, world) == std::make_pair(0,2));
    BOOST_CHECK(peri.access({{1,0}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{1,1}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{1,2}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{2,0}}, world) == std::make_pair(2,0));
    BOOST_CHECK(peri.access({{2,1}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{2,2}}, world) == std::make_pair(2,2));

    // case x < 0
    BOOST_CHECK(peri.access({{-1,0}}, world) == std::make_pair(2,0));
    BOOST_CHECK(peri.access({{-1,1}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{-1,2}}, world) == std::make_pair(2,2));
    BOOST_CHECK(peri.access({{-2,0}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{-2,1}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{-2,2}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{-3,0}}, world) == std::make_pair(0,0));
    BOOST_CHECK(peri.access({{-3,1}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{-3,2}}, world) == std::make_pair(0,2));
 
    // case 3 <= x
    BOOST_CHECK(peri.access({{3,0}}, world) == std::make_pair(0,0));
    BOOST_CHECK(peri.access({{3,1}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{3,2}}, world) == std::make_pair(0,2));
    BOOST_CHECK(peri.access({{4,0}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{4,1}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{4,2}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{5,0}}, world) == std::make_pair(2,0));
    BOOST_CHECK(peri.access({{5,1}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{5,2}}, world) == std::make_pair(2,2));

    // case y < 0
    BOOST_CHECK(peri.access({{0,-1}}, world) == std::make_pair(0,2));
    BOOST_CHECK(peri.access({{1,-1}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{2,-1}}, world) == std::make_pair(2,2));
    BOOST_CHECK(peri.access({{0,-2}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{1,-2}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{2,-2}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{0,-3}}, world) == std::make_pair(0,0));
    BOOST_CHECK(peri.access({{1,-3}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{2,-3}}, world) == std::make_pair(2,0));

    // case 3 <= y
    BOOST_CHECK(peri.access({{0,3}}, world) == std::make_pair(0,0));
    BOOST_CHECK(peri.access({{1,3}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{2,3}}, world) == std::make_pair(2,0));
    BOOST_CHECK(peri.access({{0,4}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{1,4}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{2,4}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{0,5}}, world) == std::make_pair(0,2));
    BOOST_CHECK(peri.access({{1,5}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{2,5}}, world) == std::make_pair(2,2));

    // case x < 0, y < 0
    BOOST_CHECK(peri.access({{-1,-1}}, world) == std::make_pair(2,2));
    BOOST_CHECK(peri.access({{-1,-2}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{-1,-3}}, world) == std::make_pair(2,0));
    BOOST_CHECK(peri.access({{-2,-1}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{-2,-2}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{-2,-3}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{-3,-1}}, world) == std::make_pair(0,2));
    BOOST_CHECK(peri.access({{-3,-2}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{-3,-3}}, world) == std::make_pair(0,0));

    // case 3 <= x, y < 0
    BOOST_CHECK(peri.access({{3,-1}}, world) == std::make_pair(0,2));
    BOOST_CHECK(peri.access({{3,-2}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{3,-3}}, world) == std::make_pair(0,0));
    BOOST_CHECK(peri.access({{4,-1}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{4,-2}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{4,-3}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{5,-1}}, world) == std::make_pair(2,2));
    BOOST_CHECK(peri.access({{5,-2}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{5,-3}}, world) == std::make_pair(2,0));

    // case x < 0, 3 <= y
    BOOST_CHECK(peri.access({{-1,3}}, world) == std::make_pair(2,0));
    BOOST_CHECK(peri.access({{-1,4}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{-1,5}}, world) == std::make_pair(2,2));
    BOOST_CHECK(peri.access({{-2,3}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{-2,4}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{-2,5}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{-3,3}}, world) == std::make_pair(0,0));
    BOOST_CHECK(peri.access({{-3,4}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{-3,5}}, world) == std::make_pair(0,2));

    // case 3 <=, 3 <= y
    BOOST_CHECK(peri.access({{3,3}}, world) == std::make_pair(0,0));
    BOOST_CHECK(peri.access({{3,4}}, world) == std::make_pair(0,1));
    BOOST_CHECK(peri.access({{3,5}}, world) == std::make_pair(0,2));
    BOOST_CHECK(peri.access({{4,3}}, world) == std::make_pair(1,0));
    BOOST_CHECK(peri.access({{4,4}}, world) == std::make_pair(1,1));
    BOOST_CHECK(peri.access({{4,5}}, world) == std::make_pair(1,2));
    BOOST_CHECK(peri.access({{5,3}}, world) == std::make_pair(2,0));
    BOOST_CHECK(peri.access({{5,4}}, world) == std::make_pair(2,1));
    BOOST_CHECK(peri.access({{5,5}}, world) == std::make_pair(2,2));
}
