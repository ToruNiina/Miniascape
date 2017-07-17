#ifndef MINIASCAPE_PERIODIC_BOUNDARY
#define MINIASCAPE_PERIODIC_BOUNDARY
#include <array>
#include <pseudo/zip_iterator.hpp>
#include "Cell.hpp"

namespace miniascape
{

template<typename T_neighbor>
class PeriodicBoundary
{
  public:
    using neighbor_type   = T_neighbor;
    using cell_index_type = typename neighbor_type::cell_index_type;
    constexpr static std::size_t dimension = neighbor_type::dimension;

  public:
    PeriodicBoundary() = default;
    PeriodicBoundary(const cell_index_type& begin, const cell_index_type& end)
        :begin_(begin), end_(end)
    {}
    ~PeriodicBoundary() = default;

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
};

template<typename T_neighbor>
template<typename T_world>
typename T_world::cell_ptr const&
PeriodicBoundary<T_neighbor>::access(
        const cell_index_type& id, const T_world& container) const
{
    cell_index_type index = id;
    for(auto iter = psd::make_zip_iterator(index.begin(), begin_.cbegin(), end_.cbegin());
            iter != psd::make_zip_iterator(index.end(), begin_.cend(), end_.cend());
            ++iter)
    {
        const int range = *psd::get<2>(iter) - *psd::get<1>(iter);
        if((*psd::get<0>(iter) < *psd::get<1>(iter)) /* index < begin */||
           (*psd::get<0>(iter) >= *psd::get<2>(iter))/* end <= index  */) 
        {
            const int idx = *psd::get<0>(iter) % range;
            *psd::get<0>(iter) = (idx < 0) ? idx + range : idx;
        }
    }
    return container(index);
}

template<typename T_neighbor>
template<typename T_world>
typename T_world::cell_ptr &
PeriodicBoundary<T_neighbor>::access(
        const cell_index_type& id, T_world& container) const
{
    cell_index_type index = id;
    for(auto iter = psd::make_zip_iterator(index.begin(), begin_.cbegin(), end_.cbegin());
            iter != psd::make_zip_iterator(index.end(), begin_.cend(), end_.cend());
            ++iter)
    {
        const int range = *psd::get<2>(iter) - *psd::get<1>(iter);
        if((*psd::get<0>(iter) < *psd::get<1>(iter)) /* index < begin */||
           (*psd::get<0>(iter) >= *psd::get<2>(iter))/* end <= index  */) 
        {
            const int idx = *psd::get<0>(iter) % range;
            *psd::get<0>(iter) = (idx < 0) ? idx + range : idx;
        }
    }
    return container(index);
}

}

#endif /* MINIASCAPE_PERIODIC_BOUNDARY */
