#ifndef MINIASCAPE_WORLD
#define MINIASCAPE_WORLD
#include <vector>
#include <memory>

namespace miniascape
{

template<typename T_traits>
class World
{
  public:

    using traits_type    = T_traits;
    using size_type      = typename traits_type::size_type;
    using state_type     = typename traits_type::state_type;
    using cell_type      = typename traits_type::cell_type;
    using cell_ptr       = std::unique_ptr<cell_type>;
    using container_type = std::vector<cell_ptr>;
    using iterator       = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;

  public:

    World() = default;
    virtual ~World() = default;

    template<typename... T_args>
    void emplace(T_args&&... args)
    {
        container_.emplace_back(new cell_type(std::forward<T_args>(args)...));
    }

    size_type size()  const {return container_.size();}
    bool      empty() const {return container_.empty();}

    cell_ptr &      operator[](const size_type i)       {return container_[i];}
    cell_ptr const& operator[](const size_type i) const {return container_[i];}
    cell_ptr &      at(const size_type i)       {return container_.at(i);}
    cell_ptr const& at(const size_type i) const {return container_.at(i);}

    iterator begin(){return container_.begin();}
    iterator end()  {return container_.end();}
    const_iterator cbegin() const {return container_.cbegin();}
    const_iterator cend()   const {return container_.cend();}

  protected:

    container_type container_;
};

}

#endif /* MINIASCAPE_WORLD */
