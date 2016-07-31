#ifndef MINIASCAPE_PERIODIC_BOUNDARY
#define MINIASCAPE_PERIODIC_BOUNDARY
#include <array>
#include "zip_iterator.hpp"

namespace miniascape
{

template<typename T_neighbor>
class PeriodicBoundary
{
  public:
    constexpr static std::size_t dimension = T_neighbor::dimension;
    using cell_index_type = std::array<std::size_t, dimension>;

  public:
    PeriodicBoundary() = default;
    PeriodicBoundary(const cell_index_type& begin, const cell_index_type& end)
        :begin_(begin), end_(end)
    {}
    ~PeriodicBoundary() = default;

    cell_index_type access(const std::size_t i, const cell_index_type& id) const;

  private:
    // [begin, end)
    cell_index_type begin_; // = (0, ..., 0), normally
    cell_index_type end_;
};

template<typename T_neighbor>
typename PeriodicBoundary<T_neighbor>::cell_index_type
PeriodicBoundary<T_neighbor>::access(const std::size_t i,
                                     const cell_index_type& index) const
{
    cell_index_type retval = index;

    // to avoid size_t(-1) overflow
    for(auto iter = make_zip(begin_.cbegin(), end_.cbegin(), retval.begin());
            iter != make_zip(begin_.cend(),   end_.cend(),   retval.end());
            ++iter)
        if(*get<0>(iter) == *get<2>(iter))
            *get<2>(iter) = *get<1>(iter);

    retval = T_neighbor::access(i, retval);

    for(auto iter = make_zip(begin_.cbegin(), end_.cbegin(), retval.begin());
            iter != make_zip(begin_.cend(),   end_.cend(),   retval.end());
            ++iter)
        if(*get<1>(iter) <= *get<2>(iter))
            *get<2>(iter) -= *get<1>(iter);

    return retval;
}

}

#endif /* MINIASCAPE_PERIODIC_BOUNDARY */
