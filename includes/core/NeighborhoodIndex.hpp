#ifndef MINIASCAPE_NEIGHBORHOOD_INDEX
#define MINIASCAPE_NEIGHBORHOOD_INDEX
#include <array>
#include <stdexcept>

namespace miniascape
{

// 2D
/* -> 1 -> *
 *  _ _ _  *
 * |_|_|_| *
 * |_|_|_| *
 * |_|_|_| */ 

struct MooreNeighborhood
{
    constexpr static std::size_t dimension = 2;
    constexpr static std::size_t num_neighbor = 8;
    using index_type      = int;
    using cell_index_type = std::array<index_type, dimension>;

    static cell_index_type access(
        const std::size_t i, const cell_index_type& index)
    {
        switch(i)
        {
          case 0:
            return {{index[0]+1, index[1]}};
          case 1:
            return {{index[0]+1, index[1]+1}};
          case 2:
            return {{index[0],   index[1]+1}};
          case 3:
            return {{index[0]-1, index[1]+1}};
          case 4:
            return {{index[0]-1, index[1]}};
          case 5:
            return {{index[0]-1, index[1]-1}};
          case 6:
            return {{index[0],   index[1]-1}};
          case 7:
            return {{index[0]+1, index[1]-1}};
          default:
            throw std::invalid_argument("invalid index");
        }
    }
};

/* -> 1 -> *
 *    _    *
 *  _|_|_  *
 * |_|_|_| *
 *   |_|   */ 
struct VonNeumannNeighborhood
{
    constexpr static std::size_t dimension = 2;
    constexpr static std::size_t num_neighbor = 4;
    using index_type      = int;
    using cell_index_type = std::array<index_type, dimension>;

    static cell_index_type access(
        const std::size_t i, const cell_index_type& idx)
    {
        switch(i)
        {
          case 0:
            return {{idx[0]+1, idx[1]}};
          case 1:
            return {{idx[0], idx[1]+1}};
          case 2:
            return {{idx[0]-1, idx[1]}};
          case 3:
            return {{idx[0], idx[1]-1}};
          default:
            throw std::invalid_argument("invalid index");
        }
    }
};

/* -> 1 -> *
 *    ^    *
 *   /_\   *
 *  /\ /\  *
 * /__v__\ */ 
struct TriangleLatticeIndex
{
    constexpr static std::size_t num_neighbor = 3;

};

/* -> 1 -> *
 *   ^ ^   *
 *  | | |  *
 *  /\^/\  *
 * | | | | *
 *  \/v\/  *
 *  | | |  *
 *   v v   */
struct HexagonalLatticeIndex
{
    constexpr static std::size_t num_neighbor = 6;

};




}

#endif /* MINIASCAPE_NEIGHBORHOOD_INDEX */
