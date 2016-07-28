#ifndef MINIASCAPE_SPACE
#define MINIASCAPE_SPACE
#include <vector>
#include <memory>

namespace miniascape
{

template<typename T_traits>
class Space
{
  public:

    using traits_type = T_traits;
    using world_type  = typename traits_type::world_type;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;
    using cell_ptr    = std::unique_ptr<cell_type>;
    using temporal_container_type = std::vector<state_type>;

  public:

    Space() = default;
    ~Space() = default;

    world_type &      world()       {return world_;}
    world_type const& world() const {return world_;}

    temporal_container_type &      temp()       {return temp_;}
    temporal_container_type const& temp() const {return temp_;}

  private:

    temporal_container_type temp_;
    world_type              world_;
};



}

#endif /* MINIASCAPE_SPACE */
