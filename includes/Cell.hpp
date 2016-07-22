#ifndef MINIASCAPE_CELL
#define MINIASCAPE_CELL
#include <vector>
#include <array>

namespace miniascape
{

constexpr static int DYNAMIC = -1;

template<int I_neighbors, typename T_state>
struct Cell
{
    using state_type = T_state;
    constexpr static int number_of_neighbors = I_neighbors;
    using self_type = Cell<number_of_neighbors, state_type>;
    using self_ptr = Cell<number_of_neighbors, state_type>*;
    using neighbor_container = std::array<self_ptr, number_of_neighbors>;

    explicit Cell(){}
    virtual ~Cell() = default;

    state_type         state;
    neighbor_container neighbors;
};

template<typename T_state>
struct Cell<0, T_state>
{
    using state_type = T_state;
    constexpr static int number_of_neighbors = 0;
    using self_type = Cell<number_of_neighbors, state_type>;
    using self_ptr = Cell<number_of_neighbors, state_type>*;

    explicit Cell(){}
    virtual ~Cell() = default;

    state_type state;
};

template<typename T_state>
struct Cell<DYNAMIC, T_state>
{
    using state_type = T_state;
    constexpr static int number_of_neighbors = DYNAMIC;
    using self_type = Cell<number_of_neighbors, state_type>;
    using self_ptr = Cell<number_of_neighbors, state_type>*;
    using neighbor_container = std::vector<self_ptr>;

    explicit Cell(){}
    virtual ~Cell() = default;

    state_type state;
    neighbor_container neighbors;
};

}

#endif /* MINIASCAPE_CELL */
