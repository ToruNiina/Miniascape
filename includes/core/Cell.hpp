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
    static_assert(I_neighbors > 0, "number of neighbors never be negative");
    using state_type     = T_state;
    constexpr static int number_of_neighbors = I_neighbors;
    using self_type      = Cell<number_of_neighbors, state_type>;
    using self_ptr       = self_type *;
    using self_const_ptr = self_type const*;
    using neighbors_type = std::array<self_const_ptr, number_of_neighbors>;

    Cell() = default;
    virtual ~Cell() = default;

    state_type     state;
    neighbors_type neighbors;
};

template<typename T_state>
struct Cell<0, T_state>
{
    using state_type = T_state;
    constexpr static int number_of_neighbors = 0;
    using self_type  = Cell<number_of_neighbors, state_type>;

    Cell() = default;
    virtual ~Cell() = default;

    state_type state;
};

template<typename T_state>
struct Cell<DYNAMIC, T_state>
{
    using state_type = T_state;
    constexpr static int number_of_neighbors = DYNAMIC;
    using self_type      = Cell<number_of_neighbors, state_type>;
    using self_ptr       = self_type*;
    using self_const_ptr = self_type const*;
    using neighbors_type = std::vector<self_const_ptr>;

    Cell() = default;
    virtual ~Cell() = default;

    state_type     state;
    neighbors_type neighbors;
};

}

#endif /* MINIASCAPE_CELL */
