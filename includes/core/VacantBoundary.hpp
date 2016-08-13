#ifndef MINIASCAPE_VOID_BOUNDARY
#define MINIASCAPE_VOID_BOUNDARY
#include <array>
#include <memory>
#include "util/zip_iterator.hpp"
#include "Cell.hpp"

namespace miniascape
{

template<typename T_state, typename T_neighbor>
class VacantBoundary
{
  public:
    using neighbor_type   = T_neighbor;
    using state_type      = T_state;
    using cell_type       = Cell<0, state_type>;
    using cell_ptr        = std::unique_ptr<const cell_type>;
    using cell_index_type = typename neighbor_type::cell_index_type;
    constexpr static std::size_t dimension = neighbor_type::dimension;

  public:
    VacantBoundary() = default;
    VacantBoundary(const state_type& vacant,
                   const cell_index_type& begin, const cell_index_type& end)
        :vacant_(new cell_type(vacant)), begin_(begin), end_(end)
    {}
    ~VacantBoundary() = default;

    template<typename T_world>
    typename T_world::cell_ptr const&
    access(const cell_index_type& id, const T_world& world) const;

    template<typename T_world>
    typename T_world::cell_ptr &
    access(const cell_index_type& id, T_world& container) const;

  private:
    // [begin, end)
    cell_index_type begin_; // = (0, ..., 0), normally
    cell_index_type end_;
    cell_ptr        vacant_;
};

template<typename T_state, typename T_neighbor>
template<typename T_world>
typename T_world::cell_ptr const&
VacantBoundary<T_state, T_neighbor>::access(
        const cell_index_type& id, const T_world& container) const
{
    for(auto iter = make_zip(id.begin(), begin_.cbegin(), end_.cbegin());
            iter != make_zip(id.end(), begin_.cend(), end_.cend());
            ++iter)
    {
        if(*get<0>(iter) < *get<1>(iter) || *get<2>(iter) <= *get<0>(iter))
            return vacant_;
    }
    return container(index);
}

template<typename T_state, typename T_neighbor>
template<typename T_world>
typename T_world::cell_ptr &
VacantBoundary<T_state, T_neighbor>::access(
        const cell_index_type& id, T_world& container) const
{
    for(auto iter = make_zip(id.begin(), begin_.cbegin(), end_.cbegin());
            iter != make_zip(id.end(), begin_.cend(), end_.cend());
            ++iter)
    {
        if(*get<0>(iter) < *get<1>(iter) || *get<2>(iter) <= *get<0>(iter))
            return vacant_;
    }
    return container(index);
}

}//miniascape

#endif /* MINIASCAPE_PERIODIC_BOUNDARY */
