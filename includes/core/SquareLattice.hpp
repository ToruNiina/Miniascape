#ifndef MINIASCAPE_SQUARE_LATTICE
#define MINIASCAPE_SQUARE_LATTICE
#include "core/World.hpp"
#include "core/NeighborhoodIndex.hpp"
#include "core/RandomNumberGenerator.hpp"

namespace miniascape
{

template<typename T_traits>
class SquareLattice : public World<T_traits>
{
  public:

    using traits_type   = T_traits;
    using size_type     = typename traits_type::size_type;
    using state_type    = typename traits_type::state_type;
    using cell_type     = typename traits_type::cell_type;
    using cell_ptr      = std::unique_ptr<cell_type>;
    using cell_rawptr   = cell_type*;
    using boundary_type = typename traits_type::boundary_type;
    using neighbor_type = typename traits_type::neighbor_type;

    constexpr static std::size_t num_neighbor = neighbor_type::num_neighbor;

  public:
    SquareLattice() = default;
    ~SquareLattice() = default;

    void create(const std::size_t vertical, const std::size_t horizontal);
    void create(const std::size_t vertical, const std::size_t horizontal,
                const state_type& init);

    void randomize(RandomStateGenerator<state_type>& rsg);

    cell_ptr &      operator()(const size_type v, const size_type h);
    cell_ptr const& operator()(const size_type v, const size_type h) const;

  protected:

    std::size_t vertical_;
    std::size_t horizontal_;
    boundary_type boundary_;
};

template<typename T_traits>
void SquareLattice<T_traits>::create(
        const std::size_t vertical, const std::size_t horizontal)
{
    vertical_ = vertical; horizontal_ = horizontal;
    boundary_ = boundary_type({{0,0}}, {{vertical_, horizontal_}});

    // create empty world
    for(std::size_t i = 0; i < (this->vertical_ * this->horizontal_); ++i)
        this->emplace();

    // connect neighboring cells
    for(std::size_t v = 0; v < this->vertical_ ; ++v)
    for(std::size_t h = 0; h < this->horizontal_ ; ++h)
    {
        for(auto i = 0; i < 8; ++i)
        {
            const auto index = boundary_.access(i, {{v, h}});
            (*this)(v, h)->neighbors.at(i) = (*this)(index[0], index[1]).get();
        }
    }
    return;
}

template<typename T_traits>
void SquareLattice<T_traits>::create(const std::size_t vertical,
        const std::size_t horizontal, const state_type& init)
{
    this->create(vertical, horizontal);
    // initialize
    for(auto iter = this->begin(); iter != this->end(); ++iter)
        (*iter)->state = init;
    return;
}

template<typename T_traits>
void SquareLattice<T_traits>::randomize(RandomStateGenerator<state_type>& rsg)
{
    for(auto iter = this->begin(); iter != this->end(); ++iter)
        (*iter)->state = rsg();
    return;
}

template<typename T_traits>
inline typename SquareLattice<T_traits>::cell_ptr&
SquareLattice<T_traits>::operator()(
        const size_type v, const size_type h)
{
    return this->container_.at(v * this->horizontal_ + h);
}

template<typename T_traits>
inline typename SquareLattice<T_traits>::cell_ptr const&
SquareLattice<T_traits>::operator()(
        const size_type v, const size_type h) const
{
    return this->container_.at(v * this->horizontal_ + h);
}

}

#endif /* MINIASCAPE_SQUARE_LATTICE */
