#ifndef MINIASCAPE_RULE
#define MINIASCAPE_RULE

namespace miniascape
{

template<typename T_traits>
class RuleBase
{
  public:
    using traits_type = T_traits;
    using time_type   = typename traits_type::time_type;
    using state_type  = typename traits_type::state_type;
    using cell_type   = typename traits_type::cell_type;

  public:

    RuleBase() = default;
    virtual ~RuleBase() = default;

    virtual state_type step(const cell_type& cell) = 0;
    virtual time_type  delta_t() = 0;
};

}

#endif /* MINIASCAPE_RULE */
