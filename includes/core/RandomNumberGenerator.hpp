#ifndef MINIASCAPE_RANDOM_STATE_GENERATOR
#define MINIASCAPE_RANDOM_STATE_GENERATOR
#include "util/meta_function.hpp"
#include <random>

namespace miniascape
{

class RandomNumberGenerator
{
  public:
    RandomNumberGenerator(const unsigned int seed): seed_(seed), mt_(seed){}
    ~RandomNumberGenerator() = default;

    template<typename T>
    T uniform_int(const T begin, const T end)
    {
        return (std::uniform_int_distribution<T>(begin, end))(this->mt_);
    }

    template<typename T>
    T uniform_real(const T begin, const T end)
    {
        return (std::uniform_real_distribution<T>(begin, end))(this->mt_);
    }

    unsigned int seed() const {return seed_;}

  private:
    const unsigned int seed_;
    std::mt19937 mt_;
};

template<typename T_state>
class RandomStateGenerator{};

}

#endif /* MINIASCAPE_RANDOM_STATE_GENERATOR */
